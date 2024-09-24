#include <iostream>

#include "CEntityInstance.h"

#include "../../interfaces/interfaces.h"
#include "../../../utils/vmt.h"

#define GET_CLASS_INFO(varName, dllName, className)                                                                  \
    static CSchemaSystemTypeScope* typeScope = Interfaces::schemeSystem->FindTypeScopeForModule(dllName);            \
    if (!typeScope) {                                                                                                \
        printf("Failed to get type scope: %s", dllName);                                                             \
                                                                                                                     \
        return false;                                                                                                \
    }                                                                                                                \
                                                                                                                     \
    static CSchemaClassInfo* varName = typeScope->FindDeclaredClass(className);                                      \
    if (!classInfo) {                                                                                                \
        printf("Failed to get class info: %s", className);                                                           \
                                                                                                                     \
        return false;                                                                                                \
    }

CSchemaClassInfo* CEntityInstance::GetSchemaClassInfo() {
    CSchemaClassInfo* classInfo = nullptr;

    CALL_VIRTUAL(this, void, 38, &classInfo);

    return classInfo;
}

const char* CEntityInstance::GetEntityClassName() {
    CSchemaClassInfo* classInfo = GetSchemaClassInfo();

    return classInfo->GetName();
}

bool CEntityInstance::IsPlayer() {
    return IsPlayerPawn() || IsPlayerController();
}

bool CEntityInstance::IsPlayerPawn() {
    GET_CLASS_INFO(classInfo, "client.dll", "C_CSPlayerPawn");

    return GetSchemaClassInfo() == classInfo;
}

bool CEntityInstance::IsPlayerController() {
    GET_CLASS_INFO(classInfo, "client.dll", "CCSPlayerController");

    return GetSchemaClassInfo() == classInfo;
}