#include "hooks.h"

void Hooks::FrameStageNotify::Hook(void* ptr, int stage) {
	IS_UNINITIALIZED(ptr, stage);

	Original(ptr, stage);

	switch (stage)
	{
	case FRAME_NET_UPDATE_POST_DATA_UPDATE_START:
	{
		SkinChanger::Knifes::Init(stage);
	}
	break;
	case FRAME_NET_UPDATE_POST_DATA_UPDATE_END: {
		SkinChanger::Agents::Init(stage);
		SkinChanger::Knifes::Init(stage);
	}
	break;
	case FRAME_SIMULATE_END: {
		Visuals::Players::Store();
		Visuals::Weapons::Store();
		Lagcompensation::Run();
		break;
	}
	}
}