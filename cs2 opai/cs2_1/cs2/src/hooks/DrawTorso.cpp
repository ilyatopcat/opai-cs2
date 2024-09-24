#include "hooks.h"

bool Hooks::DrawTorso::Hook(C_CSPlayerPawn* pPlayerPawn) {
    IS_UNINITIALIZED(pPlayerPawn);

    if (!(config.removals & REMOVALS_TORSO))
        return Original(pPlayerPawn);

    C_CSPlayerPawn* pLocalPlayerPawn = Entity::GetLocalPlayerPawn();

    if (pLocalPlayerPawn != pPlayerPawn)
        return Original(pPlayerPawn);

    return Interfaces::input->m_bInThirdPerson;
}