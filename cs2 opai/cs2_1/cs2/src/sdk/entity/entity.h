#pragma once

#include <vector>

#include "../classes/entity/C_CSPlayerPawn.h"
#include "../classes/entity/CCSPlayerController.h"

#define ENTITY_ALL 1
#define ENTITY_ENEMIES_ONLY 2
#define ENTITY_TEAMMATES_ONLY 3

using PlayerControllerPair = std::pair<CCSPlayerController*, C_CSPlayerPawn*>;

namespace Entity {
    void Initialize();

    //inline C_CSPlayerPawn* LocalPlayerPawn;
    //inline CCSPlayerController* LocalPlayerController;

    void LevelInit();
    void LevelShutdown();
    void AddEntity(CEntityInstance*, int);
    void RemoveEntity(CEntityInstance*, int);

    C_CSPlayerPawn* GetLocalPlayerPawn();
    CCSPlayerController* GetLocalPlayerController();

    std::vector<CEntityInstance*> Get(const char*);
    int GetEntityHandle(C_CSPlayerPawn* pawn);
    std::vector<C_CSPlayerPawn*> GetPlayers(int);
    std::vector<PlayerControllerPair> GetPlayersWithController(int);
}