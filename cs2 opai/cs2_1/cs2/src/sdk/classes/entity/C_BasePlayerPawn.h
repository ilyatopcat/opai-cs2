#pragma once

#include "../CPlayer_CameraServices.h"
#include "../CPlayer_WeaponServices.h"
#include "C_BaseCombatCharacter.h"

#include "../../schema/schema.h"

class C_BasePlayerPawn : public C_BaseCombatCharacter {
public:
	SCHEMA(m_pCameraServices, CPlayer_CameraServices*, "C_BasePlayerPawn", "m_pCameraServices");
	SCHEMA(m_pWeaponServices, CPlayer_WeaponServices*, "C_BasePlayerPawn", "m_pWeaponServices");
};