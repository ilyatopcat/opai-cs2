#pragma once

#include "entity/CEntityInstance.h"

#include "../math/Color.h"

#include "../schema/schema.h"

class CGameRules
{
public:
	char pad[0x30]; // 0x00
	bool m_bFreezePause; // 0x30
	char pad2[0xB]; // 0x31
	int m_iPause; // 0x3C
	char pad3[0x38]; // 0x40
	int m_iGamePhases; // 0x78
};