#pragma once

#include "../math/Vector.h"

class CViewSetup {
private:
    char pad_0000[0x04D8]; //0x0000
public:
    float fov; //0x04D8
    float viewmodelFov; //0x04DC
    Vector origin; //0x04E0
private:
    char pad_04EC[0xC]; //0x04EC
public:
    Vector angles; //0x04F8
private:
    char pad_0504[0x14]; //0x0504
public:
    float aspectRatio; //0x0518
};