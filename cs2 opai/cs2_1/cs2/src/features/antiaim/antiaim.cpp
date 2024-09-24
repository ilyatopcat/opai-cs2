#include "antiaim.h"

void AntiAim::Run(CUserCmd* cmd, C_CSPlayerPawn* localPlayer, CBaseUserCmdPB* baseUserCmd) {
	if (!localPlayer->IsAlive())
		return;

	if ( localPlayer->m_nActualMoveType() == MOVETYPE_LADDER || localPlayer->m_nActualMoveType() == MOVETYPE_NOCLIP)
		return;

	if (Interfaces::gameRules->m_bFreezePause)
		return;

	if (Interfaces::gameRules->m_iGamePhases == 5)
		return;

	auto activeWeapon = localPlayer->GetActiveWeapon();
	if (!activeWeapon)
		return;

	auto weaponData = activeWeapon->GetWeaponData();
	if (!weaponData)
		return;

	if (weaponData->m_WeaponType() == WEAPONTYPE_GRENADE)
		return;

	auto viewAngle = baseUserCmd->mutable_viewangles();
	if (!viewAngle)
		return;

	viewAngle->set_x(89.f);
	viewAngle->set_y(baseUserCmd->viewangles().y() + 180.f);
}