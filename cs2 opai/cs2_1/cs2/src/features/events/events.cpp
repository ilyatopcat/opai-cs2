#include "events.h"

void CEvents::Intilization()
{
	Interfaces::gameEventManager->AddListeners(this, "player_hurt", false);
	if (!Interfaces::gameEventManager->FindListener(this, "player_hurt"))
		return;

	Interfaces::gameEventManager->AddListeners(this, "player_death", false);
	if (!Interfaces::gameEventManager->FindListener(this, "player_death"))
		return;

	Interfaces::gameEventManager->AddListeners(this, "add_bullet_hit_marker", false);
	if (!Interfaces::gameEventManager->FindListener(this, "add_bullet_hit_marker"))
		return;

	Interfaces::gameEventManager->AddListeners(this, "bullet_impact", false);
	if (!Interfaces::gameEventManager->FindListener(this, "bullet_impact"))
		return;

	Interfaces::gameEventManager->AddListeners(this, "round_start", false);
	if (!Interfaces::gameEventManager->FindListener(this, "round_start"))
		return;

	Interfaces::gameEventManager->AddListeners(this, "weapon_fire", false);
	if (!Interfaces::gameEventManager->FindListener(this, "weapon_fire"))
		return;
}

void CEvents::FireGameEvent(CGameEvent* event)
{
	std::string name = event->GetName();

	if (name.find("bullet_impact") != std::string::npos)
		OnBulletImpact(event);
}

void CEvents::OnBulletImpact(CGameEvent* event)
{
	C_CSPlayerPawn* localPlayerPawn = Entity::GetLocalPlayerPawn();
	if (!localPlayerPawn)
		return;

	auto player = event->GetEventHelper().GetPlayerController();
	auto position = Vector(event->GetFloat2("x", 0), event->GetFloat2("y", 0), event->GetFloat2("z", 0));

	Visuals::WorldModulation::ProcessTracers(localPlayerPawn->GetEyePosition(), position, (config.world_modulation.bulletColor * 255));
}