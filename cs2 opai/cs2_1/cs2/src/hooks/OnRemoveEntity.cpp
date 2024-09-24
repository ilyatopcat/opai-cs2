#include "hooks.h"

void* Hooks::OnRemoveEntity::Hook(void* pGameEntitySystem, CEntityInstance* pEntityInstance, int handle) {
    IS_UNINITIALIZED(pGameEntitySystem, pEntityInstance, handle);

    Entity::RemoveEntity(pEntityInstance, handle);

    return Original(pGameEntitySystem, pEntityInstance, handle);
}