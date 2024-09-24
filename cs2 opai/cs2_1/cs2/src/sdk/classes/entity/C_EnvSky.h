#pragma once

#include "C_BaseModelEntity.h"

#include "../../schema/schema.h"
#include "../../math/Color.h"

class C_EnvSky : public C_BaseModelEntity {
public:
	SCHEMA(m_vTintColor, ByteColorRGB, "C_EnvSky", "m_vTintColor")
	SCHEMA(m_flBrightnessScale, float, "C_EnvSky", "m_flBrightnessScale");
	SCHEMA(m_nFogType, int, "C_EnvSky", "m_nFogType");
};