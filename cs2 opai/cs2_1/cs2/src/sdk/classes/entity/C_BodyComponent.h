#pragma once

#include "CEntityInstance.h"

class CGameSceneNode;

class CAnimationGraphInstance
{
public:
    void SetNetworkedVariables(void* ptr) noexcept
    {
        *reinterpret_cast<void**>(std::uintptr_t(this) + 0x2E0) = ptr;
    }
};

class CBaseAnimGraphController
{
public:
    CAnimationGraphInstance* GetAnimGraph()
    {
        return *(CAnimationGraphInstance**)(std::uintptr_t(this) + 0x16F0);
    }
};

class CBodyComponent : public CEntityInstance
{
public:
    CGameSceneNode* m_pGameSceneNode;
    unsigned char pad_10[0x40];

    CBaseAnimGraphController* GetBaseAnimGraph()
    {
        return reinterpret_cast<CBaseAnimGraphController*>(std::uintptr_t(this) + 0x468);
    }
};