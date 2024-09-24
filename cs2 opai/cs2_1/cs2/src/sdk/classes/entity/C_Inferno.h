#pragma once
#include "CCSWeaponBaseVData.h"
#include "C_BasePlayerWeapon.h"

#include "../../schema/schema.h"

class C_Inferno : public C_BaseModelEntity
{
public:
	SCHEMA(m_nFireLifetime, float, "C_Inferno", "m_nFireLifetime");
	SCHEMA(m_nFireEffectTickBegin, int, "C_Inferno", "m_nFireEffectTickBegin");
};