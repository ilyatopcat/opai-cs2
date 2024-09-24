#pragma once

#include "../config/config.h"

#include "../../sdk/entity/entity.h"

#include "../../sdk/classes/CCSGOInput.h"
#include "../../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../../sdk/math/math.h"
#include "../../sdk/interfaces/interfaces.h"

#include "../../features/subticks/subtick.h"

class CAimbot
{
public:
	void AutoPistols(CUserCmd* cmd);
	void Run(CUserCmd* cmd);
};

inline CAimbot* Aimbot = new CAimbot;