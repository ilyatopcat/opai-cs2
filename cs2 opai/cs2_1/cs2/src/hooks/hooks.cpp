#include "hooks.h"

#include "../../dependencies/minhook/minhook.h"
#include "../utils/utils.h"
#include "../utils/vmt.h"

bool Hooks::Initialize() {
    IsUninitialized = false;

    /*
    __int64 dll = reinterpret_cast<__int64>(GetModuleHandle("materialsystem2.dll"));

    __int64 qword_1801099C0 = dll + 0x1099C0;
    __int64 pResourceSystem = *reinterpret_cast<__int64*>(qword_1801099C0);

    __int64 v72 = 0;
    (*(void(__fastcall**)(__int64, __int64, __int64*, __int64))(pResourceSystem + 0x130))(qword_1801099C0, 1952542070i64, &v72, 7i64);

    printf("v72: %i \n", v72);
    */

    MH_Initialize();

    DirectX::Initialize();
    Visuals::Chams::initMaterials();

    CREATE_HOOK(DirectXPresent, DirectX::PresentAddress);

    // xref: "cl: %d: %s\n", "cl: %d ===========================\n"
    CREATE_HOOK(CreateMove, vmt::GetVMethod(Interfaces::input, 5));
    CREATE_HOOK(ValidateInput, vmt::GetVMethod(Interfaces::input, 7));

    CREATE_HOOK(MouseInput, vmt::GetVMethod(Interfaces::input, 13));

    CREATE_HOOK(EnableCursor, vmt::GetVMethod(Interfaces::inputSystem, 78));

    CREATE_HOOK(UpdateInPVS, Utils::OpcodeScan("client.dll", "40 53 48 83 EC ? 48 8B 01 48 8B D9 FF 90 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B 43"));

    CREATE_HOOK(UpdatePostProcessing, Utils::OpcodeScan("client.dll", "48 89 5C 24 08 57 48 83 EC 60 80"));

    // cvar: lb_enable_lights (https://i.imgur.com/u3IWSYz.png)
    CREATE_HOOK(DrawLightSceneObject, Utils::OpcodeScan("scenesystem.dll", "48 89 54 24 10 53 55 41"));

    CREATE_HOOK(UpdateSkybox, Utils::OpcodeScan("client.dll", "48 8B C4 48 89 58 18 48 89 70 20 55 57 41 54 41 55"));

    CREATE_HOOK(DrawOverHeadInfo, Utils::OpcodeScan("client.dll", "40 53 48 83 EC ? 48 8B D9 83 FA ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 10"));

    // cvar: weapon_reticle_knife_show
    CREATE_HOOK(DrawCrosshair, Utils::OpcodeScan("client.dll", "48 89 5C 24 08 57 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 85"));

    CREATE_HOOK(DrawScopeOverlay, Utils::OpcodeScan("client.dll", "40 56 57 48 83 EC 68"));

    CREATE_HOOK(GetFieldOfView, Utils::OpcodeScan("client.dll", "40 53 48 81 EC 80 00 00 00 48 8B D9 E8 ?? ?? ?? ?? 48 85"));

    CREATE_HOOK(DrawFlashbang, Utils::OpcodeScan("client.dll", "40 55 57 48 8D AC 24 C8"));

    // CSmokeVolumeSceneObjectDesc : 1 index
    CREATE_HOOK(DrawSmokeVolume, Utils::OpcodeScan("client.dll", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 40 48 8B 9C 24 88 00 00 00 4D"));

    // cvar: cl_firstperson_legs
    //CREATE_HOOK(DrawTorso, Utils::OpcodeScan("client.dll", "40 53 48 83 EC 20 48 8B D9 E8 ?? ?? ?? ?? 48 85 C0 0F 85"));

    // xref: "team_intro_end", "team_intro_start"
    CREATE_HOOK(DrawTeamIntro, Utils::OpcodeScan("client.dll", "48 83 EC 28 45 0F B6"));

    CREATE_HOOK(ShouldUpdateKnifeSequences, Utils::OpcodeScan("animationsystem.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B 40 48"));

    // cvar: mp_teammates_are_enemies
    CREATE_HOOK(DrawRadarEntities, Utils::OpcodeScan("client.dll", "48 89 4C 24 08 55 41 55 48 8D AC 24 78"));

    // cvar: view_punch_decay
    CREATE_HOOK(ViewPunch, Utils::OpcodeScan("client.dll", "40 55 53 56 41 56 41 57 48 8D 6C 24 C9"));

    CREATE_HOOK(OverrideView, Utils::OpcodeScan("client.dll", "40 53 48 81 EC A0 00 00 00 49"));

    // xref: "C:\\buildworker\\csgo_rel_win64\\build\\src\\scenesystem\\ (&ILightBinner `RTTI Type Descriptor', &CLightBinner2 `RTTI Type Descriptor')
    CREATE_HOOK(UpdateAggregateSceneObject, Utils::OpcodeScan("scenesystem.dll", "48 89 5C 24 18 48 89 6C 24 20 56 57 41 55"));

    // xref: "mapname", "transition", "game_newmap"
    CREATE_HOOK(LevelInit, Utils::OpcodeScan("client.dll", "48 89 5C 24 18 56 48 83 EC 30 48"));
    CREATE_HOOK(LevelShutdown, Utils::OpcodeScan("client.dll", "48 83 EC ? 48 8B 0D ? ? ? ? 48 8D 15 ? ? ? ? 45 33 C9 45 33 C0 48 8B 01 FF 50 ? 48 85 C0 74 ? 48 8B 0D ? ? ? ? 48 8B D0 4C 8B 01 41 FF 50 ? 48 83 C4"));
    CREATE_HOOK(DrawAggregateSceneObject, Utils::OpcodeScan("scenesystem.dll", "4C 89 44 24 ? 48 89 54 24 ? 55 57 48 8D AC 24"));

    CREATE_HOOK(OnAddEntity, Utils::OpcodeScan("client.dll", "48 89 74 24 10 57 48 83 EC 20 48 8B F9 41 8B C0 B9"));
    CREATE_HOOK(OnRemoveEntity, Utils::OpcodeScan("client.dll", "48 89 74 24 10 57 48 83 EC 20 48 8B F9 41 8B C0 25"));

    CREATE_HOOK(FrameStageNotify, Utils::OpcodeScan("client.dll", "48 89 5C 24 ? 56 48 83 EC ? 8B 05 ? ? ? ? 8D 5A"));

    CREATE_HOOK(DrawGlow, Utils::OpcodeScan("client.dll", "40 53 48 83 EC 20 48 8B 54"));

    CREATE_HOOK(DrawAnimatableSceneObject, Utils::OpcodeScan("scenesystem.dll", "48 8B C4 53 41 54 41 55 48 81 EC ? ? ? ? 4D 63 E1"));

    MH_EnableHook(MH_ALL_HOOKS);

    return true;
}

void* Hooks::ShouldUpdateKnifeSequences::Hook(void* a1, void* a2, void* a3) {
    const char* szModelName = *reinterpret_cast<const char**>(reinterpret_cast<std::uintptr_t>(a1) + 0x8);
    if (szModelName == nullptr || !config.skins.knifes.enabled)
        return Original(a1, a2, a3);

    std::string strModelName = std::string(szModelName);
    if (strModelName.starts_with("weapons/models/knife/"))
        *reinterpret_cast<__int64*>(reinterpret_cast<std::uintptr_t>(a3) + 0x30) = 0;

	return Original(a1, a2, a3);
}

void Hooks::Uninitialize() {
    IsUninitialized = true;

    if (IsUninitialized)
        EnableCursor::UnHook();

    DirectX::Uninitialize();

    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}
