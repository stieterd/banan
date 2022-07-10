// dllmain.cpp : Defines the entry point for the DLL application.
#include "Windows.h"
#include <iostream>

#define NWORD DWORD

NWORD v1ce(HMODULE hMod) {
    
    AllocConsole();
    FILE* f;
    (void)freopen_s(&f, "CONIN$", "r", stdin);
    (void)freopen_s(&f, "CONOUT$", "w+", stdout);
    SetStdHandle(STD_INPUT_HANDLE, stdin);
    SetStdHandle(STD_OUTPUT_HANDLE, stdout);

    printf("Excellent knowledge with Microsoft Word and excel\n");
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       NWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)InitHack, hModule, NULL, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

