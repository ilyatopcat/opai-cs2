#include "CSchemaSystem.h"

#include "../../../utils/vmt.h"

const char* CSchemaClassInfo::GetName() {
    return *reinterpret_cast<const char**>((unsigned __int64)(this) + 0x8);
}

short CSchemaClassInfo::GetFieldsSize() {
    return *reinterpret_cast<short*>((unsigned __int64)(this) + 0x1C);
}

CSchemaClassField* CSchemaClassInfo::GetFields() {
    return *reinterpret_cast<CSchemaClassField**>((unsigned __int64)(this) + 0x28);
}

CSchemaClassInfo* CSchemaSystemTypeScope::FindDeclaredClass(const char* className) {
    CSchemaClassInfo* rv = nullptr;
    CALL_VIRTUAL(this, void, 2, &rv, className);

    return rv;
}

CSchemaSystemTypeScope* CSchemaSystem::FindTypeScopeForModule(const char* moduleName) {
    return CALL_VIRTUAL(this, CSchemaSystemTypeScope*, 13, moduleName, nullptr);
}