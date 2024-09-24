#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <thread>

#include "hooks/hooks.h"
#include "sdk/entity/entity.h"
#include "sdk/interfaces/interfaces.h"
#include "features/events/events.h"

FILE* console_file;

void OnDetach(HMODULE instance) {
    Hooks::Uninitialize();

    Interfaces::particleSystem = nullptr;
    Interfaces::particleManager = nullptr;
    Interfaces::globalVars = nullptr;

    Entity::LevelShutdown();

    if (console_file)
        fclose(console_file);
    
    FreeConsole();
    FreeLibraryAndExitThread(instance, 0);
}

void OnAttach(HINSTANCE instance) {
    AllocConsole();
    SetConsoleTitleA("CS2 DEBUG");

    freopen_s(&console_file, "CONOUT$", "w", stdout);

    if (Interfaces::Initialize()) {
        printf("[Interfaces] Initialized \n");

        Entity::Initialize();

        Events->Intilization();

        Interfaces::cvar->UnlockHidden();

        SkinChanger::OnInit();

        if (Hooks::Initialize())
            printf("[Hooks] Initialized \n");
    }

    while (!GetAsyncKeyState(VK_END))
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    OnDetach(instance);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instance);

        const HANDLE thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(OnAttach), instance, 0, 0);
        if (thread)
            CloseHandle(thread);
    }

    return TRUE;
}