#pragma once

#include "../../schema/schema.h"
#include "CEntityIdentity.h"
#include "../../math/CBaseHandle.h"

class CSchemaClassInfo;

class CEntityInstance {
public:
    template <typename T>
    T* As() {
        return reinterpret_cast<T*>(this);
    }

    CSchemaClassInfo* GetSchemaClassInfo();
    const char* GetEntityClassName();

    CBaseHandle GetRefEHandle()
    {
        CEntityIdentity* pIdentity = m_pEntity();
        if (pIdentity == nullptr)
            return CBaseHandle();

        return CBaseHandle(pIdentity->m_iIndex(), pIdentity->GetSerialNumber() - (pIdentity->m_flags() & 1));
    }

    bool IsPlayer();
    bool IsPlayerPawn();
    bool IsPlayerController();

    SCHEMA(m_pEntity, CEntityIdentity*, "CEntityInstance", "m_pEntity")
    SCHEMA(m_bVisibleinPVS, bool, "CEntityInstance", "m_bVisibleinPVS");
};