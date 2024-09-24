#include "hooks.h"

void* Hooks::ViewPunch::Hook(CPlayer_CameraServices* pCameraServices, float* a2, float* a3, float* a4) {
    IS_UNINITIALIZED(pCameraServices, a2, a3, a4);

    if (config.visualRecoil == VISUAL_RECOIL_REMOVE_SHAKE) {
        static Vector nullVector;

        pCameraServices->m_vecCsViewPunchAngle() = nullVector;
    }

    return Original(pCameraServices, a2, a3, a4);
}