#pragma once

#include "C_BaseModelEntity.h"

class C_AttributeContainer;
class C_EconItemView;	

class C_EconEntity : public C_BaseModelEntity
{
public:
	SCHEMA_ARRAY(m_AttributeManager, C_AttributeContainer, "C_EconEntity", "m_AttributeManager");
	SCHEMA(m_nFallbackPaintKit, int, "C_EconEntity", "m_nFallbackPaintKit");
	SCHEMA(m_nFallbackSeed, int, "C_EconEntity", "m_nFallbackSeed");
	SCHEMA(m_OriginalOwnerXuidLow, uint32_t, "C_EconEntity", "m_OriginalOwnerXuidLow");
	SCHEMA(m_OriginalOwnerXuidHigh, uint32_t, "C_EconEntity", "m_OriginalOwnerXuidHigh");
	SCHEMA(m_flFallbackWear, float, "C_EconEntity", "m_flFallbackWear");
	SCHEMA(m_nFallbackStatTrak, int, "C_EconEntity", "m_nFallbackStatTrak");
	SCHEMA(m_bNeedToReApplyGloves, bool, "C_EconEntity", "m_bNeedToReApplyGloves");
	SCHEMA(m_EconGloves, C_EconItemView, "C_EconEntity", "m_EconGloves");
};