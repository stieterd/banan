#include "hooks.hpp"

#include <iostream>

namespace hooks
{
	namespace defs
	{
		typedef void (*tClientPlayerUpdate)(void* player);
		tClientPlayerUpdate ClientPlayerUpdate = (tClientPlayerUpdate)(game::base + (uintptr_t)0x369C50);
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
	if (player->isLocal())
	{
		game::localPlayer = player;
	}
	else
	{
		if (!game::localPlayer)
		{
			return defs::ClientPlayerUpdateOriginal(player);
		}

		if (player->getTeam() == game::localPlayer->getTeam() /*&& mode == teamdeathmatch*/)
		{

		}

		player->getOutline()->setOutlineWidth(2.0);
		player->OutlineDisplay(game::structs::Color{ 1.0,0.0,0.0,1.0 });
		player->DisplayName();
	}

	return defs::ClientPlayerUpdateOriginal(player);
}
