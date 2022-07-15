#pragma once

#include <Windows.h>

namespace game
{
	namespace structs
	{
		struct ClientPlayer
		{
			int getMaxHealth() { return *(int*)(this + 0x40); }
			int getHealth() { return *(int*)(this + 0x3C); }
		};
	}
}
