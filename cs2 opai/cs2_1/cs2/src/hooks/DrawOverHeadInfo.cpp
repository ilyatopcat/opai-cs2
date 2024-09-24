#include "hooks.h"

bool Hooks::DrawOverHeadInfo::Hook(C_CSPlayerPawn* pPlayerPawn) {
    IS_UNINITIALIZED(pPlayerPawn);

    if (!config.players.localplayer.disableOverHeadInfo)
        return Original(pPlayerPawn);

    if (pPlayerPawn == Entity::GetLocalPlayerPawn())
        return false;

    return Original(pPlayerPawn);
}