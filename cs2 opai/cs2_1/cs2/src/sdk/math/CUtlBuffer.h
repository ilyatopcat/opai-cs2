#pragma once

#include "../../utils/utils.h"

class CUtlBuffer {
    char pad_001[0x80];
public:
    CUtlBuffer(int a1, int size, int a3) {
        using MakeUtlBuffer_t = void(__fastcall*)(CUtlBuffer*, int, int, int);
        static MakeUtlBuffer_t MakeUtlBuffer = reinterpret_cast<MakeUtlBuffer_t>(Utils::OpcodeScan("tier0.dll", "48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 48 89 7C 24 ?? 41 56 48 83 EC 20 33 DB 44 89 41 08"));

        MakeUtlBuffer(this, a1, size, a3);
    };
    CUtlBuffer() { };

    void EnsureCapacity(int size)
    {
        using EnsureCapacity_t = void(__fastcall*)(CUtlBuffer*, int);
        static EnsureCapacity_t EnsureCapacityFunc = reinterpret_cast<EnsureCapacity_t>(Utils::OpcodeScan("tier0.dll", "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 20 F7"));

        EnsureCapacityFunc(this, size);
    }
};