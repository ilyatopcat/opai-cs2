#include "hooks.h"

bool Hooks::UpdateInPVS::Hook(CEntityInstance* pEntityInstance) {
    IS_UNINITIALIZED(pEntityInstance);

    Misc::PVSUpdate(pEntityInstance);

    return Original(pEntityInstance);
}