#include "hooks.h"

void Hooks::DrawSmokeVolume::Hook(void* thisptr, __int64 a2, __int64 a3, unsigned int a4, __int64 a5, unsigned int* a6) {
    IS_UNINITIALIZED(thisptr, a2, a3, a4, a5, a6);

    if (config.removals & REMOVALS_SMOKE)
        return;

    Original(thisptr, a2, a3, a4, a5, a6);
}