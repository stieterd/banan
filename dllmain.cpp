// dllmain.cpp : Defines the entry point for the DLL application.
#include "Windows.h"

#define NWORD DWORD

NWORD v1ce(HMODULE hMod) {

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

