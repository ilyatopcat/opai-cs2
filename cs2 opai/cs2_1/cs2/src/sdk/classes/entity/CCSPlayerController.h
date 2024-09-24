#pragma once

#include "../../schema/schema.h"

#include "CBasePlayerController.h"

class CCSPlayerController : public CBasePlayerController {
public:
	SCHEMA(m_sSanitizedPlayerName, const char*, "CCSPlayerController", "m_sSanitizedPlayerName");
	SCHEMA(m_nTickBase, uint32_t, "CBasePlayerController", "m_nTickBase");
};