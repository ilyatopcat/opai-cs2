#include "hooks.h"

void* Hooks::LevelInit::Hook(void* pClientModeShared, const char* mapName) {
    IS_UNINITIALIZED(pClientModeShared, mapName);

    Interfaces::UpdateGlobalVars();

    Entity::LevelInit();

    Interfaces::gameRules = *reinterpret_cast<CGameRules**>(Utils::OpcodeScanAbsolute("client.dll", "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 74 0D 33 C0", 0x3));

    Interfaces::particleSystem = reinterpret_cast<CParticleSystem * (__fastcall*)()>(Utils::OpcodeScanAbsolute("client.dll", "E8 ?? ?? ?? ?? 80 FB 03 F3 0F 11 7C 24 20", 0x1))();
    Interfaces::particleManager = *reinterpret_cast<CParticleManager**>(Utils::OpcodeScanAbsolute("client.dll", "48 8B 05 ?? ?? ?? ?? 48 8B 08 48 8B 59 68", 0x3));

    return Original(pClientModeShared, mapName);
}