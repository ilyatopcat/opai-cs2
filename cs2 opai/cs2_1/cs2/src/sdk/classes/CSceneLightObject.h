#pragma once

#include "../math/Color.h"

#include "../schema/schema.h"

class CSceneLightObject {
public:
	char pad_0000[0xE4]; // 0x0
	ColorRGB color; // 0xE4
};