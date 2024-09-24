#pragma once

#include "../config/config.h"

#include "../../sdk/entity/entity.h"

#include "../../sdk/classes/CCSGOInput.h"
#include "../../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../../sdk/math/math.h"
#include "../../sdk/interfaces/interfaces.h"

namespace AntiAim
{
	void Run(CUserCmd* cmd, C_CSPlayerPawn* localPlayer, CBaseUserCmdPB* baseUserCmd);
}