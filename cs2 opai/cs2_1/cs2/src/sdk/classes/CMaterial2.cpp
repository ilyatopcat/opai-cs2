#include <iostream>

#include "../../utils/vmt.h"
#include "../../utils/utils.h"

#include "CMaterial2.h"

const char* CMaterial2::GetName() {
    return CALL_VIRTUAL(this, const char*, 0);
}

const char* CMaterial2::GetShareName() {
    return CALL_VIRTUAL(this, const char*, 1);
}

CMaterialParamater* CMaterial2::FindParameter(const char* name) {
    // xref: "%f %f %f %f" (https://i.imgur.com/1pQtGg6.png) CMaterialSystem2: 23
    using FindParameter_t = CMaterialParamater * (__fastcall*)(void*, const char*);
    static FindParameter_t FindParameter = reinterpret_cast<FindParameter_t>(Utils::OpcodeScan("materialsystem2.dll", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B 59 18"));

    if (!FindParameter) {
        printf("[CMaterial2] fained to find FindParameter \n");

        return nullptr;
    }

    return FindParameter(this, name);
}

void CMaterial2::UpdateParameter() {
    using UpdateParameter_t = void(__fastcall*)(void*);
    static UpdateParameter_t UpdateParameter = reinterpret_cast<UpdateParameter_t>(Utils::OpcodeScan("materialsystem2.dll", "40 56 41 54 48 83 EC"));

    if (!UpdateParameter) {
        printf("[CMaterial2] fained to find UpdateParameter \n");

        return;
    }

    UpdateParameter(this);
}

void CMaterial2::ColorModulate(ColorRGB color) {
    CMaterialParamater* materialParamater = FindParameter("g_vColorTint");
    if (!materialParamater)
        return;

    CMaterialVector& materialVector = materialParamater->vector;

    materialVector[0] = color.r;
    materialVector[1] = color.g;
    materialVector[2] = color.b;
    materialVector[3] = 1;

    UpdateParameter();
}

void CMaterial2::ColorModulate(ColorRGBA color) {
    CMaterialParamater* materialParamater = FindParameter("g_vColorTint");
    if (!materialParamater)
        return;

    CMaterialVector& materialVector = materialParamater->vector;

    materialVector[0] = color.r;
    materialVector[1] = color.g;
    materialVector[2] = color.b;
    materialVector[3] = color.a;

    UpdateParameter();
}