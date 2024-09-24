#pragma once

#include "CCSWeaponBaseVData.h"
#include "C_BasePlayerWeapon.h"

#include "../../schema/schema.h"

class C_CSWeaponBase : public C_BasePlayerWeapon {
public:
	CCSWeaponBaseVData* GetWeaponBaseData();

	void RegenerateWeaponSkin()
	{

	}

	SCHEMA(m_zoomLevel, int, "C_CSWeaponBaseGun", "m_zoomLevel");
};

class C_BaseCSGrenade : public C_CSWeaponBase {
public:
	SCHEMA(m_bPinPulled, bool, "C_BaseCSGrenade", "m_bPinPulled");
	SCHEMA(m_fThrowTime, int, "C_BaseCSGrenade", "m_fThrowTime");
};