// dllmain.cpp : Defines the entry point for the DLL application.
#include "Windows.h"
#include <iostream>
#include "MinHook.h"

#pragma comment(lib, "libMinHook.x64.lib")

#define NWORD DWORD

struct Vec2 {
    float x, y;
};
struct Vec3 {
    float x, y, z;
};

HINSTANCE DllHandle;

typedef void (*tSendPos)(void* player);
uintptr_t moduleBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
tSendPos pSendPosTarget = (tSendPos)(moduleBase + (uintptr_t)0x369C50);
tSendPos pSendPos = nullptr;

void hookedSendPos(void* player) {
    // Only get localplayer
    if (((bool(__cdecl*)(void*))((uintptr_t)moduleBase + (uintptr_t)0x36BDB0))(player)){

        printf("Localplayer: %p\n", player);
        int maxHealth = *(int*)((uintptr_t)player + (uintptr_t)0x40);
        printf("Maxhealth: %d\n", maxHealth);

        Vec3 pos = *(Vec3*)((uintptr_t)player + (uintptr_t)0x80);

        // Get kills
        short kills = ((short(__cdecl*)(void*))((uintptr_t)moduleBase + (uintptr_t)0x36BDD0))(player);
        printf("kills: %hd\n", kills);

        // take health
        //((void(__cdecl*)(void*, int))((uintptr_t)moduleBase + (uintptr_t)0x3692C0))(player, 100);
        
        // Set dead method
        ((void(__cdecl*)(void*, bool))((uintptr_t)moduleBase + (uintptr_t)0x36BE20))(player, true);
    }
    else {
        // Set dead method
        // ((void(__cdecl*)(void*, bool))((uintptr_t)moduleBase + (uintptr_t)0x36BE20))(player, true);
    }

    return pSendPos(player);
}

NWORD __stdcall EjectThread(LPVOID lpParameter) {
    Sleep(100);
    FreeLibraryAndExitThread(DllHandle, 0);
    return 0;
}

void shutdown(std::string reason) {

    MH_Uninitialize();
    printf("%s\n", reason);
    Sleep(1000);
    FreeConsole();
    CreateThread(0, 0, EjectThread, 0, 0, 0);
    return;
}

void main() {

    MH_STATUS status = MH_Initialize();
    
    if (MH_CreateHook((void**)pSendPosTarget, &hookedSendPos, (void**)(&pSendPos)) != MH_OK) {
        shutdown("PeekMessageA CreateHook failed!");
        return;
    }
    printf("Works");
    if (MH_EnableHook((void**)pSendPosTarget) != MH_OK) {
        shutdown("Hook failed!");
        return ;
    }
    while (true) {
        if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
            break;
        }
    }
    shutdown("Stopped");
}

NWORD v1ce(HMODULE hMod) {
    
    AllocConsole();
    FILE* f;
    (void)freopen_s(&f, "CONIN$", "r", stdin);
    (void)freopen_s(&f, "CONOUT$", "w+", stdout);
    SetStdHandle(STD_INPUT_HANDLE, stdin);
    SetStdHandle(STD_OUTPUT_HANDLE, stdout);

    printf("Excellent knowledge with Microsoft Word and excel\n");
    main();
    
    //FreeConsole();
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
        DllHandle = hModule;
        CloseHandle(CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)v1ce, hModule, NULL, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

