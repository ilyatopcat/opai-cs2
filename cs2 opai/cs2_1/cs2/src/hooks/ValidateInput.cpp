#include "hooks.h"

void Hooks::ValidateInput::Hook(CCSGOInput* pInput, int a2) {
    IS_UNINITIALIZED(pInput, a2);

    Vector vecViewAngles = pInput->m_vecViewAngles;

    Original(pInput, a2);

    pInput->m_vecViewAngles = vecViewAngles;
}