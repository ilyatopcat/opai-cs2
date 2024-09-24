#pragma once

#include "entity/CHandle.h"

#include "../math/Vector.h"
#include "../schema/schema.h"

class CCSPlayer_MovementServices
{
public:
	SCHEMA(m_flDuckAmount, float, "CCSPlayer_MovementServices", "m_flDuckAmount");
};