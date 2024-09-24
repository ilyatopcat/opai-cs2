#pragma once

#include "../CMaterial2.h"
#include "../../../utils/vmt.h"

class ResourceArray_t {
public:
    unsigned long long count;
    CMaterial2*** resources;
private:
    unsigned long long pad_0010[3];
};

class CResourceSystem {
public:
    void EnumerateResources(ResourceArray_t*, unsigned char);

    void EnumerateMaterials(std::uintptr_t hex, ResourceArray_t* arr, int num )
    {
        CALL_VIRTUAL(this, void, 38, hex, arr, num);
    }
};