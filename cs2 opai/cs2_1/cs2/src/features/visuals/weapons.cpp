#include <stdint.h>

#include "../../sdk/interfaces/interfaces.h"
#include "../../utils/utils.h"

#include "visuals.h"
#include <cmath>

std::vector<ImVec2> GetWorldPosition(const Vector& pos, float radius)
{
	constexpr float step = M_PI * 2.0f / 60.f;

	std::vector<ImVec2> points{};

	for (float lat = 0.f; lat <= M_PI * 2.f; lat += step)
	{
		Vector point3d = Vector(std::sin(lat), std::cos(lat), 0.f) * radius;

		auto p = pos + point3d;

		Vector point2d{};
		if (Render::WorldToScreen(p, point2d))
			points.emplace_back(ImVec2(point2d.x, point2d.y));
	}

	return points;
}

Visuals::Box Visuals::Weapons::GetBox(C_BaseEntity* entity)
{
	Visuals::Box out{};

	auto collision = entity->m_pCollision();
	if (!collision)
		return out;

	Vector min = collision->m_vecMins();
	Vector max = collision->m_vecMaxs();

	auto sceneNode = entity->m_pGameSceneNode();

	Vector points[8] = 
	{ 
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z), 
		Vector(max.x, min.y, min.z), 
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	CTransform nodeToWorldTransform = sceneNode->m_nodeToWorld();
	Matrix3x4_t matTransform = nodeToWorldTransform.quatOrientation.ToMatrix(nodeToWorldTransform.vecPosition);

	int validBounds = 0;
	Vector pointsToScreen[8]{};
	for (int i = 0; i < 8; i++)
	{
		auto transform = Math::VectorTransform(points[i], matTransform);
		if (!Render::WorldToScreen(transform, pointsToScreen[i]))
			continue;

		validBounds++;
	}

	if (!validBounds)
		return out;

	float left = pointsToScreen[3].x;
	float top = pointsToScreen[3].y;
	float right = pointsToScreen[3].x;
	float bottom = pointsToScreen[3].y;

	for (auto i = 1; i < 8; i++)
	{
		if (left > pointsToScreen[i].x)
			left = pointsToScreen[i].x;
		if (top < pointsToScreen[i].y)
			top = pointsToScreen[i].y;
		if (right < pointsToScreen[i].x)
			right = pointsToScreen[i].x;
		if (bottom > pointsToScreen[i].y)
			bottom = pointsToScreen[i].y;
	}

	out.x = left;
	out.y = bottom;
	out.w = right - left;
	out.h = top - bottom;
	out.found = true;

	return out;
}

void Visuals::Weapons::Store()
{
	const std::unique_lock<std::mutex> m(weaponMutex);

	C_CSPlayerPawn* localPlayerPawn = Entity::GetLocalPlayerPawn();
	if (!localPlayerPawn)
		return;

	// erase invalid entities, that were kicked from map
	// but their handle stores in esp memory
	// @opai
	std::erase_if(weaponMap, [](const auto& kv)
	{
		auto& weaponInfo = kv.second;
		if (weaponInfo.valid)
		{
			if (weaponInfo.alpha <= 0.f)
				return true;

			int currentIndex = weaponInfo.handle == 0xffffffff ? 0x7fff :
				weaponInfo.handle & 0x7fff;

			// in case when handle is still valid
			// entity will be found
			// otherwise it will be fucked OR it will be find wrong entity
			auto entity = Interfaces::gameResourceService->pGameEntitySystem->GetBaseEntity(currentIndex);
			if (entity)
			{
				C_BaseEntity* weapon = entity->As<C_BaseEntity>();
				if (weaponInfo.isMolotov || weaponInfo.isSmoke)
					return weaponInfo.expireTime >= weaponInfo.lifeTime || weaponInfo.infernoPos.empty();

				return !weapon->isWeapon() || weapon->m_hOwnerEntity().GetEntryIndex() > 0;
			}
			else
				return true;
		}

		return false;
	});

	bool isAlive = localPlayerPawn->IsAlive();

	Vector origin{};
	if (isAlive)
		origin = localPlayerPawn->m_pGameSceneNode()->m_vecAbsOrigin();

	auto smokes = Entity::Get("C_SmokeGrenadeProjectile");
	for (auto smoke : smokes)
	{
		auto smokeEntity = smoke->As<C_SmokeGrenadeProjectile>();

		int handle = Entity::GetEntityHandle(smoke->As<C_CSPlayerPawn>());
		auto weaponPtr = weaponMap.find(handle);

		if (weaponPtr == weaponMap.end())
		{
			weaponMap.insert_or_assign(handle, WeaponInfo{});
			continue;
		}

		auto smokeTickBegin = smokeEntity->m_nSmokeEffectTickBegin();
		if (smokeTickBegin <= 0 || !smokeEntity->m_bSmokeEffectSpawned())
			continue;

		auto vecOrigin = smokeEntity->m_pGameSceneNode()->m_vecOrigin();

		auto& weaponInfo = weaponPtr->second;
		weaponInfo.valid = true;
		weaponInfo.handle = handle;
		weaponInfo.fireRange = 152.f;
		weaponInfo.infernoPos = std::move(GetWorldPosition(vecOrigin, weaponInfo.fireRange));

		Vector screenOrigin;

		auto& bBox = weaponInfo.box;
		bBox.found = Render::WorldToScreen(vecOrigin, screenOrigin);
		bBox.x = screenOrigin.x - NADE_TIMER_WIDTH;
		bBox.y = screenOrigin.y;
		bBox.w = NADE_TIMER_WIDTH;
		bBox.h = 4.f;

		if (isAlive)
		{
			float distance = origin.Dist(vecOrigin);
			weaponInfo.alpha = 255.f - std::clamp((255.f * distance) / MAX_NADE_DISTANCE, 0.f, 255.f);
		}
		else
			weaponInfo.alpha = 0.f;

		auto curtimeTick = TIME_TO_TICKS(Interfaces::globalVars->curTime);
		auto timeElapsed = TICKS_TO_TIME(std::abs(smokeTickBegin - curtimeTick));

		weaponInfo.name = "SMOKE";
		weaponInfo.isSmoke = true;
		weaponInfo.expireTime = timeElapsed;
		weaponInfo.lifeTime = 22.5f;

		auto lifeTimeTicks = TIME_TO_TICKS(weaponInfo.lifeTime);
		auto expireTimeTicks = TIME_TO_TICKS(weaponInfo.expireTime);

		// just a lifehack to not to add extra variables for molotov
		// looks like ghetto
		// @opai
		weaponInfo.ammo = lifeTimeTicks - expireTimeTicks;
		weaponInfo.maxAmmo = lifeTimeTicks;
	}

	auto infernos = Entity::Get("C_Inferno");
	for (auto inferno : infernos)
	{
		auto infernoEntity = inferno->As<C_Inferno>();

		int handle = Entity::GetEntityHandle(inferno->As<C_CSPlayerPawn>());
		auto weaponPtr = weaponMap.find(handle);

		if (weaponPtr == weaponMap.end())
		{
			weaponMap.insert_or_assign(handle, WeaponInfo{});
			continue;
		}

		auto vecOrigin = infernoEntity->m_pGameSceneNode()->m_vecOrigin();

		Vector screenOrigin;

		auto& weaponInfo = weaponPtr->second;
		weaponInfo.valid = true;
		weaponInfo.handle = handle;
		weaponInfo.fireRange = 152.f;
		weaponInfo.infernoPos = std::move(GetWorldPosition(vecOrigin, weaponInfo.fireRange));

		auto& bBox = weaponInfo.box;
		bBox.found = Render::WorldToScreen(vecOrigin, screenOrigin);
		bBox.x = screenOrigin.x - NADE_TIMER_WIDTH;
		bBox.y = screenOrigin.y;
		bBox.w = NADE_TIMER_WIDTH;
		bBox.h = 4.f;

		if (isAlive)
		{
			float distance = origin.Dist(vecOrigin);
			weaponInfo.alpha = 255.f - std::clamp((255.f * distance) / MAX_NADE_DISTANCE, 0.f, 255.f);
		}
		else
			weaponInfo.alpha = 0.f;

		auto curtimeTick = TIME_TO_TICKS(Interfaces::globalVars->curTime);
		auto infernoTickBegin = infernoEntity->m_nFireEffectTickBegin();
		auto timeElapsed = TICKS_TO_TIME(std::abs(infernoTickBegin - curtimeTick));

		weaponInfo.name = "INFERNO";
		weaponInfo.isMolotov = true;
		weaponInfo.expireTime = timeElapsed;
		weaponInfo.lifeTime = infernoEntity->m_nFireLifetime();
		
		auto lifeTimeTicks = TIME_TO_TICKS(weaponInfo.lifeTime);
		auto expireTimeTicks = TIME_TO_TICKS(weaponInfo.expireTime);

		// just a lifehack to not to add extra variables for molotov
		// looks like ghetto
		// @opai
		weaponInfo.ammo = lifeTimeTicks - expireTimeTicks;
		weaponInfo.maxAmmo = lifeTimeTicks;
	}

	for (auto baseEntity : weaponEntities)
	{
		const char* className = baseEntity->GetEntityClassName();
		auto weapon = baseEntity->As<C_BasePlayerWeapon>();
		auto owner = weapon->m_hOwnerEntity().GetEntryIndex();
		if (owner > 0)
			continue;

		int handle = Entity::GetEntityHandle(baseEntity->As<C_CSPlayerPawn>());
		auto weaponPtr = weaponMap.find(handle);

		if (weaponPtr == weaponMap.end())
		{
			weaponMap.insert_or_assign(handle, WeaponInfo{});
			continue;
		}

		auto& weaponInfo = weaponPtr->second;
		if (weaponInfo.isMolotov)
			continue;

		weaponInfo.valid = true;
		weaponInfo.handle = handle;
		weaponInfo.box = GetBox(baseEntity);

		if (isAlive)
		{
			float distance = origin.Dist(baseEntity->m_pGameSceneNode()->m_vecAbsOrigin());
			weaponInfo.alpha = 255.f - std::clamp((255.f * distance) / MAX_DISTANCE, 0.f, 255.f);
		}
		else
			weaponInfo.alpha = 0.f;

		auto weaponData = weapon->GetWeaponData();
		if (weaponData)
		{
			weaponInfo.ammo = weapon->m_iClip1();
			weaponInfo.maxAmmo = weaponData->m_iMaxClip1();

			const char* m_szName = weaponData->m_szName();
			const char* nameLen = strstr(m_szName, "weapon_");
			std::string weaponName = nameLen ? nameLen + strlen("weapon_") : m_szName;
			std::transform(weaponName.begin(), weaponName.end(), weaponName.begin(), ::toupper);

			weaponInfo.name = std::move(weaponName);
		}
	}
}

void Visuals::Weapons::Run()
{
	const std::unique_lock<std::mutex> m(weaponMutex);

	for (auto it = weaponMap.begin(); it != weaponMap.end(); it = std::next(it))
	{
		auto& weaponInfo = it->second;
		if (!weaponInfo.valid || weaponInfo.alpha <= 0.f)
			continue;
		
		if (weaponInfo.isMolotov || weaponInfo.isSmoke)
		{
			if (weaponInfo.expireTime >= weaponInfo.lifeTime || weaponInfo.infernoPos.empty())
				continue;

			RenderRadius(weaponInfo);
			
			if (weaponInfo.box.found)
				RenderNameAndAmmo(weaponInfo);

			continue;
		}

		if (weaponInfo.box.found)
		{
			RenderBBox(weaponInfo);
			RenderNameAndAmmo(weaponInfo);
		}
	}
}

void Visuals::Weapons::RenderBBox(WeaponInfo& info)
{
	auto mainColor = ColorRGBA{ 255, 255, 255, info.alpha }.ConvertFromRGBToFloats();
	auto outlineColor = ColorRGBA{ 0, 0, 0, info.alpha }.ConvertFromRGBToFloats();

	Render::RectOutline({ info.box.x - 1, info.box.y - 1 }, { info.box.x + info.box.w + 1, info.box.y + info.box.h + 1 }, outlineColor);
	Render::RectOutline({ info.box.x + 1, info.box.y + 1 }, { info.box.x + info.box.w - 1, info.box.y + info.box.h - 1 }, outlineColor);
	Render::RectOutline({ info.box.x, info.box.y }, { info.box.x + info.box.w, info.box.y + info.box.h }, mainColor);
}

void Visuals::Weapons::RenderNameAndAmmo(WeaponInfo& info)
{
	auto mainColor = ColorRGBA{ 255, 255, 255, info.alpha }.ConvertFromRGBToFloats();
	auto outlineColor = ColorRGBA{ 0, 0, 0, info.alpha }.ConvertFromRGBToFloats();

	ColorRGBA fullAmmoColor;
	ColorRGBA lowAmmoColor;

	if (info.isMolotov)
	{
		fullAmmoColor = ColorRGBA{ 242, 127, 104, info.alpha };
		lowAmmoColor = ColorRGBA{ 242, 104, 104, info.alpha };
	}
	else if (info.isSmoke)
	{
		fullAmmoColor = ColorRGBA{ 173, 195, 255, info.alpha };
		lowAmmoColor = ColorRGBA{ 203, 173, 255, info.alpha };
	}
	else
	{
		fullAmmoColor = ColorRGBA{ 170, 185, 250, info.alpha };
		lowAmmoColor = ColorRGBA{ 255, 33, 33, info.alpha };
	}

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
		Render::fonts.onetapPixel, info.name, Render::fonts.onetapPixel->FontSize);
}

void Visuals::Weapons::RenderRadius(WeaponInfo& info)
{
	auto oldFlags = Render::backgroundDrawList->Flags;
	Render::backgroundDrawList->Flags |= ImDrawListFlags_AntiAliasedLines;

	float espStep = std::clamp(static_cast<float>(info.ammo) / static_cast<float>(info.maxAmmo), 0.f, 1.f);

	ColorRGBA fullAmmoColor;
	ColorRGBA lowAmmoColor;

	if (info.isMolotov)
	{
		fullAmmoColor = ColorRGBA{ 242, 127, 104, info.alpha };
		lowAmmoColor = ColorRGBA{ 242, 104, 104, info.alpha };
	}
	else 
	{
		fullAmmoColor = ColorRGBA{ 173, 195, 255, info.alpha };
		lowAmmoColor = ColorRGBA{ 203, 173, 255, info.alpha };
	}

	auto lerpedColor = lowAmmoColor.Lerp(fullAmmoColor, espStep).ConvertFromRGBToFloats();

	Render::backgroundDrawList->AddPolyline(info.infernoPos.data(), info.infernoPos.size(), lerpedColor.im(), 0, 1.5f);

	Render::backgroundDrawList->Flags = oldFlags;
}