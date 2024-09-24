#include "hooks.h"

void* Hooks::UpdateSkybox::Hook(C_EnvSky* pEnvSky) {
    IS_UNINITIALIZED(pEnvSky);

    Visuals::WorldModulation::Skybox(pEnvSky);

    return Original(pEnvSky);
}