#include "CGameEntitySystem.h"

#include "../../../utils/utils.h"

int CGameEntitySystem::GetHighestEntityIndex() {
	using GetHighestEntityIndex_t = int(__thiscall*)(void*, int*);
	static GetHighestEntityIndex_t GetHighestEntityIndex = reinterpret_cast<GetHighestEntityIndex_t>(Utils::OpcodeScan("client.dll", "8B 81 10 15 00"));

	int value = -1;
	GetHighestEntityIndex(this, &value);

	return value;
}

CEntityInstance* CGameEntitySystem::GetBaseEntity(int index) {
	using GetBaseEntity_t = CEntityInstance * (__thiscall*)(void*, int);
	static GetBaseEntity_t GetBaseEntity = reinterpret_cast<GetBaseEntity_t>(Utils::OpcodeScan("client.dll", "81 FA FE 7F 00 00 77 36"));

	return GetBaseEntity(this, index);
}

void* CGameEntitySystem::GetEntityIndex(int idx) {
	using GetEntityIndex_t = void* (__fastcall*)(void*, int);
	static GetEntityIndex_t GetEntityIndex = reinterpret_cast<GetEntityIndex_t>(Utils::OpcodeScan("client.dll", "81 FA ? ? ? ? 77 ? 8B C2 C1 F8 ? 83 F8 ? 77 ? 48 98 48 8B 4C C1 ? 48 85 C9 74 ? 8B C2 25 ? ? ? ? 48 6B C0 ? 48 03 C8 74 ? 8B 41 ? 25 ? ? ? ? 3B C2 75 ? 48 8B 01"));

	return GetEntityIndex(this, idx);
}