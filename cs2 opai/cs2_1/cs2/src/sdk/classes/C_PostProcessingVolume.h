#pragma once

#include "../schema/schema.h"

class C_PostProcessingVolume {
public:
	SCHEMA(m_bExposureControl, bool, "C_PostProcessingVolume", "m_bExposureControl");
	SCHEMA(m_flMinExposure, float, "C_PostProcessingVolume", "m_flMinExposure");
	SCHEMA(m_flMaxExposure, float, "C_PostProcessingVolume", "m_flMaxExposure");
	SCHEMA(m_flExposureFadeSpeedUp, float, "C_PostProcessingVolume", "m_flExposureFadeSpeedUp");
	SCHEMA(m_flExposureFadeSpeedDown, float, "C_PostProcessingVolume", "m_flExposureFadeSpeedDown");
};