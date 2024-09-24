#include "utils.h"

#include <Windows.h>
#include <vector>

uint8_t* Utils::OpcodeScan(const char* moduleName, const char* pattern) {
    static auto pattern_to_byte = [](const char* pattern) {
        std::vector<int> bytes = std::vector<int>{};
        char* start = const_cast<char*>(pattern);
        char* end = const_cast<char*>(pattern) + strlen(pattern);

        for (char* current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }

        return bytes;
    };

    void* moduleHandle = GetModuleHandle(moduleName);
    if (moduleHandle == nullptr)
        return nullptr;

    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleHandle);
    PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(moduleHandle) + dosHeader->e_lfanew);

    auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto patternBytes = pattern_to_byte(pattern);
    auto scanBytes = reinterpret_cast<uint8_t*>(moduleHandle);

    auto patternSize = patternBytes.size();
    auto patternData = patternBytes.data();

    for (unsigned int i = 0; i < sizeOfImage - patternSize; i++) {
        bool found = true;

        for (unsigned int j = 0; j < patternSize; ++j) {
            if (scanBytes[i + j] != patternData[j] && patternData[j] != -1) {
                found = false;

                break;
            }
        }

        if (found)
            return &scanBytes[i];
    }

    return nullptr;
}

uint8_t* Utils::OpcodeScan(const char* moduleName, const char* pattern, int offset) {
    return OpcodeScan(moduleName, pattern) + offset;
}

uint8_t* Utils::OpcodeScanRelative(const char* moduleName, const char* pattern, int offset, int RVAOffset) {
    uint8_t* address = OpcodeScan(moduleName, pattern, offset);
    if (address == nullptr)
        return nullptr;

    return ResolveRelativeAddress(address, RVAOffset, 0);
}

uint8_t* Utils::OpcodeScanRelative(const char* moduleName, const char* pattern, int offset, int RVAOffset, int RIPOffset) {
    uint8_t* address = OpcodeScan(moduleName, pattern, offset);
    if (address == nullptr)
        return nullptr;

    return ResolveRelativeAddress(address, RVAOffset, RIPOffset);
}

uint8_t* Utils::OpcodeScanAbsolute(const char* moduleName, const char* pattern) {
    uint8_t* address = OpcodeScan(moduleName, pattern);
    if (address == nullptr)
        return nullptr;

    return GetAbsoluteAddress(address);
}

uint8_t* Utils::OpcodeScanAbsolute(const char* moduleName, const char* pattern, int preOffset) {
    uint8_t* address = OpcodeScan(moduleName, pattern);
    if (address == nullptr)
        return nullptr;

    return GetAbsoluteAddress(address, preOffset);
}

uint8_t* Utils::OpcodeScanAbsolute(const char* moduleName, const char* pattern, int preOffset, int postOffset) {
    uint8_t* address = OpcodeScan(moduleName, pattern);
    if (address == nullptr)
        return nullptr;

    return GetAbsoluteAddress(address, preOffset, postOffset);
}

unsigned __int64 Utils::ExportFn(unsigned __int64 base, const char* procedure_name)
{
    const auto dos_headers = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
    if (dos_headers->e_magic != IMAGE_DOS_SIGNATURE)
        return 0;

    const auto nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS64*>(base + dos_headers->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE)
        return 0;

    const std::uintptr_t export_directory_size = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
    const std::uintptr_t export_directory_address = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

    if (export_directory_size == 0u || export_directory_address == 0u)
        return 0;

    const auto exports = reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(base + export_directory_address);
    const auto names_rva = reinterpret_cast<const std::uint32_t*>(base + exports->AddressOfNames);
    const auto name_ordinals_rva = reinterpret_cast<const std::uint16_t*>(base + exports->AddressOfNameOrdinals);
    const auto functions_rva = reinterpret_cast<const std::uint32_t*>(base + exports->AddressOfFunctions);

    std::size_t right = exports->NumberOfNames, left = 0u;
    while (right != left)
    {
        const std::size_t middle = left + ((right - left) >> 1u);
        const int result = strcmp(procedure_name, reinterpret_cast<const char*>(base + names_rva[middle]));

        if (result == 0)
        {
            const std::uint32_t function_rva = functions_rva[name_ordinals_rva[middle]];

            if (function_rva >= export_directory_address && function_rva - export_directory_address < export_directory_size)
                break;

            return base + function_rva;
        }

        if (result > 0)
            left = middle + 1;
        else
            right = middle;
    }
    return 0;
}

uint8_t* Utils::GetAbsoluteAddress(unsigned char* address, int preOffset, int postOffset) {
    address += preOffset;
    address += *reinterpret_cast<std::int32_t*>(address) + 0x4;
    address += postOffset;

    return address;
}

uint8_t* Utils::GetAbsoluteAddress(unsigned char* address, int preOffset) {
    return GetAbsoluteAddress(address, preOffset, 0);
}

uint8_t* Utils::GetAbsoluteAddress(unsigned char* address) {
    return GetAbsoluteAddress(address, 0, 0);
}

uint8_t* Utils::ResolveRelativeAddress(unsigned char* address, int RVAOffset, int RIPOffset) {
    uint32_t RVA = *reinterpret_cast<uint32_t*>(address + RVAOffset);
    uint64_t RIP = reinterpret_cast<uint64_t>(address) + RIPOffset;

    return reinterpret_cast<uint8_t*>(RVA + RIP);
}

uint8_t* Utils::ResolveRelativeAddress(unsigned char* address, int RVAOffset) {
    return ResolveRelativeAddress(address, RVAOffset, 0x0);
}