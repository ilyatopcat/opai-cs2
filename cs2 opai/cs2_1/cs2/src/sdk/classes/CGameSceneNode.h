#pragma once

#include "../schema/schema.h"
#include "../math/Vector.h"
#include <cstdint>

#include "CHitboxes.h"

class CSkeletonInstance;
class CHandle;

class CGameSceneNodeHandle {
public:
    SCHEMA(m_hOwner, CHandle, "CGameSceneNodeHandle", "m_hOwner");
};

class CGameSceneNode {
public:
    SCHEMA(m_vecOrigin, Vector, "CGameSceneNode", "m_vecOrigin");
    SCHEMA(m_vecAbsOrigin, Vector, "CGameSceneNode", "m_vecAbsOrigin");
    SCHEMA(m_nodeToWorld, CTransform, "CGameSceneNode", "m_nodeToWorld");
    SCHEMA(m_hParent, CGameSceneNodeHandle, "CGameSceneNode", "m_hParent");

    void SetMeshGroupMask(uint64_t mask);

    CSkeletonInstance* GetSkeletonInstance();
};