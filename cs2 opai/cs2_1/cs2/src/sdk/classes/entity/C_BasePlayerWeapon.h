#pragma once

#include "../../schema/schema.h"
#include "C_EconEntity.h"
#include "CCSWeaponBaseVData.h"

enum ItemDefinitionIndex_t : short
{
	WEAPON_DEAGLE = 1,
	WEAPON_DUAL_BERETTAS = 2,
	WEAPON_FIVE_SEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP = 24,
	WEAPON_MP5SD = 23,
	WEAPON_XM1024 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCDENDIARY = 48,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_M4A1_S = 60,
	WEAPON_USP_S = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFECSS = 503,
	WEAPON_KNIFEFLIP = 505,
	WEAPON_KNIFEGUT = 506,
	WEAPON_KNIFEKARAMBIT = 507,
	WEAPON_KNIFEM9BAYONET = 508,
	WEAPON_KNIFETACTICAL = 509,
	WEAPON_KNIFEFALCHION = 512,
	WEAPON_KNIFESURVIVALBOWIE = 514,
	WEAPON_KNIFEBUTTERFLY = 515,
	WEAPON_KNIFEPUSH = 516,
	WEAPON_KNIFECORD = 517,
	WEAPON_KNIFECANIS = 518,
	WEAPON_KNIFEURSUS = 519,
	WEAPON_KNIFEGYPSYJACKKNIFE = 520,
	WEAPON_KNIFEOUTDOOR = 521,
	WEAPON_KNIFESTILETTO = 522,
	WEAPON_KNIFEWIDOWMAKER = 523,
	WEAPON_KNIFESKELETON = 525,
	WEAPON_KNIFEKUKRI = 526,
};

class C_BasePlayerWeapon : public C_EconEntity
{
public:
	SCHEMA(m_nNextPrimaryAttackTick, int32_t, "C_BasePlayerWeapon", "m_nNextPrimaryAttackTick");
	SCHEMA(m_flNextPrimaryAttackTickRatio, float, "C_BasePlayerWeapon", "m_flNextPrimaryAttackTickRatio");
	SCHEMA(m_nNextSecondaryAttackTick, int32_t, "C_BasePlayerWeapon", "m_nNextSecondaryAttackTick");
	SCHEMA(m_flNextSecondaryAttackTickRatio, float, "C_BasePlayerWeapon", "m_flNextSecondaryAttackTickRatio");
	SCHEMA(m_iClip1, int32_t, "C_BasePlayerWeapon", "m_iClip1");
	SCHEMA(m_iClip2, int32_t, "C_BasePlayerWeapon", "m_iClip2");

	SCHEMA(m_bInReload, bool, "C_CSWeaponBase", "m_bInReload");

	CCSWeaponBaseVData* GetWeaponData();	
	void UpdateCompositeMaterial(bool should_update);
	void RegenerateWeaponSkin();
};