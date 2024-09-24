#pragma once

#include "../classes/interfaces/GameResourceServiceClientV001.h"
#include "../classes/interfaces/CSchemaSystem.h"
#include "../classes/interfaces/CMaterialSystem.h"
#include "../classes/interfaces/IEngineClient.h"
#include "../classes/interfaces/CVar.h"
#include "../classes/interfaces/CLocalize.h"
#include "../classes/interfaces/CEngineTrace.h"
#include "../classes/interfaces/CResourceSystem.h"
#include "../classes/interfaces/CInputSystem.h"
#include "../classes/CParticleSystem.h"

#include "../classes/GlobalVars.h"
#include "../classes/CCSGOInput.h"
#include "../classes/CGameEvents.h"
#include "../classes/CNetworkClientService.h"
#include "../classes/CCLient.h"
#include "../classes/CGameRules.h"

#define INTERVAL_PER_TICK 0.015625f
#define TICK_INTERVAL (INTERVAL_PER_TICK)
#define TIME_TO_TICKS(TIME) (static_cast<int>(0.5f + static_cast<float>(TIME) / TICK_INTERVAL))
#define TICKS_TO_TIME(TICKS) (TICK_INTERVAL * static_cast<float>(TICKS))

namespace Interfaces {
	bool Initialize();

    template <typename T>
	T* GetInterface(const char*, const char*);

    inline GameResourceServiceClientV001* gameResourceService;

    inline CSchemaSystem* schemeSystem;

    inline Cvar* cvar;

    inline CParticleManager* particleManager;
    inline CParticleSystem* particleSystem;

    inline void* sceneViewDebugOverlay;

    inline GlobalVars* globalVars;
    void UpdateGlobalVars();

    inline ILocalize* localize;

    inline CGameRules* gameRules;

    inline CCSGOInput* input;

    inline CGameEventManager* gameEventManager;

    inline CNetworkClientService* networkClientService;

    inline CInputSystem* inputSystem;

    inline CEngineTrace* engineTrace;

    inline void* inputService;

    inline CClient* client;

    inline CMaterialSystem* materialSystem;

    inline IEngineClient* engineClient;

    inline CResourceSystem* resourceSystem;
}