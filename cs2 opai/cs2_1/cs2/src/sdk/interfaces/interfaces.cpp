#include <Windows.h>
#include <stdint.h>
#include <iostream>

#include "interfaces.h"
#include "../../utils/utils.h"
#include "../../utils/vmt.h"

#define CHECK(name, arg)                                    \
    if (arg == nullptr) {                                   \
        printf("[Interfaces] Failed to get: %s \n", name);  \
                                                            \
        return false;                                       \
    }

uint8_t* pGlobalVars;

//#include <fstream>

bool Interfaces::Initialize() {
    gameResourceService = GetInterface<GameResourceServiceClientV001>("engine2.dll", "GameResourceServiceClientV001");
    CHECK("Game Resource Service", gameResourceService);

    schemeSystem = GetInterface<CSchemaSystem>("schemasystem.dll", "SchemaSystem_001");
    CHECK("Scheme System", schemeSystem);

    pGlobalVars = Utils::OpcodeScan("client.dll", "48 8B 0D ?? ?? ?? ?? 48 8B D9"); // xref: tick(%d) curtime(%f) DoStartSoundEvent(%s)\n

    CHECK("Global Vars", pGlobalVars);

    UpdateGlobalVars();

    inputSystem = GetInterface<CInputSystem>("inputsystem.dll", "InputSystemVersion001");
    CHECK("Input System", inputSystem);

    cvar = GetInterface<Cvar>("tier0.dll", "VEngineCvar007");
    CHECK("Cvar", cvar);

    while (sceneViewDebugOverlay == nullptr) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        sceneViewDebugOverlay = *reinterpret_cast<void**>(Utils::OpcodeScanAbsolute("client.dll", "48 8B 05 ?? ?? ?? ?? 48 8B 74 24 48 48 83 C4 20", 0x3));
    }

    CHECK("SceneViewDebugOverlay", sceneViewDebugOverlay);

    particleManager = (CParticleManager*)(Utils::OpcodeScanAbsolute("client.dll", "E8 ?? ?? ?? ?? 0F 57 C0 4C 8D 4C 24 30", 0x1));
    CHECK("ParticleManager", particleManager);

    particleSystem = (CParticleSystem*)(Utils::OpcodeScanAbsolute("client.dll", "48 8B 05 ?? ?? ?? ?? 48 8B 08 48 8B 59 68", 0x3));
    CHECK("ParticleSystem", particleSystem);

    Interfaces::gameRules = *reinterpret_cast<CGameRules**>(Utils::OpcodeScanAbsolute("client.dll", "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 84 C0 74 0D 33 C0", 0x3));
    CHECK("GameRules", gameRules);

    Interfaces::engineTrace = *reinterpret_cast<CEngineTrace**>(Utils::OpcodeScanAbsolute("client.dll", "4C 8B 3D ? ? ? ? 24 C9 0C 49 66 0F 7F 45 ?", 0x3));
    CHECK("EngineTrace", engineTrace);

    using GetInput_t = CCSGOInput* (__fastcall*)();
    GetInput_t GetInput = reinterpret_cast<GetInput_t>(Utils::OpcodeScanAbsolute("client.dll", "E8 ?? ?? ?? ?? 48 8B 56 60", 0x1));

    CHECK("Input", GetInput);

    input = GetInput();

    materialSystem = GetInterface<CMaterialSystem>("materialsystem2.dll", "VMaterialSystem2_001");
    CHECK("Material System", materialSystem);

    engineClient = GetInterface<IEngineClient>("engine2.dll", "Source2EngineToClient001");
    CHECK("Engine Client", engineClient);

    resourceSystem = GetInterface<CResourceSystem>("resourcesystem.dll", "ResourceSystem013");
    CHECK("Resource System", resourceSystem);

    inputService = GetInterface<void*>("engine2.dll", "InputService_001");
    CHECK("Input Service", inputService);

    client = GetInterface<CClient>("client.dll", "Source2Client002");
    CHECK("Source2Client", client);

    localize = GetInterface<ILocalize>("localize.dll", "Localize_001");
    CHECK("Localize", localize);

    networkClientService = GetInterface<CNetworkClientService>("engine2.dll", "NetworkClientService_001");
    CHECK("NetworkClientService", networkClientService);

    gameEventManager = *(CGameEventManager**)(Utils::OpcodeScanAbsolute("client.dll", "48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? 48 85 C9 74 2D", 0x3));
    CHECK("EventManager", gameEventManager);

    return true;
}

template <typename T>
T* Interfaces::GetInterface(const char* moduleName, const char* interfaceName) {
    const HINSTANCE moduleHandle = GetModuleHandle(moduleName);
    if (!moduleHandle)
        return nullptr;

    using CreateInterface_t = T * (*)(const char*, int*);
    const CreateInterface_t CreateInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(moduleHandle, "CreateInterface"));
    if (!CreateInterface)
        return nullptr;

    return CreateInterface(interfaceName, nullptr);
}

void Interfaces::UpdateGlobalVars() {
    globalVars = *reinterpret_cast<GlobalVars**>(Utils::ResolveRelativeAddress(pGlobalVars, 0x3, 0x7));
}