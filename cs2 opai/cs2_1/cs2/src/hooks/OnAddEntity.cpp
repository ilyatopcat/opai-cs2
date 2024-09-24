#include "hooks.h"

void* Hooks::OnAddEntity::Hook(void* pGameEntitySystem, CEntityInstance* pEntityInstance, int handle) {
    IS_UNINITIALIZED(pGameEntitySystem, pEntityInstance, handle);

    Entity::AddEntity(pEntityInstance, handle);

    return Original(pGameEntitySystem, pEntityInstance, handle);
}