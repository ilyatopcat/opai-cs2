#include "misc.h"

void Misc::PVSUpdate(CEntityInstance* pEntityInstance) {
    if (!pEntityInstance->IsPlayerPawn())
        return;

    C_CSPlayerPawn* localPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!localPlayerPawn)
        return;

    C_CSPlayerPawn* playerPawn = pEntityInstance->As<C_CSPlayerPawn>();
    if (!playerPawn)
        return;

    int localPlayerTeamNum = localPlayerPawn->m_iTeamNum();
    int playerTeamNum = playerPawn->m_iTeamNum();

    if (localPlayerTeamNum == playerTeamNum)
        return;

    pEntityInstance->m_bVisibleinPVS() = true;
}