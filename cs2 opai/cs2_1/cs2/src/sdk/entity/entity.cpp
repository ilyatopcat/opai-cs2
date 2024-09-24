#include <Windows.h>
#include <map>

#include "entity.h"

#include "../../hash/hash.h"
#include "../interfaces/interfaces.h"
#include "../../src/features/visuals/visuals.h"

std::unordered_map<uint64_t, std::vector<CEntityInstance*>> entities;

void Entity::Initialize() {
    static CGameEntitySystem* gameEntitySystem = Interfaces::gameResourceService->pGameEntitySystem;

    int highestIndex = gameEntitySystem->GetHighestEntityIndex();
    for (int index = 0; index <= highestIndex; index++) {
        CEntityInstance* pEntity = gameEntitySystem->GetBaseEntity(index);

        if (!pEntity)
            continue;

        const char* className = pEntity->GetEntityClassName();
        entities[HASH(className)].emplace_back(pEntity);

        auto baseEntity = pEntity->As<C_BaseEntity>();
        if (baseEntity->isWeapon())
            Visuals::Weapons::weaponEntities.emplace_back(baseEntity);
    }
}

void Entity::LevelInit() {
    entities.clear();
    Visuals::Weapons::weaponEntities.clear();

    Initialize();
}

void Entity::LevelShutdown() {
    entities.clear();
    Visuals::Weapons::weaponEntities.clear();
}

void Entity::AddEntity(CEntityInstance* pEntity, int handle) {
    const char* className = pEntity->GetEntityClassName();

    auto baseEntity = pEntity->As<C_BaseEntity>();
    if (baseEntity->isWeapon()) 
        Visuals::Weapons::weaponEntities.emplace_back(baseEntity);

    entities[HASH(className)].emplace_back(pEntity);
}

void Entity::RemoveEntity(CEntityInstance* pEntity, int handle) {
    const char* className = pEntity->GetEntityClassName();

    auto baseEntity = pEntity->As<C_BaseEntity>();
    if (baseEntity->isWeapon())
    {
        for (auto iter = Visuals::Weapons::weaponEntities.begin(); iter != Visuals::Weapons::weaponEntities.end(); ++iter) {
            if ((*iter) == pEntity) {
                Visuals::Weapons::weaponEntities.erase(iter);

                break;
            }
        }
    }

    auto it = entities.find(HASH(className));
    if (it == entities.end())
        return;

    std::vector<CEntityInstance*>& entities = it->second;

    for (auto iter = entities.begin(); iter != entities.end(); ++iter) {
        if ((*iter) == pEntity) {
            entities.erase(iter);

            break;
        }
    }
}

C_CSPlayerPawn* Entity::GetLocalPlayerPawn() {
    CCSPlayerController* pPlayerController = GetLocalPlayerController();
    if (!pPlayerController)
        return nullptr;
    
    if (!pPlayerController)
        return nullptr;

    C_CSPlayerPawn* pPlayerPawn = pPlayerController->m_hPawn().Get<C_CSPlayerPawn>();
    if (!pPlayerPawn->IsPlayerPawn())
        return nullptr;

    return pPlayerPawn;
}

CCSPlayerController* Entity::GetLocalPlayerController() {
    static CGameEntitySystem* gameEntitySystem = Interfaces::gameResourceService->pGameEntitySystem;

    int localPlayerIndex = Interfaces::engineClient->GetLocalPlayerIndex();
    if (localPlayerIndex == 0)
        return nullptr;

    CEntityInstance* pEntity = gameEntitySystem->GetBaseEntity(localPlayerIndex);
    if (!pEntity)
        return nullptr;

    CCSPlayerController* pPlayerController = pEntity->As<CCSPlayerController>();
    if (!pPlayerController->IsPlayerController())
        return nullptr;

    return pPlayerController;
}

std::vector<CEntityInstance*> Entity::Get(const char* className) {
	return entities[HASH(className)];
}

int Entity::GetEntityHandle(C_CSPlayerPawn* pawn)
{
    if (!pawn)
		return -1;

    using fn = unsigned int(__fastcall*)(C_CSPlayerPawn*);
    static auto function = reinterpret_cast<fn>(Utils::OpcodeScan("client.dll", "48 85 C9 74 32 48 8B 41 10 48 85 C0 74 29 44"));

    return function(pawn);
}

std::vector<C_CSPlayerPawn*> Entity::GetPlayers(int type) {
    std::vector<C_CSPlayerPawn*> returnEntities;

    C_CSPlayerPawn* localPlayerPawn = GetLocalPlayerPawn();
    if (!localPlayerPawn)
        return returnEntities;

    int localPlayerTeamNum = localPlayerPawn->m_iTeamNum();

    std::vector<CEntityInstance*> entities = Entity::Get("C_CSPlayerPawn");
    for (CEntityInstance* pEntity : entities) {
        C_CSPlayerPawn* playerPawn = pEntity->As<C_CSPlayerPawn>();

        int teamNum = playerPawn->m_iTeamNum();

        if (type == ENTITY_ALL || ((type == ENTITY_ENEMIES_ONLY && localPlayerTeamNum != teamNum) || (type == ENTITY_TEAMMATES_ONLY && localPlayerTeamNum == teamNum && localPlayerPawn != playerPawn)))
            returnEntities.emplace_back(playerPawn);
    }

    return returnEntities;
}

std::vector<PlayerControllerPair> Entity::GetPlayersWithController(int type)
{
    std::vector<PlayerControllerPair> returnEntities;

    C_CSPlayerPawn* localPlayerPawn = GetLocalPlayerPawn();
    if (!localPlayerPawn)
        return returnEntities;

    int localPlayerTeamNum = localPlayerPawn->m_iTeamNum();

    auto entities = Entity::Get("CCSPlayerController");
    for (auto entity : entities)
    {
        auto controller = entity->As<CCSPlayerController>();

        auto playerPawn = controller->m_hPawn().Get<C_CSPlayerPawn>();
        if (!playerPawn)
            continue;

        int teamNum = playerPawn->m_iTeamNum();

        if (type == ENTITY_ALL || ((type == ENTITY_ENEMIES_ONLY && localPlayerTeamNum != teamNum) || (type == ENTITY_TEAMMATES_ONLY && localPlayerTeamNum == teamNum && localPlayerPawn != playerPawn)))
            returnEntities.emplace_back(std::make_pair(controller, playerPawn));
    }

    return returnEntities;
}
