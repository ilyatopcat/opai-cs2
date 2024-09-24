#pragma once

#pragma once

#include "../config/config.h"

#include "../../render/render.h"

#include "../../sdk/interfaces/interfaces.h"

#include "../../sdk/entity/entity.h"

#include "../visuals/visuals.h"

class CEvents : public IGameEventListener
{
public:
	void OnBulletImpact(CGameEvent* event);
	void FireGameEvent(CGameEvent* event);
	void Intilization();
	void EmplaceHitData(C_CSPlayerPawn* enity);
	void OnPlayerHurt(CGameEvent* event);
};

inline CEvents* Events = new CEvents();