#include "CParticleSystem.h"

void CParticleSystem::CreateEffectIndex(unsigned int* effect_index, CParticleEffect* effect_data)
{
	using CreateEffectIndex_t = void(__fastcall*)(CParticleSystem*, unsigned int*, CParticleEffect*);
	static CreateEffectIndex_t CreateEffectIndex = reinterpret_cast<CreateEffectIndex_t>(Utils::OpcodeScan("client.dll", "40 57 48 83 EC 20 49 8B 00 48 8B FA 48 85 C0 74 31 80 38 00 74 2C 48 89 5C 24 ?"));

	CreateEffectIndex(this, effect_index, effect_data);
}

void CParticleSystem::UnkFunction(int EffectIndex, unsigned int Unk, const CStrongHandle<CParticleSnapshot>* ParticleSnapshot)
{
	using Unk_t = bool(__fastcall*)(CParticleSystem*, int, unsigned int, const CStrongHandle<CParticleSnapshot>*);
	static Unk_t UnkFunc = reinterpret_cast<Unk_t>(Utils::OpcodeScan("client.dll", "48 89 74 24 10 57 48 83 EC 30 4C 8B D9 49 8B F9 33 C9 41 8B F0 83 FA FF 0F"));

	UnkFunc(this, EffectIndex, Unk, ParticleSnapshot);
}

void CParticleSystem::CreateEffect(unsigned int effect_index, int unk, void* clr, int unk2)
{
	using CreateEffect_t = void(__fastcall*)(CParticleSystem*, unsigned int, int, void*, int);
	static CreateEffect_t CreateEffect = reinterpret_cast<CreateEffect_t>(Utils::OpcodeScan("client.dll", "48 83 EC 58 F3 41 0F 10 51 ? 0F 28 05 ? ? ? ? F2 41 0F 10 19 4C 8D 4C 24 ? F3 0F 10 0D ? ? ? ? 0F 14 D1 66 0F 7F 44 24 ?"));

	CreateEffect(this, effect_index, unk, clr, unk2);
}