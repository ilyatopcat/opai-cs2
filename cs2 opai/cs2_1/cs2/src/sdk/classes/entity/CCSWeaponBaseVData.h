#pragma once

#include "../../schema/schema.h"
#include <memory>

enum CSWeaponType : uint32_t
{
	WEAPONTYPE_KNIFE = 0x0,
	WEAPONTYPE_PISTOL = 0x1,
	WEAPONTYPE_SUBMACHINEGUN = 0x2,
	WEAPONTYPE_RIFLE = 0x3,
	WEAPONTYPE_SHOTGUN = 0x4,
	WEAPONTYPE_SNIPER_RIFLE = 0x5,
	WEAPONTYPE_MACHINEGUN = 0x6,
	WEAPONTYPE_C4 = 0x7,
	WEAPONTYPE_TASER = 0x8,
	WEAPONTYPE_GRENADE = 0x9,
	WEAPONTYPE_EQUIPMENT = 0xa,
	WEAPONTYPE_STACKABLEITEM = 0xb,
	WEAPONTYPE_FISTS = 0xc,
	WEAPONTYPE_BREACHCHARGE = 0xd,
	WEAPONTYPE_BUMPMINE = 0xe,
	WEAPONTYPE_TABLET = 0xf,
	WEAPONTYPE_MELEE = 0x10,
	WEAPONTYPE_SHIELD = 0x11,
	WEAPONTYPE_ZONE_REPULSOR = 0x12,
	WEAPONTYPE_UNKNOWN = 0x13,
};

using CFiringFloat_t = float[2];

class CCSWeaponBaseVData
{
public:
	SCHEMA(m_iMaxClip1, int32_t, "CBasePlayerWeaponVData", "m_iMaxClip1");
	SCHEMA(m_iMaxClip2, int32_t, "CBasePlayerWeaponVData", "m_iMaxClip2");
	SCHEMA(m_iDefaultClip1, int32_t, "CBasePlayerWeaponVData", "m_iDefaultClip1");
	SCHEMA(m_iDefaultClip2, int32_t, "CBasePlayerWeaponVData", "m_iDefaultClip2");
	SCHEMA(m_iWeight, int32_t, "CBasePlayerWeaponVData", "m_iWeight");
	SCHEMA(m_szName, const char*, "CCSWeaponBaseVData", "m_szName");
	SCHEMA(m_flCycleTime, CFiringFloat_t, "CCSWeaponBaseVData", "m_flCycleTime");
	SCHEMA(m_nDamage, int, "CCSWeaponBaseVData", "m_nDamage");
	SCHEMA(m_flArmorRatio, float, "CCSWeaponBaseVData", "m_flArmorRatio");
	SCHEMA(m_flRange, float, "CCSWeaponBaseVData", "m_flRange");
	SCHEMA(m_flRangeModifier, float, "CCSWeaponBaseVData", "m_flRangeModifier");
	SCHEMA(m_flPenetration, float, "CCSWeaponBaseVData", "m_flPenetration");
	SCHEMA(m_flHeadshotMultiplier, float, "CCSWeaponBaseVData", "m_flHeadshotMultiplier");
	SCHEMA(m_flSpread, float, "CCSWeaponBaseVData", "m_flSpread");
	SCHEMA(m_nNumBullets, float, "CCSWeaponBaseVData", "m_nNumBullets");
	SCHEMA(m_WeaponType, int, "CCSWeaponBaseVData", "m_WeaponType");
};