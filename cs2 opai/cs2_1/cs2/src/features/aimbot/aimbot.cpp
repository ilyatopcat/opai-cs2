#include "aimbot.h"

void CAimbot::AutoPistols(CUserCmd* cmd) {
	auto localController = Entity::GetLocalPlayerController();
	if (!localController)
		return;

	auto localPlayer = Entity::GetLocalPlayerPawn();
	if (!localPlayer || !localPlayer->IsAlive())
		return;

	auto activeWeapon = localPlayer->GetActiveWeapon();
	if (!activeWeapon)
		return;

	auto weaponData = activeWeapon->GetWeaponData();
	if (!weaponData)
		return;

	if (activeWeapon->m_iClip1() <= 0)
		return;

	if (localPlayer->m_bWaitForNoAttack())
		return;

	int nextPrimaryTick = activeWeapon->m_nNextPrimaryAttackTick();
	int nextSecondaryTick = activeWeapon->m_nNextSecondaryAttackTick();

	int ticks = localController->m_nTickBase();

	if (ticks < nextPrimaryTick) {
		if (cmd->buttons.value & IN_ATTACK)
			cmd->buttons.value &= ~IN_ATTACK;
	}

	if (ticks < nextSecondaryTick) {
		if (cmd->buttons.value & IN_ATTACK2)
			cmd->buttons.value &= ~IN_ATTACK2;
	}
}

void CAimbot::Run(CUserCmd* cmd)
{
	auto localPlayer = Entity::GetLocalPlayerPawn();

	if (!localPlayer || !localPlayer->IsAlive())
		return;

	const auto& players = Entity::GetPlayers(ENTITY_ENEMIES_ONLY);

	for (auto player_pawn : players)
	{
		if (!player_pawn->IsAlive())
			continue;

		auto hitbox_pos = player_pawn->GetBonePosition(6);

		auto final_angle = Math::AimDirection(localPlayer->GetEyePosition(), hitbox_pos);

		cmd->SetInputAngles(final_angle);
	}
}