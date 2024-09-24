#include "hooks.h"

#include "../features/config/config.h"

void Hooks::DrawScopeOverlay::Hook(void* a1, void* a2) {
    IS_UNINITIALIZED(a1, a2);

    if (config.overrideZoom.overlay == ZOOM_OVERLAY_DEFAULT)
        return Original(a1, a2);
}