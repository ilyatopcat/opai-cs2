#pragma once

#include "C_BasePlayerPawn.h"
#include "C_CSWeaponBaseGun.h"
#include "CHandle.h"

#include "../../schema/schema.h"
#include "../CCSPlayer_MovementServices.h"

#include <array>

class C_BaseViewModel : public C_BaseModelEntity
{
public:
	SCHEMA(m_hWeapon, CBaseHandle, "C_BaseViewModel", "m_hWeapon");
};

class CCSPlayer_ViewModelServices
{
public:
	SCHEMA(m_hViewModel, CHandle, "CCSPlayer_ViewModelServices", "m_hViewModel");
};

class C_CSPlayerPawnBase : public C_BasePlayerPawn {
public:
	SCHEMA(m_pMovementServices, CCSPlayer_MovementServices*, "C_BasePlayerPawn", "m_pMovementServices");
	SCHEMA(m_pViewModelServices, CCSPlayer_ViewModelServices*, "C_CSPlayerPawnBase", "m_pViewModelServices");
	SCHEMA(m_hOriginalController, CHandle, "C_CSPlayerPawnBase", "m_hOriginalController");
	//SCHEMA(m_pClippingWeapon, C_CSWeaponBaseGun*, "C_CSPlayerPawnBase", "m_pClippingWeapon")
	SCHEMA(m_flFlashDuration, float, "C_CSPlayerPawnBase", "m_flFlashDuration");
	SCHEMA(m_flLastSpawnTimeIndex, float, "C_CSPlayerPawnBase", "m_flLastSpawnTimeIndex");
	SCHEMA(m_bIsDefusing, bool, "C_CSPlayerPawnBase", "m_bIsDefusing");	
};