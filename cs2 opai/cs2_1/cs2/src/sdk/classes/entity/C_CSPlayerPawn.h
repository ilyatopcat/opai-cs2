#pragma once

#include "C_CSPlayerPawnBase.h"
#include "../CPlayer_WeaponServices.h"

#include "../../schema/schema.h"
#include "../../math/Vector.h"
#include "../CUtlVector.h"

#define	FL_ONGROUND				(1 << 0)
#define FL_DUCKING				(1 << 1)
#define	FL_WATERJUMP			(1 << 3)
#define FL_ONTRAIN				(1 << 4)
#define FL_INRAIN				(1 << 5)
#define FL_FROZEN				(1 << 6)
#define FL_ATCONTROLS			(1 << 7)
#define	FL_CLIENT				(1 << 8)
#define FL_FAKECLIENT			(1 << 9)
#define	FL_INWATER				(1 << 10)
#define FL_HIDEHUD_SCOPE		(1 << 11)

class EntitySpottedState_t {
private:
	char pad0000[0x8]; // 0x0
public:
	bool m_bSpotted; // 0x8	
private:
	char pad0009[0x3]; // 0x9
public:
	unsigned int m_bSpottedByMask[2]; // 0xc	
};

struct CBulletInfo
{

	CBulletInfo()
	{
		position = Vector(0, 0, 0);
		time_stamp = 0;
		expire_time = -1;
	}

	CBulletInfo(Vector position, float time_stamp, float expire_time)
	{
		position = position;
		time_stamp = time_stamp;
		expire_time = expire_time;
	}

	Vector	position;
	float	time_stamp;
	float	expire_time;
};

class CBulletService
{
public:
	int BulletCount()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x48);
	}
	CUtlVector<CBulletInfo>& BulletData()
	{
		return *reinterpret_cast<CUtlVector<CBulletInfo>*>(uintptr_t(this) + 0x48);
	}
};

class C_CSPlayerPawn : public C_CSPlayerPawnBase {
public:
	SCHEMA(m_aimPunchCache, CUtlVector<Vector>, "C_CSPlayerPawn", "m_aimPunchCache");
	SCHEMA(m_bIsScoped, bool, "C_CSPlayerPawn", "m_bIsScoped");

	SCHEMA(m_vHeadConstraintOffset, Vector, "C_CSPlayerPawn", "m_vHeadConstraintOffset");

	SCHEMA(m_fSimulationTime, float, "C_BaseEntity", "m_flSimulationTime");

	SCHEMA(m_entitySpottedState, EntitySpottedState_t, "C_CSPlayerPawn", "m_entitySpottedState");

	SCHEMA(m_pBulletServices, CBulletService*, "C_CSPlayerPawn", "m_pBulletServices");

	SCHEMA(m_bWaitForNoAttack, bool, "C_CSPlayerPawn", "m_bWaitForNoAttack");

	SCHEMA(m_EconGloves, C_EconItemView, "C_CSPlayerPawn", "m_EconGloves");

	SCHEMA(m_bNeedToReApplyGloves, bool, "C_CSPlayerPawn", "m_bNeedToReApplyGloves");

	Vector GetEyePosition();
	Vector GetOriginPosition();
	Vector GetBonePosition(int);

	bool IsVisible(C_CSPlayerPawn* pPawn, Vector vecPoint);

	std::uint32_t GetOwnerHandleIndex()
	{
		std::uint32_t Result = -1;
		if (this && m_pCollision() && !(m_pCollision()->m_usSolidFlags() & 4))
			Result = this->m_hOwnerEntity().GetEntryIndex();

		return Result;
	}

	CHitboxsets* GetHitboxSets(unsigned int hitboxSetIndex);

	C_BasePlayerWeapon* GetActiveWeapon();

	bool IsAlive();
	int GetBoneIndex(const char* name);
};