#pragma once

namespace Utils {
    unsigned char* OpcodeScan(const char*, const char*);
    unsigned char* OpcodeScan(const char*, const char*, int);

    unsigned char* OpcodeScanRelative(const char*, const char*, int, int);
    unsigned char* OpcodeScanRelative(const char*, const char*, int, int, int);

    unsigned char* OpcodeScanAbsolute(const char*, const char*);
    unsigned char* OpcodeScanAbsolute(const char*, const char*, int);
    unsigned char* OpcodeScanAbsolute(const char*, const char*, int, int);

    unsigned char* GetAbsoluteAddress(unsigned char*);
    unsigned char* GetAbsoluteAddress(unsigned char*, int);
    unsigned __int64 ExportFn(unsigned __int64 base, const char* procedure_name);
    unsigned char* GetAbsoluteAddress(unsigned char*, int, int);

    unsigned char* ResolveRelativeAddress(unsigned char*, int);
    unsigned char* ResolveRelativeAddress(unsigned char*, int, int);
}