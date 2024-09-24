#include <unordered_map>

#include "schema.h"

#include "../interfaces/interfaces.h"
#include "../../hash/hash.h"

using SchemaKeyValueMap_t = std::unordered_map<unsigned long long, short>;
using SchemaTableMap_t = std::unordered_map<unsigned long long, SchemaKeyValueMap_t>;

const char* dllFiles[2] = {"client.dll" , "animationsystem.dll"};

bool InitSchemaFieldsForClass(SchemaTableMap_t& tableMap, const char* className, uint64_t classKey) {
    for (const char* dllFile : dllFiles) {
        CSchemaSystemTypeScope* typeScope = Interfaces::schemeSystem->FindTypeScopeForModule(dllFile);
        if (!typeScope)
            continue;

        CSchemaClassInfo* classInfo = typeScope->FindDeclaredClass(className);
        if (!classInfo)
            continue;

        short fieldsSize = classInfo->GetFieldsSize();
        CSchemaClassField* fields = classInfo->GetFields();

        auto& keyValueMap = tableMap[classKey];

        for (int i = 0; i < fieldsSize; ++i) {
            CSchemaClassField& field = fields[i];

            keyValueMap.emplace(HASH(field.m_name), field.m_offset);
        }

        return true;
    }

    tableMap.emplace(classKey, SchemaKeyValueMap_t{});

    return false;
}

int16_t SchemaGetOffset(const char* className, const char* keyName) {
    uint64_t classNameKey = HASH(className);
    uint64_t keyNameKey = HASH(keyName);

    static SchemaTableMap_t schemaTableMap;

    const auto& it = schemaTableMap.find(classNameKey);
    if (it == schemaTableMap.cend()) {
        if (InitSchemaFieldsForClass(schemaTableMap, className, classNameKey))
            return SchemaGetOffset(className, keyName);

        printf_s("[Schema] couldn't find %s->%s \n", className, keyName);

        return 0;
    }

    const SchemaKeyValueMap_t& tableMap = it->second;
    if (tableMap.find(keyNameKey) == tableMap.cend()) {
        printf_s("[Schema] couldn't find %s->%s \n", className, keyName);

        return 0;
    }

    int16_t offset = tableMap.at(keyNameKey);

    printf_s("[Schema] %s->%s: 0x%X \n", className, keyName, offset);

    return offset;
}