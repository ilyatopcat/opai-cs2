#pragma once

#include "entity/CHandle.h"

#include "../math/Vector.h"
#include "../schema/schema.h"

class CPlayer_CameraServices {
public:
	SCHEMA(m_hActivePostProcessingVolume, CHandle, "CPlayer_CameraServices", "m_hActivePostProcessingVolume");
	SCHEMA(m_vecCsViewPunchAngle, Vector, "CPlayer_CameraServices", "m_vecCsViewPunchAngle");
};