#pragma once

#include "CGameEntitySystem.h"

class GameResourceServiceClientV001 {
private:
	char pad_0000[0x58];
public:
	CGameEntitySystem* pGameEntitySystem;
};