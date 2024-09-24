#include <stdint.h>

#include "../../sdk/interfaces/interfaces.h"
#include "../../utils/utils.h"

#include "visuals.h"
#include <cmath>

Visuals::Box Visuals::Players::GetBox(C_CSPlayerPawn* entity)
{
	Visuals::Box outBox{};

	auto sceneNode = entity->m_pGameSceneNode();
	if (!sceneNode)
		return {};

	auto movementServices = entity->m_pMovementServices();
	if (!movementServices)
		return {};

	auto absOrigin = sceneNode->m_vecAbsOrigin();
	auto duckAmount = movementServices->m_flDuckAmount();

	auto bbAdjust = Vector{ 0.f, 0.f, -16.f } * duckAmount;
	auto bbDown = absOrigin - Vector{ 0.f, 0.f, 1.f };
	auto bbTop = bbDown + Vector{ 0.f, 0.f, 72.f } + bbAdjust;

	Vector screenPoints[2]{};
	if (Render::WorldToScreen(bbTop, screenPoints[1]) && Render::WorldToScreen(bbDown, screenPoints[0])) 
	{
		outBox.h = std::abs((screenPoints[1] - screenPoints[0]).y);
		outBox.w = outBox.h / 2.0f;

		outBox.x = screenPoints[1].x - outBox.w / 2.f;
		outBox.y = screenPoints[1].y;

		outBox.found = true;
		return outBox;
	}

	return {};
}

void Visuals::Players::Store()
{
	const std::unique_lock<std::mutex> m(playerMutex);

	C_CSPlayerPawn* localPlayerPawn = Entity::GetLocalPlayerPawn();
	if (!localPlayerPawn)
		return;

	// erase invalid entities, that were kicked from map
	// but their handle stores in esp memory
	// @opai
	std::erase_if(playerMap, [](const auto& kv) 
	{
		auto& playerInfo = kv.second;
		if (playerInfo.valid)
		{
			int currentIndex = playerInfo.handle == 0xffffffff ? 0x7fff :
				playerInfo.handle & 0x7fff;

			// in case when handle is still valid
			// entity will be found
			// otherwise it will be fucked OR it will be find wrong entity
			auto entity = Interfaces::gameResourceService->pGameEntitySystem->GetBaseEntity(currentIndex);
			if (entity)
			{
				CCSPlayerController* pPlayerController = entity->As<CCSPlayerController>();

				// if entity is wrong (for example it magically became some unknown prop)
				// erase it
				return !pPlayerController->IsPlayer();
			}
			else
				return true;
		}

		return false;
	});

	int localPlayerTeamNum = localPlayerPawn->m_iTeamNum();

	const auto entities = Entity::Get("CCSPlayerController");
	for (auto entity : entities)
	{
		auto controller = entity->As<CCSPlayerController>();
		if (!controller)
			continue;

		auto playerPawn = controller->m_hPawn().Get<C_CSPlayerPawn>();
		if (!playerPawn)
			continue;

		int handle = Entity::GetEntityHandle(playerPawn);
		int teamNum = playerPawn->m_iTeamNum();
		auto playerPtr = playerMap.find(handle);

		if (playerPawn == Entity::GetLocalPlayerPawn() || localPlayerTeamNum == teamNum || !playerPawn->IsAlive())
		{
			if (playerPtr != playerMap.end())
				playerMap.erase(playerPtr);

			continue;
		}

		if (playerPtr == playerMap.end())
		{
			playerMap.insert_or_assign(handle, PlayerInfo{});
			continue;
		}

		auto& playerInfo = playerPtr->second;
		playerInfo.valid = true;
		playerInfo.handle = handle;
		playerInfo.box = GetBox(playerPawn);
		playerInfo.health = playerPawn->m_iHealth();
		playerInfo.name = controller->m_sSanitizedPlayerName();

		auto activeWeapon = playerPawn->GetActiveWeapon();
		if (activeWeapon)
		{
			auto weaponData = activeWeapon->GetWeaponData();
			if (weaponData)
			{
				playerInfo.ammo = activeWeapon->m_iClip1();
				playerInfo.maxAmmo = weaponData->m_iMaxClip1();

				const char* m_szName = weaponData->m_szName();
				const char* nameLen = strstr(m_szName, "weapon_");
				std::string weaponName = nameLen ? nameLen + strlen("weapon_") : m_szName;
				std::transform(weaponName.begin(), weaponName.end(), weaponName.begin(), ::toupper);

				playerInfo.weaponName = std::move(weaponName);
			}
		}
	}
}

void Visuals::Players::Run()
{
	const std::unique_lock<std::mutex> m(playerMutex);

	for (auto it = playerMap.begin(); it != playerMap.end(); it = std::next(it))
	{
		auto& playerInfo = it->second;
		if (!playerInfo.valid)
			continue;

		if (playerInfo.box.found)
		{
			if (config.esp.bounding_box)
				RenderBBox(playerInfo.box);
			if (config.esp.health_bar)
				RenderHealth(playerInfo);
			if (config.esp.name)
				RenderName(playerInfo);
			if (config.esp.weapon)
				RenderWeapon(playerInfo);
		}
	}
}

void Visuals::Players::RenderBBox(Box& box)
{
	const auto mainColor = ColorRGBA{ 255, 255, 255, 255 }.ConvertFromRGBToFloats();
	const auto outlineColor = ColorRGBA{ 0, 0, 0, 255 }.ConvertFromRGBToFloats();

	Render::RectOutline({ box.x - 1, box.y - 1 }, { box.x + box.w + 1, box.y + box.h + 1 }, outlineColor);
	Render::RectOutline({ box.x + 1, box.y + 1 }, { box.x + box.w - 1, box.y + box.h - 1 }, outlineColor);
	Render::RectOutline({ box.x, box.y }, { box.x + box.w, box.y + box.h }, mainColor);
}

void Visuals::Players::RenderHealth(PlayerInfo& info)
{
	auto fullHpColor = ColorRGBA{ 177, 255, 155, 255 };
	auto lowHpColor = ColorRGBA{ 255, 33, 33, 255 };
	const auto outlineColor = ColorRGBA{ 0, 0, 0, 255 }.ConvertFromRGBToFloats();

	int espHealth = std::clamp(info.health, 0, 100);
	float espStep = std::clamp(static_cast<float>(espHealth) / 100.f, 0.f, 1.f);

	auto& box = info.box;
	float hpBarH = (box.h - ((box.h * static_cast<float>(espHealth)) / 100.f));
	hpBarH = std::max<float>(std::min<float>(hpBarH, box.h), 0.f);

	Vector bbOutlineMin{ (box.x - (BAR_WIDTH * 2.f)) - 2.f, box.y - 1.f };
	Vector bbOutlineMax{ BAR_WIDTH * 2.f, box.h + 2.f };

	Vector bbMin{ (box.x - (BAR_WIDTH * 2.f)) - 1.f, box.y + hpBarH };
	Vector bbMax{ BAR_WIDTH, box.h - hpBarH };

	Render::Rect(bbOutlineMin, bbOutlineMin + bbOutlineMax, outlineColor);
	Render::Rect(bbMin, bbMin + bbMax, lowHpColor.Lerp(fullHpColor, espStep).ConvertFromRGBToFloats());
}

void Visuals::Players::RenderName(PlayerInfo& info)
{
	const auto mainColor = (config.esp.nameColor * 255.f).ConvertFromRGBToFloats();
	const auto outlineColor = ColorRGBA{ 0, 0, 0, 255 }.ConvertFromRGBToFloats();
	
	ImGui::PushFont(Render::fonts.verdanaSmall);
	auto textSize = ImGui::CalcTextSize(info.name.c_str());

	auto& box = info.box;
	Render::Text(Vector(box.x + box.w / 2.f, box.y - textSize.y - 3.f), 
		mainColor, FontFlags_Center | FontFlags_DropShadow,
		Render::fonts.verdanaSmall, info.name,
		Render::fonts.verdanaSmall->FontSize);

	ImGui::PopFont();
}

void Visuals::Players::RenderWeapon(PlayerInfo& info)
{
	const auto mainColor = ColorRGBA{ 255, 255, 255, 255 }.ConvertFromRGBToFloats();
	const auto outlineColor = ColorRGBA{ 0, 0, 0, 255 }.ConvertFromRGBToFloats();

	auto fullAmmoColor = ColorRGBA{ 170, 185, 250, 255 };
	auto lowAmmoColor = ColorRGBA{ 255, 33, 33, 255 };

	auto& box = info.box;
	float textOffset = 0.f;
	if (info.ammo > 0)
	{
		float espStep = std::clamp(static_cast<float>(info.ammo) / static_cast<float>(info.maxAmmo), 0.f, 1.f);

		float ammoBarW = ((box.w * static_cast<float>(info.ammo)) / static_cast<float>(info.maxAmmo));
		ammoBarW = std::max<float>(std::min<float>(ammoBarW, box.w), 0.f);

		Vector bbOutlineMin{ box.x - 1.f, box.y + box.h + 2.f };
		Vector bbOutlineMax{ box.w + 2.f, BAR_WIDTH * 2.f };

		Vector bbMin{ box.x, box.y + box.h + 3.f };
		Vector bbMax{ ammoBarW, BAR_WIDTH };

		Render::Rect(bbOutlineMin, bbOutlineMin + bbOutlineMax, outlineColor);
		Render::Rect(bbMin, bbMin + bbMax, lowAmmoColor.Lerp(fullAmmoColor, espStep).ConvertFromRGBToFloats());

		textOffset += (BAR_WIDTH * 2.f) + 1.f;
	}

	Render::Text(Vector(box.x + box.w / 2.f, box.y + box.h + textOffset + 3.f), mainColor, FontFlags_Center | FontFlags_Outline,
		Render::fonts.onetapPixel, info.weaponName, Render::fonts.onetapPixel->FontSize);
}