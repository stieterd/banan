#include <Windows.h>
#include <iostream>

#include "hooks.hpp"

#pragma comment(lib, "libMinHook.x64.lib")

HINSTANCE DllHandle;

void cheatMain(HMODULE hMod) {
    
    AllocConsole(); FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    if (!hooks::initialize())
    {
        std::cout << "[-]: Failed to place hooks. Aborting..." << std::endl;
        return;
    }

    std::cout << "[+]: Hooks placed!" << std::endl;

    while (1)
    {

    }

    return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DllHandle = hModule;
        CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)cheatMain, hModule, NULL, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

