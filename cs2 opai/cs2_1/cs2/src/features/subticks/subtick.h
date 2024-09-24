#pragma once

#include "../config/config.h"

#include "../../sdk/entity/entity.h"

#include "../../sdk/classes/CCSGOInput.h"
#include "../../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../../sdk/math/math.h"
#include "../../sdk/interfaces/interfaces.h"

class CSubtick
{
public:
	float m_flWhen = 0.0f;
	bool m_bPressed = false;
	uint64_t m_uButton = 0;
	float m_flLeftMove = 0.0f;
	float m_flForwardMove = 0.0f;
};

namespace Subticks
{
	inline int subtick_count;
	inline CCSGOInput* backup_input;
	inline CSubtick g_Subtick[12]{};

	void AddSubtick(uint64_t button, bool pressed, float when);
	void AddAction(uint64_t button, CUserCmd* cmd);
	void Store(CCSGOInput* input, CCSInputMoves* input_moves);
	void Restore(CCSGOInput* input, CCSInputMoves* input_moves);
	void Run(CCSGOInput* input, CBaseUserCmdPB* base);
}