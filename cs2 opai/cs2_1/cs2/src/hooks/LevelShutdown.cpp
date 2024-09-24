#include "hooks.h"

void* Hooks::LevelShutdown::Hook(void* pClientModeShared) {
    IS_UNINITIALIZED(pClientModeShared);

    Entity::LevelShutdown();

    Interfaces::particleSystem = nullptr;
    Interfaces::particleManager = nullptr;
    Interfaces::globalVars = nullptr;

    return Original(pClientModeShared);
}