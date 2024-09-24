#include "hooks.h"

#include "../sdk/interfaces/interfaces.h"

#include "../features/menu/menu.h"

void* Hooks::EnableCursor::Hook(void* pInputSystem, bool active) {
    EnableCursorLastActive = active;

    if (Menu::isOpen)
        active = false;

    return Original(pInputSystem, active);
}

void Hooks::EnableCursor::UnHook() {
    Original(Interfaces::inputSystem, EnableCursorLastActive);
}