#include "CGameEvents.h"
#include "../interfaces/interfaces.h"

CCSPlayerController* CGameEventHelper::GetPlayerController()
{
    if (!Event)
        return nullptr;

    int controller_id{};

    CBuffer buffer;
    buffer.name = "userid";

    Event->GetControllerId(controller_id, &buffer);

    if (controller_id == -1)
        return nullptr;

    return (CCSPlayerController*)Interfaces::gameResourceService->pGameEntitySystem->GetEntityIndex(controller_id + 1);
}

CCSPlayerController* CGameEventHelper::GetAttackerController()
{
    if (!Event)
        return nullptr;

    int controller_id{};

    CBuffer buffer;
    buffer.name = "attacker";

    Event->GetControllerId(controller_id, &buffer);

    if (controller_id == -1)
        return nullptr;

    return (CCSPlayerController*)Interfaces::gameResourceService->pGameEntitySystem->GetEntityIndex(controller_id + 1);
}

int CGameEventHelper::GetDamage()
{
    if (!Event)
        return -1;

    return Event->GetInt2("dmg_health", false);
}

int CGameEventHelper::GetHealth()
{
    if (!Event)
        return -1;

    CBuffer buffer;
    buffer.name = "health";

    return Event->GetInt(&buffer);
}

int CGameEvent::GetInt2(const char* Name, bool Unk)
{
    using GetEventInt_t = int(__fastcall*)(void*, const char*, bool);
    static GetEventInt_t GetEventInt = reinterpret_cast<GetEventInt_t>(Utils::OpcodeScan("client.dll", "48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 56 48 83 EC 30 48 8B 01 41 8B F0 4C 8B F1 41 B0 01 48 8D 4C 24 20 48 8B DA 48 8B 78"));

    return GetEventInt(this, Name, Unk);
}

float CGameEvent::GetFloat2(const char* Name, bool Unk)
{
    using GetEventFloat_t = float(__fastcall*)(void*, const char*, bool);
    static GetEventFloat_t GetEventFloat = reinterpret_cast<GetEventFloat_t>(Utils::OpcodeScan("client.dll", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B 01 48 8B F1 0F 29 74 24 30 48 8D 4C 24 20 0F 28 F2 48 8B DA 48 8B 78"));

    return GetEventFloat(this, Name, Unk);
}