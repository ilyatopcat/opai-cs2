#pragma once

#include "C_BaseEntity.h"

#include "../../schema/schema.h"

class C_BaseModelEntity : public C_BaseEntity {
public:
	SCHEMA(m_vecViewOffset, Vector, "C_BaseModelEntity", "m_vecViewOffset");

    void SetModel(const char* model_name)
    {
        using fnSetModel = void*(__fastcall*)(void*, const char*);
        static fnSetModel oSetModel = reinterpret_cast<fnSetModel>(Utils::OpcodeScanAbsolute("client.dll", "E8 ? ? ? ? 41 8B 54 24 ? 49 8B 0C 24", 0x1));

        oSetModel(this, model_name);
    }
};