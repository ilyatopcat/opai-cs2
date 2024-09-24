#include "misc.h"

void Misc::Movement::BunnyHop(CUserCmd* userCmd, C_CSPlayerPawn* localPlayerPawn) {
	if (!config.movement.bunnyHop)
		return;

	if (localPlayerPawn->m_fFlags() & FL_ONGROUND)
		userCmd->buttons.value &= ~IN_JUMP;
}

float CalcualteDelta(float m_speed)
{
	const static float maxSpeed = 300.f;
	const static auto sv_airaccelerate = Interfaces::cvar->GetByName("sv_airaccelerate")->GetFloat();
	const float term = config.movement.autostrafeSmooth / sv_airaccelerate / maxSpeed * 100.0f / m_speed;

	if (term < 1.0f && term > -1.0f)
		return std::acos(term);

	return 0.0f;
};

void Misc::Movement::Strafer(CUserCmd* userCmd, CBaseUserCmdPB* baseUserCmd, Vector& oldAngle) {
    if (!config.movement.autoStrafe)
        return;

    auto localPlayer = Entity::GetLocalPlayerPawn();
	if (!localPlayer)
		return;

	if (localPlayer->m_MoveType() == MOVETYPE_LADDER || localPlayer->m_MoveType() == MOVETYPE_NOCLIP || localPlayer->m_nActualMoveType() == MOVETYPE_LADDER || localPlayer->m_nActualMoveType() == MOVETYPE_NOCLIP)
		return;

    if (localPlayer->m_fFlags() & FL_ONGROUND)
        return;

    if (userCmd->buttons.value & IN_SPEED)
        return;

	const float speed = localPlayer->m_vecVelocity().Length();

	const float deltaInAir = CalcualteDelta(speed);

	if (deltaInAir == 0.0f)
		return;

	float yaw = Math::DEG2RAD(baseUserCmd->viewangles().y());
	auto& vecVelocity = localPlayer->m_vecVelocity();
	float velocityDirection = std::atan2(vecVelocity.y, vecVelocity.x) - yaw;
	float bestAngleMove = std::atan2(baseUserCmd->leftmove(), baseUserCmd->forwardmove());

	float finalDelta = Math::DeltaAngle(velocityDirection, bestAngleMove);
	float finalMove = finalDelta < 0.0f ? velocityDirection + deltaInAir : velocityDirection - deltaInAir;

	baseUserCmd->set_forwardmove(std::cos(finalMove));
	baseUserCmd->set_leftmove(std::sinf(finalMove));
}

void Misc::Movement::FixMovement(CUserCmd* user_cmd, CBaseUserCmdPB* baseUserCmd, C_CSPlayerPawn* localPlayerPawn, Vector oldAngle) {
	Vector direction;
	Vector moveAngle;

	Vector move = Vector(baseUserCmd->forwardmove(), baseUserCmd->leftmove(), 0);

	float length = move.NormilizeMovement();

	if (length == 0.0f)
		return;

	Vector ang = oldAngle;

	Vector eyeAngle = Vector(baseUserCmd->viewangles().x(), baseUserCmd->viewangles().y(), baseUserCmd->viewangles().z());

	Math::VectorAngles(move, moveAngle);

	float delta = (eyeAngle.y - ang.y);
	moveAngle.y += delta;
	Math::AngleVectors(moveAngle, direction);

	if (eyeAngle.x < -90 || eyeAngle.x > 90)
		direction.x = -direction.x;

	baseUserCmd->set_forwardmove(direction.x);
	baseUserCmd->set_leftmove(direction.y);
}