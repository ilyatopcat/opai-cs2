#include "hooks.h"

void* Hooks::DrawGlow::Hook(CGlowProperty* glow_property) {
    IS_UNINITIALIZED(glow_property);

    void* result = Original(glow_property);

    CEntityInstance* owner = glow_property->m_hOwner;
    if (!owner->IsPlayerPawn())
        return result;

    C_CSPlayerPawn* player_pawn = owner->As<C_CSPlayerPawn>();
    if (!player_pawn->IsAlive())
        return result;

    C_CSPlayerPawn* local_player_pawn = Entity::GetLocalPlayerPawn();
    if (local_player_pawn && (local_player_pawn == player_pawn || local_player_pawn->m_iTeamNum() == player_pawn->m_iTeamNum()))
        return result;

    glow_property->m_glowColorOverride() = ByteColorRGBA(128, 136, 255, 130);
    glow_property->m_bGlowing() = true;

    return result;
}