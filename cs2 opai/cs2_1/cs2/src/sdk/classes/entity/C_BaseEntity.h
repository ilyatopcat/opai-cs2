#pragma once

#include "CEntityInstance.h"
#include "../CGameSceneNode.h"
#include "../CSkeletonInstance.h"
#include "C_BodyComponent.h"

#include "../../schema/schema.h"

class C_Collision {
public:
	SCHEMA(m_vecMins, Vector, "CCollisionProperty", "m_vecMins");
	SCHEMA(m_vecMaxs, Vector, "CCollisionProperty", "m_vecMaxs");

	std::uint16_t CollisionMask()
	{
		return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<std::uintptr_t>(this) + 0x38);
	}

	SCHEMA(m_usSolidFlags, std::uint8_t, "CCollisionProperty", "m_usSolidFlags");
	SCHEMA(m_CollisionGroup, std::uint8_t, "CCollisionProperty", "m_CollisionGroup");
};

class C_BaseEntity : public CEntityInstance {
public:
	SCHEMA(m_iTeamNum, int, "C_BaseEntity", "m_iTeamNum");
	SCHEMA(m_hOwnerEntity, CBaseHandle, "C_BaseEntity", "m_hOwnerEntity");
	SCHEMA(m_pGameSceneNode, CGameSceneNode*, "C_BaseEntity", "m_pGameSceneNode");
	SCHEMA(m_fFlags, int, "C_BaseEntity", "m_fFlags");
	SCHEMA(m_MoveType, int, "C_BaseEntity", "m_MoveType");
	SCHEMA(m_nActualMoveType, int, "C_BaseEntity", "m_nActualMoveType");
	SCHEMA(m_iHealth, int, "C_BaseEntity", "m_iHealth");
	SCHEMA(m_vecAbsVelocity, Vector, "C_BaseEntity", "m_vecAbsVelocity");

	SCHEMA(m_vecVelocity, Vector, "C_BaseEntity", "m_vecVelocity");

	SCHEMA(m_pCollision, C_Collision*, "C_BaseEntity", "m_pCollision");

	SCHEMA(m_CBodyComponent, CBodyComponent*, "C_BaseEntity", "m_CBodyComponent");

	SCHEMA(m_nSubclassID, uint32_t, "C_BaseEntity", "m_nSubclassID");

	void UpdateSubclass();

	bool isWeapon();
};