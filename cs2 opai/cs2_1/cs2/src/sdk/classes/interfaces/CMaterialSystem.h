#pragma once

#include "../CMaterial2.h"

class CMaterialSystem {
public:
    CMaterial2*** FindMaterial(CMaterial2***, const char*);
    CMaterial2** CreateMaterial(CMaterial2***, const char*, void*);

    void SetCreateDataByMaterial(void*, CMaterial2***);
};