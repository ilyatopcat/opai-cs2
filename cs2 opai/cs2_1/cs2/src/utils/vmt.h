#pragma once

#define CALL_VIRTUAL(pClass, retType, index, ...) vmt::CallVirtual<retType>(pClass, index, __VA_ARGS__)

namespace vmt {
    template <typename T = void*>
    inline T GetVMethod(void* pClass, unsigned int index) {
        if (!pClass) {
            return T{};
        }

        void** pVTable = *static_cast<void***>(pClass);
        if (!pVTable) {
            return T{};
        }

        return reinterpret_cast<T>(pVTable[index]);
    }

    template <typename T, typename... Args>
    inline T CallVirtual(void* pClass, unsigned int index, Args... args) {
        auto pFunc = GetVMethod<T(__thiscall*)(void*, Args...)>(pClass, index);

        return pFunc(pClass, args...);
    }
}