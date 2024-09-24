#pragma once

#include "../../../utils/vmt.h"

class ILocalize
{
public:
	const char* FindSafe(const char* token_name)
	{
		return CALL_VIRTUAL(this, const char*, 17, token_name);
	}
};