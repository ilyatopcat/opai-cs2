#pragma once

#include "../../schema/schema.h"

#include "C_BaseEntity.h"
#include "CHandle.h"

class CBasePlayerController : public C_BaseEntity {
public:
	SCHEMA(m_bIsLocalPlayerController, bool, "CBasePlayerController", "m_bIsLocalPlayerController");
	SCHEMA(m_hPawn, CHandle, "CBasePlayerController", "m_hPawn");
};