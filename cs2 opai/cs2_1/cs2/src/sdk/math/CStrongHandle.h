#pragma once

#include <type_traits>

struct CResourceBindingT
{
    void* MData;
};

template <typename T>
class CStrongHandle
{
public:
    operator T* () const
    {
        if (MBinding == nullptr)
            return nullptr;

        return static_cast<T*>(MBinding->MData);
    }

    T* operator->() const
    {
        if (MBinding == nullptr)
            return nullptr;

        return static_cast<T*>(MBinding->MData);
    }

    const CResourceBindingT* MBinding;
};