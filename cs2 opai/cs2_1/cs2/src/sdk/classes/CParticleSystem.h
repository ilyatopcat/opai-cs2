#pragma once
#include "../../utils/vmt.h"
#include "../../utils/utils.h"

#include "../math/Vector.h"
#include "../math/CStrongHandle.h"

class CParticleSnapshot
{
public:
    void Draw(int Count, void* Data)
    {
        CALL_VIRTUAL(this, void, 1, Count, Data);
    }
};

class CParticleEffect
{
public:
    const char* name{};
    char pad[0x30]{};
};

class CParticleInformation
{
public:
    float time;
    float width;
    float unk;
};

class CParticleData
{
public:
    Vector* vecPosition;
    char pad1[0x74];
    float* flTime;
    char pad2[0x28];
    float* flTime2;
    char pad3[0x98];
};

struct CParticleColor
{
    float r;
    float g;
    float b;
};

class CParticleManager
{
public:
    void CreateSnapshot(CStrongHandle<CParticleSnapshot>* OutParticleSnapshot)
    {
        __int64 unknown = 0;
        CALL_VIRTUAL(this, void, 42, OutParticleSnapshot, &unknown);
    }

    void Draw(CStrongHandle<CParticleSnapshot>* ParticleSnapshot, int Count, void* Data)
    {
        CALL_VIRTUAL(this, void, 43, ParticleSnapshot, Count, Data);
    }
};

class CParticleSystem
{
public:
    void CreateEffectIndex(unsigned int* effect_index, CParticleEffect* effect_data);
    void CreateEffect(unsigned int effect_index, int unk, void* clr, int unk2);
    void UnkFunction(int EffectIndex, unsigned int Unk, const CStrongHandle<CParticleSnapshot>* ParticleSnapshot);
};