#include "hooks.hpp"

#include <iostream>

namespace hooks
{
	namespace defs
	{
		uintptr_t moduleBase = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");

		typedef void (*tClientPlayerUpdate)(void* player);
		tClientPlayerUpdate ClientPlayerUpdate = (tClientPlayerUpdate)(moduleBase + (uintptr_t)0x369C50);
		tClientPlayerUpdate ClientPlayerUpdateOriginal = nullptr;
	}

	bool initialize()
	{
		MH_STATUS status = MH_Initialize();

		status = MH_CreateHook((void**)defs::ClientPlayerUpdate, &funcs::hookedClientPlayerUpdate, (void**)&defs::ClientPlayerUpdateOriginal);
		if (status != MH_OK) { return false; }

		status = MH_EnableHook((void**)defs::ClientPlayerUpdate);
		if (status != MH_OK) { return false; }

		return true;
	}
}

void hooks::funcs::hookedClientPlayerUpdate(game::structs::ClientPlayer* player)
{
	if (!player->isLocal())
	{
		player->DisplayName();
		player->OutlineDisplay(game::structs::Color{ 1, 0, 0, 1 });
	}

	return defs::ClientPlayerUpdateOriginal(player);
}
