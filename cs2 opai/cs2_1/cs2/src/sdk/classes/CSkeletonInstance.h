#pragma once

#include "../schema/schema.h"
#include "../math/Vector.h"

class C_BaseEntity;

struct CBoneData
{
    Vector pos;
    float scale;
    Vector4D rot;
};

class CModelState
{
public:
    CBoneData* GetBoneData() noexcept
    {
        return *reinterpret_cast<CBoneData**>(reinterpret_cast<std::uintptr_t>(this) + 0x80);
    }
};

class CSkeletonInstance : public CGameSceneNode
{
public:
    SCHEMA(m_pModelState, CModelState, "CSkeletonInstance", "m_modelState");
    SCHEMA(m_nHitboxSet, std::uint8_t, "CSkeletonInstance", "m_nHitboxSet");

    void CalcWorldSpaceBones(int boneMask) {
        using CalcWorldSpaceBones_t = void(__fastcall*)(CSkeletonInstance*, int);
        auto CalcWorldSpaceBones = reinterpret_cast<CalcWorldSpaceBones_t>(Utils::OpcodeScan("client.dll", "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC D0"));

        CalcWorldSpaceBones(this, boneMask);
    }

    CModel* GetModel()
    {
        auto ptr = *reinterpret_cast<void**>((uintptr_t)this + 0x210);

        if (!ptr)
            return nullptr;

        return *reinterpret_cast<CModel**>(ptr);
    }

    CEntityInstance* GetEntity()
    {
        return *reinterpret_cast<CEntityInstance**>(reinterpret_cast<uintptr_t>(this) + 0x260);
    }
};

class CBodyComponentSkeletonInstance : public CSkeletonInstance
{
public:

};