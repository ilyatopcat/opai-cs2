#include <iostream>

uint64_t uiSeed = 0xCBF29CE484222325;
uint64_t uiPrime = 0x1000193;

uint64_t Hash(const char* text) {
    uint64_t hash = uiSeed;

    for (int i = 0; i < strlen(text); i++) {
        hash ^= text[i];
        hash *= uiPrime;
    }

    return hash;
}