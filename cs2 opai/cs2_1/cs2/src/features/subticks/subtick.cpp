#include "subtick.h"

void Subticks::Store(CCSGOInput* input, CCSInputMoves* input_moves) {
	subtick_count = input->m_iSubtickCount;

	for (auto i = 0; i < subtick_count; i++) {
		auto subtick_moves = &input->m_aSubtickMoves[i];
		if (!subtick_moves)
			continue;

		auto subticks = &g_Subtick[i];
		subticks->m_bPressed = subtick_moves->pressed;
		subticks->m_flWhen = subtick_moves->when;
		subticks->m_uButton = subtick_moves->button;
		subticks->m_flLeftMove = input_moves->m_flSideMove;
		subticks->m_flForwardMove = input_moves->m_flForwardMove;
	}
}

void Subticks::Restore(CCSGOInput* input, CCSInputMoves* input_moves) {
	input->m_iSubtickCount = subtick_count;

	for (auto i = 0; i < subtick_count; i++) {
		auto subtick_moves = &input->m_aSubtickMoves[i];
		if (!subtick_moves)
			continue;

		auto subticks = &g_Subtick[i];
		if (!subticks)
			continue;

		subtick_moves->pressed = subticks->m_bPressed;
		subtick_moves->when = subticks->m_flWhen;
		subtick_moves->button = subticks->m_uButton;
		input_moves->m_flSideMove = subticks->m_flLeftMove;
		input_moves->m_flForwardMove = subticks->m_flForwardMove;
	}
}

void Subticks::Run(CCSGOInput* input, CBaseUserCmdPB* base) {
	auto input_moves = input->m_pInputMoves;
	if (!input_moves)
		return;

	backup_input = input;

	Store(input, input_moves);
	{
		for (auto i = 0; i < subtick_count; i++)
		{
			auto subtick = &g_Subtick[i];
			if (!subtick)
				continue;

			auto subtickMoves = base->AddSubtickMoves();
			if (!subtickMoves)
				continue;

			subtickMoves->SetWhen(subtick->m_flWhen);

			if (subtick->m_bPressed)
			{
				subtickMoves->SetButton(subtick->m_uButton);
				subtickMoves->SetPressed(subtick->m_bPressed);

				subtickMoves->SetWhen(subtick->m_flWhen);
			}
			else
			{
				if (subtick->m_flForwardMove != 0.0)
					subtickMoves->SetAnalogForwardDelta(subtick->m_flForwardMove);

				if (subtick->m_flLeftMove != 0.0)
					subtickMoves->SetAnalogLeftDelta(subtick->m_flLeftMove);
			}
		}
	}
	Restore(input, input_moves);
}

void Subticks::AddSubtick(uint64_t button, bool pressed, float when) {
	for (auto i = 0; i < subtick_count; i++) {
		auto subtick = &g_Subtick[i];
		if (!subtick)
			continue;

		subtick->m_bPressed = pressed;
		subtick->m_flWhen = when;
		subtick->m_uButton = button;
	}
}

void Subticks::AddAction(uint64_t button, CUserCmd* cmd)
{
	AddSubtick(button, true, 0.0f);

	if (button == IN_ATTACK)
	{
		if (backup_input->m_iActiveInputs > 1)
			backup_input->m_pInputMessage[backup_input->m_iActiveInputs - 1].playerTickCount = backup_input->m_pInputMessage->playerTickCount;

		if (backup_input->m_iAttackHistory_1 != -1)
			 cmd->pb.set_attack1_start_history_index(backup_input->m_iAttackHistory_1);

		if (backup_input->m_iAttackHistory_2 != -1)
			cmd->pb.set_attack2_start_history_index(backup_input->m_iAttackHistory_2);

		if (backup_input->m_iAttackHistory_3 != -1)
			cmd->pb.set_attack3_start_history_index(backup_input->m_iAttackHistory_3);

		backup_input->SetAttackFraction(backup_input->GetAttackFraction());
		backup_input->SetAttackTickRatio(backup_input->GetAttackTickRatio());
		backup_input->SetAttackTickPostFireRatio(backup_input->GetAttackTickPostFireRatio());

		cmd->pb.set_attack1_start_history_index(backup_input->m_pInputMessage[backup_input->m_iAttackHistory_1].entryIndexMax);
		cmd->pb.set_attack2_start_history_index(backup_input->m_pInputMessage[backup_input->m_iAttackHistory_2].entryIndexMax);
		cmd->pb.set_attack3_start_history_index(backup_input->m_pInputMessage[backup_input->m_iAttackHistory_3].entryIndexMax);
	}
}