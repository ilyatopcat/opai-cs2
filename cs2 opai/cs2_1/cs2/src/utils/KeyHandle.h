#pragma once

#include <Windows.h>

class CKeyHandler
{
public:
    bool WasKeyPressed(int key, int key_style) {
        switch (key_style) {
        case 0:
            return HIWORD(GetKeyState(key));
        case 1:
            return LOWORD(GetKeyState(key));
        case 2:
            return true;
        default: return true;
        }
    }
};

inline CKeyHandler* KeyHandler = new CKeyHandler;