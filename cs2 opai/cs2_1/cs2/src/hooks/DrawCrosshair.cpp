#include "hooks.h"

bool Hooks::DrawCrosshair::Hook(C_CSWeaponBaseGun* pWeaponBaseGun) {
    IS_UNINITIALIZED(pWeaponBaseGun);

    if (!config.forceCrosshair)
        return Original(pWeaponBaseGun);

    C_CSPlayerPawn* pLocalPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!pLocalPlayerPawn)
        return Original(pWeaponBaseGun);

    return !pLocalPlayerPawn->m_bIsScoped();
}