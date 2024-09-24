#pragma once

#include "../config/config.h"

#include "../../sdk/entity/entity.h"

#include "../../sdk/classes/CCSGOInput.h"
#include "../../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../../sdk/math/math.h"
#include "../../sdk/interfaces/interfaces.h"

#include <Windows.h>
#include <stdio.h>
#include <cstdio>
#include <cstdint>

enum EStrafeDirection
{
	STRAFE_FORWARDS = 0,
	STRAFE_BACKWARDS = 180,
	STRAFE_LEFT = 90,
	STRAFE_RIGHT = -90,
	STRAFE_BACK_LEFT = 135,
	STRAFE_BACK_RIGHT = -135
};

namespace Misc {
	namespace Movement {
		inline int scrolls{ };
		inline bool sweitcher = true;
		inline int maxScrolls{ };

		void BunnyHop(CUserCmd*, C_CSPlayerPawn*);
		void Strafer(CUserCmd*, CBaseUserCmdPB*, Vector&);
		void FixMovement(CUserCmd* , CBaseUserCmdPB* baseUserCmd, C_CSPlayerPawn* localPlayerPawn, Vector oldAngle);
	}

	void PVSUpdate(CEntityInstance*);
}