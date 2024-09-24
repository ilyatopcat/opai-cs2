#include "hooks.h"

void Hooks::DrawAnimatableSceneObject::Hook(CAnimatableSceneObjectDesc* pAnimatableSceneObjectDesc, CRenderContextDx11* pRenderContextDx11, CSceneData* pSceneData, int dataCounter, CSceneView* pSceneView, CSceneLayer* pSceneLayer, void* a7, void* a8) {
	IS_UNINITIALIZED(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);

	auto networkClient = Interfaces::networkClientService->GetNetworkClient();
	if (networkClient && !networkClient->IsConnected())
		return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);

	auto objectInfo = pSceneData->sceneObject;
	if (!objectInfo)
		return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);

	auto pOwner = objectInfo->owner.Get<C_BaseEntity>();
	if (!pOwner)
		return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);
	
	auto type = Visuals::Chams::GetEnemyType(pOwner);
	if (type == -1)
		return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);

	std::string_view materialName{ pSceneData->material->GetName() };
	if (materialName.find("materials/dev/glowproperty.vmat") != std::string::npos)
		return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);

	if ((pOwner->As<C_CSPlayerPawn>() == Entity::GetLocalPlayerPawn() && !Interfaces::input->m_bInThirdPerson) && (config.removals & REMOVALS_TORSO) )
		return;

	auto overrideMaterial = [&](CMaterial2* material, const ColorRGBA& color)
	{
		pSceneData->color.r = static_cast<unsigned char>(color.r * 255.f);
		pSceneData->color.g = static_cast<unsigned char>(color.g * 255.f);
		pSceneData->color.b = static_cast<unsigned char>(color.b * 255.f);
		pSceneData->color.a = static_cast<unsigned char>(color.a * 255.f);

		Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, material);
	};

	auto drawChams = [&](int type, bool xqz = false)
	{
		int materialParam = MATERIAL_PARAM_DEFAULT + static_cast<int>(xqz);

		auto& chamsConfig = config.chams[type];

		if (chamsConfig.enable)
		{
			bool overriding = false;
			if (chamsConfig.material)
			{
				auto material = Visuals::Chams::materials[chamsConfig.material - 1][materialParam];
				if (material)
					overrideMaterial(material, chamsConfig.materialColor);

				overriding = true;
			}

			if (chamsConfig.overlayMaterial)
			{
				auto material = Visuals::Chams::materials[chamsConfig.overlayMaterial - 1][materialParam];
				if (material)
					overrideMaterial(material, chamsConfig.overlayMaterialColor);

				overriding = true;
			}

			return overriding;
		}

		return false;
	};

	constexpr auto ENEMY_CHAMS = CHAMS_ENEMY + CHAMS_ENEMY_XQZ;
	if (type == ENEMY_CHAMS)
	{
		int index{ -1 };

		if (materialName.find("balaclava") != std::string::npos || materialName.find("head") != std::string::npos)
			index = 0;
		if (materialName.find("body") != std::string::npos || materialName.find("arms") != std::string::npos)
			index = 1;
		if (materialName.find("legs") != std::string::npos)
			index = 2;

		float lerpStep = static_cast<float>(index) / 3.f;
		float r = std::lerp<float>(0, 1.f, lerpStep);

		auto material = Visuals::Chams::materials[MATERIAL_FLAT][MATERIAL_PARAM_DEFAULT];
		if (material)
			overrideMaterial(material, ColorRGBA{ r, 0.f, r, 1.f });

	/*	bool draw = drawChams(CHAMS_ENEMY) || drawChams(CHAMS_ENEMY_XQZ, true);
		if (!draw)
			return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);*/
	}
	else
	{
		if (!drawChams(type))
			return Original(pAnimatableSceneObjectDesc, pRenderContextDx11, pSceneData, dataCounter, pSceneView, pSceneLayer, a7, a8);
	}
}