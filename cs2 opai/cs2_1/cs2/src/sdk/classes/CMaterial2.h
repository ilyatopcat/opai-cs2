#pragma once

#include "../math/Color.h"
#include "entity/CHandle.h"

class CSkeletonInstance;
class CBodyComponentSkeletonInstance;
class CHandle;

class CMaterialVector {
public:
    float vec[4];

    float& operator[](int index) {
        return vec[index];
    }
};

class CMaterialParamater {
public:
    CMaterialVector vector; // 0x0
    void* texture; // 0x10
private:
    char pad[0x10]; // 0x18
public:
    const char* name; // 0x28
    const char* text; // 0x30
    long long value; // 0x38
};

class CMaterial2 {
public:
    const char* GetName();
    const char* GetShareName();

    CMaterialParamater* FindParameter(const char* name);
    void UpdateParameter();

    void ColorModulate(ColorRGB);
    void ColorModulate(ColorRGBA);
};

class CMaterialData {
public:
};

enum ObjectInfoEnumeratedId : int {
    ARMS = 38,
    PLAYER_TERRORIST = 104,
    PLAYER_COUNTER_TERRORIST = 113
};

class CObjectInfo {
public:
    char pad_0000[224]; //0x0000
    CBodyComponentSkeletonInstance* skeletonInstance; //0x00E0
};

class CSceneAnimatableObject
{
public:
    char pad[0xB8];
    CHandle owner;
};

class CSceneData {
private:
    char pad_0000[0x18];
public:
    CSceneAnimatableObject* sceneObject;
    CMaterial2* material;
private:
    char pad_0020[0x18];
public:
    ByteColorRGBA color;
    CObjectInfo* objectInfo;
};