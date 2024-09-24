#pragma once
#include "CCSWeaponBaseVData.h"
#include "C_BasePlayerWeapon.h"
#include "C_BaseFlex.h"

#include "../../schema/schema.h"

class C_BaseGrenade : public C_BaseFlex
{
public:
};

class C_BaseCSGrenadeProjectile : public C_BaseGrenade
{
public:

};

class C_SmokeGrenadeProjectile : public C_BaseCSGrenadeProjectile
{
public:
	SCHEMA(m_nSmokeEffectTickBegin, int, "C_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin");
	SCHEMA(m_bSmokeEffectSpawned, bool, "C_SmokeGrenadeProjectile", "m_bSmokeEffectSpawned");
};