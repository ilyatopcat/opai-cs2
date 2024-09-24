#pragma once

struct CSchemaClassField {
    const char* m_name;
    char pad0[0x8];
    short m_offset;
    char pad1[0xE];
};

class CSchemaClassInfo {
public:
    const char* GetName();
    short GetFieldsSize();
    CSchemaClassField* GetFields();
};

class CSchemaSystemTypeScope {
public:
    CSchemaClassInfo* FindDeclaredClass(const char* pClass);
};

class CSchemaSystem {
public:
    CSchemaSystemTypeScope* FindTypeScopeForModule(const char* module);
};