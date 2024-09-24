#pragma once

#include "entity/CEntityInstance.h"

#include "../math/Color.h"

#include "../schema/schema.h"

class CGlowProperty {
private:
    char pad_0000[0x18]; // 0x0
public:
    CEntityInstance* m_hOwner;

    SCHEMA(m_glowColorOverride, ByteColorRGBA, "CGlowProperty", "m_glowColorOverride");
    SCHEMA(m_bGlowing, bool, "CGlowProperty", "m_bGlowing");
};