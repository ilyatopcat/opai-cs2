#include "hooks.h"

#include "../features/menu/menu.h"

bool Hooks::MouseInput::Hook(CCSGOInput* pInput) {
    IS_UNINITIALIZED(pInput);

    if (Menu::isOpen)
        return false;

    return Original(pInput);
}