#pragma once

#include "../math/Vector.h"
#include "../math/math.h"

#include <stdint.h>
#include <string>

#include "../../utils/utils.h"
#include "../../sdk/math/CUtlBuffer.h"
#include "../../utils/vmt.h"

class CNetworkClient
{
public:
	int GetClientTick()
	{
		return CALL_VIRTUAL(this, int, 5);
	}
	int GetServerTick()
	{
		return CALL_VIRTUAL(this, int, 6);
	}

	const char* GetMapName()
	{
		return *reinterpret_cast<const char**>(reinterpret_cast<std::uintptr_t>(this) + 0x240);
	}

	bool IsConnected()
	{
		return std::string_view{ GetMapName() }.find("maps/<empty>.vpk")
			== std::string::npos;
	}

	OFFSET(int, GetSignonState, 0x260);
};

class CNetworkClientService
{
public:
	CNetworkClient* GetNetworkClient()
	{
		return CALL_VIRTUAL(this, CNetworkClient*, 23);
	}
};