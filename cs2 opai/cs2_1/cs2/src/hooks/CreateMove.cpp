#include "hooks.h"
#include <algorithm>

void Hooks::CreateMove::Hook(CCSGOInput* pInput, int a2, int a3) {
    IS_UNINITIALIZED(pInput, a2, a3);

    Original(pInput, a2, a3);

    C_CSPlayerPawn* localPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!localPlayerPawn)
        return;

    CCSPlayerController* localPlayerController = Entity::GetLocalPlayerController();
    if (!localPlayerController)
        return;

    CUserCmd* userCmd = pInput->GetUserCmd();
    if (!userCmd)
        return;

    CBaseUserCmdPB* baseUserCmd = userCmd->pb.mutable_base();
    if (!baseUserCmd)
        return;

    baseUserCmd->clear_subtick_moves();

    auto oldAngle = Vector(baseUserCmd->viewangles().x(), baseUserCmd->viewangles().y(), baseUserCmd->viewangles().z());

    Menu::CreateMove(userCmd);

    Subticks::Run(pInput, baseUserCmd);

    Aimbot->AutoPistols(userCmd);

    Visuals::ThirdPerson();

    //Aimbot->Run(userCmd);

    Misc::Movement::BunnyHop(userCmd, localPlayerPawn);
    Misc::Movement::Strafer(userCmd, baseUserCmd, oldAngle);
    AntiAim::Run(userCmd, localPlayerPawn, baseUserCmd);
    Misc::Movement::FixMovement(userCmd, baseUserCmd, localPlayerPawn, oldAngle);
}