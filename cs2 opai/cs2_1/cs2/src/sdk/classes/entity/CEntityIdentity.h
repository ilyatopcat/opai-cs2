#pragma once

#include "../../schema/schema.h"
#include "../../math/CBaseHandle.h"

class CEntityIdentity {
public:
	SCHEMA(m_name, const char*, "CEntityIdentity", "m_name");
	SCHEMA(m_designerName, const char*, "CEntityIdentity", "m_designerName");
	SCHEMA(m_flags, std::uint32_t, "CEntityIdentity", "m_flags");

	 bool IsValid()
	{
		return m_iIndex() != INVALID_EHANDLE_INDEX;
	}

	int GetEntryIndex()
	{
		if (!IsValid())
			return ENT_ENTRY_MASK;

		return m_iIndex() & ENT_ENTRY_MASK;
	}

	int GetSerialNumber()
	{
		return m_iIndex() >> NUM_SERIAL_NUM_SHIFT_BITS;
	}

	OFFSET(int, m_iIndex, 0x10);
};