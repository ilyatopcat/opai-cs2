#include "hooks.h"

void* Hooks::DrawLightSceneObject::Hook(CLightBinnerGPU* pLightBinnerGPU, CSceneLightObject* pSceneLightObject, __int64 a3) {
    IS_UNINITIALIZED(pLightBinnerGPU, pSceneLightObject, a3);

    void* result = Original(pLightBinnerGPU, pSceneLightObject, a3);

    Visuals::WorldModulation::Lighting(pSceneLightObject);

    return result;
}