#include "hooks.h"

void Hooks::DrawTeamIntro::Hook(void* pGameRules, void* pGameRulesProxy, byte* a3) {
    IS_UNINITIALIZED(pGameRules, pGameRulesProxy, a3);

    if (config.removals & REMOVALS_TEAM_INTRO)
        return;

    Original(pGameRules, pGameRulesProxy, a3);
}