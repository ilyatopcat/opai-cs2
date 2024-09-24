#pragma once

#include "entity/CHandle.h"

#include "../schema/schema.h"
#include "../../utils/vmt.h"

class CEconItemDefinition;

class C_EconItemView
{
public:
	SCHEMA(m_iItemDefinitionIndex, uint16_t, "C_EconItemView", "m_iItemDefinitionIndex");
	SCHEMA(m_iItemID, uint64_t, "C_EconItemView", "m_iItemID");
	SCHEMA(m_iItemIDLow, uint32_t, "C_EconItemView", "m_iItemIDLow");
	SCHEMA(m_iItemIDHigh, uint32_t, "C_EconItemView", "m_iItemIDHigh");
	SCHEMA(m_iAccountID, uint32_t, "C_EconItemView", "m_iAccountID");
	SCHEMA(m_bInitialized, bool, "C_EconItemView", "m_bInitialized");
	SCHEMA(m_szCustomName, const char*, "C_EconItemView", "m_szCustomName");
	SCHEMA(m_szCustomNameOverride, const char*, "C_EconItemView", "m_szCustomNameOverride");

	auto GetCustomPaintKitIndex() { return CALL_VIRTUAL(this, int, 2); }

	CEconItemDefinition* GetStaticData() {
		return CALL_VIRTUAL(this, CEconItemDefinition*, 13);
	}
};

class C_AttributeContainer
{
public:
	SCHEMA_ARRAY(m_Item, C_EconItemView, "C_AttributeContainer", "m_Item");
};

class CCSPlayer_WeaponServices
{
public:
	SCHEMA(m_flNextAttack, float, "CCSPlayer_WeaponServices", "m_flNextAttack");
	SCHEMA(m_bIsLookingAtWeapon, bool, "CCSPlayer_WeaponServices", "m_bIsLookingAtWeapon");
	SCHEMA(m_bIsHoldingLookAtWeapon, bool, "CCSPlayer_WeaponServices", "m_bIsHoldingLookAtWeapon");
};

class CPlayer_WeaponServices {
public:
	SCHEMA(m_hActiveWeapon, CHandle, "CPlayer_WeaponServices", "m_hActiveWeapon");
	SCHEMA(m_hLastWeapon, CHandle, "CPlayer_WeaponServices", "m_hLastWeapon");
	SCHEMA(m_hMyWeapons, C_NetworkUtlVectorBase<CHandle>, "CPlayer_WeaponServices", "m_hMyWeapons");

	OFFSET(float, m_flNextAttack, 0xC0);
};