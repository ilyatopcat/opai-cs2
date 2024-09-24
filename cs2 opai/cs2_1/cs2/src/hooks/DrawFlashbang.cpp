#include "hooks.h"

void* Hooks::DrawFlashbang::Hook(C_CSPlayerPawn* pPlayerPawn) {
    IS_UNINITIALIZED(pPlayerPawn);

    if (config.removals & REMOVALS_FLASHBANG)
        pPlayerPawn->m_flFlashDuration() = 0;

    return Original(pPlayerPawn);
}