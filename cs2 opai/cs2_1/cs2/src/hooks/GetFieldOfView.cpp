#include "hooks.h"

float Hooks::GetFieldOfView::Hook(void* a1) {
    IS_UNINITIALIZED(a1);

    C_CSPlayerPawn* pLocalPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!pLocalPlayerPawn)
        return Original(a1);

    int fieldOfView = config.fieldOfView;

    if (!pLocalPlayerPawn->m_bIsScoped())
        return fieldOfView;

    CPlayer_WeaponServices* pWeaponServices = pLocalPlayerPawn->m_pWeaponServices();
    if (!pWeaponServices)
        return fieldOfView;

    C_CSWeaponBaseGun* pWeapon = pWeaponServices->m_hActiveWeapon().Get<C_CSWeaponBaseGun>();
    if (!pWeapon)
        return fieldOfView;

    int zoomLevel = pWeapon->m_zoomLevel();

    float zoomModifier = config.overrideZoom.forceSecondZoom ? (zoomLevel == 2 ? 0.75 : 0) : (zoomLevel == 1 ? 0.5 : 0.75);

    return fieldOfView - (config.overrideZoom.fieldOfView * zoomModifier);
}