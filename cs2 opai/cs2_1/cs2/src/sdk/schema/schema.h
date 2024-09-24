#pragma once

#include <memory>

short SchemaGetOffset(const char* className, const char* keyName);

#define SCHEMA(varName, type, className, keyName)																		\
	type& varName() {																									\
		static const short offset = SchemaGetOffset(className, keyName);												\
																														\
		return *reinterpret_cast<type*>(reinterpret_cast<unsigned __int64>(this) + offset);								\
	}

#define SCHEMA_ARRAY(varName, type, className, keyName)																		\
	type* varName() {																									\
		static const short offset = SchemaGetOffset(className, keyName);												\
																														\
		return reinterpret_cast<type*>(reinterpret_cast<unsigned __int64>(this) + offset);								\
	}

#define OFFSET( type, name, offset )                                                              \
    __forceinline std::add_lvalue_reference_t< type > name( ) const {                                             \
        return *reinterpret_cast< type* >( reinterpret_cast< std::uintptr_t >( this ) + offset ); \
    }