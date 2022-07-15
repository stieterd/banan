#include <Windows.h>

#include "MinHook.h"
#include "game.hpp"

namespace hooks
{
	bool initialize();

	namespace funcs
	{
		void hookedClientPlayerUpdate(game::structs::ClientPlayer* player);
	}
}
