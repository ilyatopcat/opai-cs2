#include "hooks.h"

void* Hooks::UpdatePostProcessing::Hook(C_PostProcessingVolume* pPostProcessingVolume, int a2) {
    IS_UNINITIALIZED(pPostProcessingVolume, a2);

    void* result = Original(pPostProcessingVolume, a2);

    Visuals::WorldModulation::Exposure(pPostProcessingVolume);

    return result;
}