#include "hooks.h"

void Hooks::DrawRadarEntities::Hook(void* a1) {
    IS_UNINITIALIZED(a1);

    if (config.radar)
        *reinterpret_cast<byte*>(reinterpret_cast<uintptr_t>(a1) + 0x12D08) = 1;

    Original(a1);
}