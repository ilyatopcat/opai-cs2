#pragma once

template <typename T>
class CUtlVector {
public:
    auto begin() const { return data; }
    auto end() const { return data + size; }

    auto At(int i) const { return data[i]; }
    auto AtPtr(int i) const { return data + i; }

    bool Exists(T val) const {
        for (const auto& it : *this)
            if (it == val) return true;
        return false;
    }
    bool IsEmpty() const { return size == 0; }

    int size;
    char pad0[0x4];
    T* data;
    char pad1[0x8];
};

class CUtlString {
public:
    const char* Get() {
        return m_Data;
    }

    const char* m_Data;
};