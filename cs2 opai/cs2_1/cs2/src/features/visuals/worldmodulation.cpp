#include <string>

#include "visuals.h"
#include "../../utils/utils.h"

void Visuals::WorldModulation::Skybox() {
    using UpdateSkybox_t = void(__fastcall*)(void*);
    static UpdateSkybox_t UpdateSkybox = reinterpret_cast<UpdateSkybox_t>(Utils::OpcodeScan("client.dll", "48 89 5C 24 08 57 48 83 EC 30 48 8B F9 E8 ?? ?? ?? ?? 48 8B 47"));

    bool disableFogRendering = config.world_modulation.disableFogRendering;

    ColorRGB skyboxColor = config.world_modulation.skyboxColor;

    static bool previousDisableFogRendering = !disableFogRendering;

    static ColorRGB previousSkyboxColor(-1, -1, -1);

    if (previousSkyboxColor == skyboxColor && previousDisableFogRendering == disableFogRendering)
        return;

    previousDisableFogRendering = disableFogRendering;

    previousSkyboxColor = skyboxColor;

    const auto& sky = Entity::Get("C_EnvSky");
    for (CEntityInstance* entity : sky) {
        C_EnvSky* pEnvSky = entity->As<C_EnvSky>();

        Skybox(pEnvSky);

        UpdateSkybox(pEnvSky);
    }
}

void Visuals::ThirdPerson()
{
    auto localPlayer = Entity::GetLocalPlayerPawn();

    if (!localPlayer)
        return;

    bool bInThirdPerson = false;
    if (KeyHandler->WasKeyPressed(config.thirdperson.thirdperson_keybind, config.thirdperson.thirdperson_keybind_style))
        bInThirdPerson = true;

    static float flCurrentFraction = 0.f;
    if (bInThirdPerson && localPlayer->IsAlive())
    {
        const float flDistance = config.thirdperson.distance;
        Vector vecViewAngles = Interfaces::input->GetViewAngles();
        Vector vecInversedViewAngles = Interfaces::input->GetViewAngles();
        vecInversedViewAngles.z = flDistance;

        Vector vecForward, vecUp, vecRight;
        Math::AngleVectors(vecInversedViewAngles, vecForward, vecRight, vecUp);

        Vector vecEyePosition = localPlayer->GetEyePosition();
        Vector vecOffset = vecEyePosition - vecForward * flDistance + vecRight + vecUp;

        TraceFilter_t traceFilter(0x3001, localPlayer, nullptr, 4);
        traceFilter.m_arrCollisions.at(1) = 0x10000;

        Ray_t ray;
        GameTrace_t trace;
        Interfaces::engineTrace->TraceShape(&ray, vecEyePosition, vecOffset, &traceFilter, &trace);

        const float flTargetFraction = trace.m_flFraction;
        if (flCurrentFraction > flTargetFraction)
            flCurrentFraction = flTargetFraction;
        else if (flCurrentFraction > 0.9999f)
            flCurrentFraction = 1.0f;

        flCurrentFraction = Math::Interpolate(flCurrentFraction, flTargetFraction, Interfaces::globalVars->frameTime * 10.0f);
        vecViewAngles.z = flDistance;

        Interfaces::input->m_bInThirdPerson = flCurrentFraction > 0.1f;
        Interfaces::input->m_vecThirdPersonAngles = vecViewAngles;
    }
    else
    {
        flCurrentFraction = 0.0f;
        Interfaces::input->m_bInThirdPerson = false;
    }

}

void Visuals::ProcessBulletImpactsOnClient(){
    if (!Entity::GetLocalPlayerPawn() || !Entity::GetLocalPlayerPawn()->IsAlive())
        return;

    auto bulletService = Entity::GetLocalPlayerPawn()->m_pBulletServices();

    if (!bulletService)
        return;

    for (auto i = bulletService->BulletData().size; i > lastCountBullet; --i)
    {
        auto memory = bulletService->BulletData().data[i - 1];
        Interfaces::client->GetDebugOverlaySystem()->AddBoxOverlay(memory.position, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(), ColorRGBA(255, 0, 0, 127));
    }

    if (bulletService->BulletData().size != lastCountBullet)
        lastCountBullet = bulletService->BulletData().size;
}

void Visuals::WorldModulation::ProcessTracers(Vector start, Vector end, ColorRGB color) {
    auto& bullet = bullets.emplace_back();

    if (!Interfaces::particleSystem || !Interfaces::particleManager || !config.world_modulation.bulletracers)
        return;

    bullet.effectIndex = -1;

    bullet.particleData_ = {};

    auto dir = (end - start);
    auto stage_2 = start + (dir * 0.3f);
    auto stage_3 = start + (dir * 0.5f);

    Vector positions_[] = { start,stage_2, stage_3,end };

    for (int i = 0; i < sizeof(positions_) / sizeof(Vector); i++) {

        CParticleInformation particle_info{};
        particle_info.time = 3.0f;
        particle_info.width = 1.0f;
        particle_info.unk = 1.f;

        bullet.positions = new Vector[i + 1];
        bullet.times = new float[i + 1];

        for (int j = 0; j < i + 1; j++) {
            bullet.positions[j] = positions_[j];
            bullet.times[j] = 1.f / 64.f * float(j);
        }

        bullet.particleData_.vecPosition = bullet.positions;
        bullet.particleData_.flTime2 = bullet.times;

        CParticleEffect particle_effect_{ };
        particle_effect_.name = "particles/entity/spectator_utility_trail.vpcf";
        particle_effect_.pad[0] = 8;
        Interfaces::particleSystem->CreateEffectIndex(&bullet.effectIndex, &particle_effect_);
        CParticleColor clr = { (float)color.r, (float)color.g, (float)color.b };
        Interfaces::particleSystem->CreateEffect(bullet.effectIndex, 16, &clr, 0);

        Interfaces::particleSystem->CreateEffect(bullet.effectIndex, 3, &particle_info, 0);

        Interfaces::particleManager->CreateSnapshot(&bullet.handleSnapshotParticle);

        Interfaces::particleSystem->UnkFunction(bullet.effectIndex, 0, &bullet.handleSnapshotParticle);

        bullet.handleSnapshotParticle->Draw(i + 1, &bullet.particleData_);

        delete[] bullet.positions;
        delete[] bullet.times;
    }
}

void Visuals::WorldModulation::Skybox(C_EnvSky* pEnvSky) {
    bool disableFogRendering = config.world_modulation.disableFogRendering;

    ColorRGB skyboxColor = config.world_modulation.skyboxColor;

    ByteColorRGB color = (skyboxColor * 255).ToByteRGB();

    pEnvSky->m_vTintColor() = color;

    pEnvSky->m_flBrightnessScale() = disableFogRendering ? 0.f : 1.f;
}

void Visuals::WorldModulation::Lighting(CSceneLightObject* pSceneLightObject) {
    ColorRGB lightingColor = config.world_modulation.lightingColor;

    pSceneLightObject->color = lightingColor * 3;
}

void Visuals::WorldModulation::Exposure(C_CSPlayerPawn* localPlayerPawn) {
    using UpdateCameraServices_t = void(__fastcall*)(CPlayer_CameraServices*, int);
    static UpdateCameraServices_t UpdateCameraServices = reinterpret_cast<UpdateCameraServices_t>(Utils::OpcodeScan("client.dll", "48 89 5C 24 08 57 48 83 EC 20 8B FA 48 8B D9 E8 ?? ?? ?? ?? 84 C0 0F 84"));
    
    static float previousExposure = -1;

    float exposure = static_cast<float>(config.world_modulation.exposure);

    if (previousExposure == exposure)
        return;

    if (!localPlayerPawn)
        return;

    CPlayer_CameraServices* cameraServices = localPlayerPawn->m_pCameraServices();

    if (!cameraServices)
        return;

    C_PostProcessingVolume* postProcessingVolume = cameraServices->m_hActivePostProcessingVolume().Get<C_PostProcessingVolume>();

    if (!postProcessingVolume)
        return;

    previousExposure = exposure;
    
    Exposure(postProcessingVolume);

    UpdateCameraServices(cameraServices, 0);
}

void Visuals::WorldModulation::Exposure(C_PostProcessingVolume* pPostProcessingVolume) {
    float exposure = config.world_modulation.exposure * 0.01f;

    pPostProcessingVolume->m_bExposureControl() = true;

    pPostProcessingVolume->m_flExposureFadeSpeedDown() = pPostProcessingVolume->m_flExposureFadeSpeedUp() = 0;

    pPostProcessingVolume->m_flMinExposure() = pPostProcessingVolume->m_flMaxExposure() = exposure;
}