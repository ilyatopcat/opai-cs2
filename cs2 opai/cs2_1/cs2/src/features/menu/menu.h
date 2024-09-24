#pragma once

#include "../../sdk/classes/CCSGOInput.h"

namespace Menu {
	inline bool isOpen = true;
	inline bool isCursorInMenu = false;

	void Render();
	void CreateMove(CUserCmd*);
}