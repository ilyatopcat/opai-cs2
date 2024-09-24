#include "CHandle.h"

#include "../../interfaces/interfaces.h"

#include <iostream>

void* CHandle::GetBaseEntity() {
	static CGameEntitySystem* gameEntitySystem = Interfaces::gameResourceService->pGameEntitySystem;

	return gameEntitySystem->GetBaseEntity(index & 0x7FFF);
}