#pragma once

#include "../entity/CEntityInstance.h"

class CGameEntitySystem {
public:
	int GetHighestEntityIndex();

	CEntityInstance* GetBaseEntity(int);
	void* GetEntityIndex(int);
};