#include "hooks.h"

void* Hooks::OverrideView::Hook(CViewRender* pViewRender, CViewSetup* pViewSetup, void* a3, void* a4, void* a5, void* a6) {
    IS_UNINITIALIZED(pViewRender, pViewSetup, a3, a4, a5, a6);

    if (config.visualRecoil == VISUAL_RECOIL_REMOVE_ALL && !Interfaces::input->m_bInThirdPerson)
        pViewSetup->angles = Interfaces::input->GetViewAngles();

    return Original(pViewRender, pViewSetup, a3, a4, a5, a6);
}