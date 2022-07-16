#pragma once

#include <Windows.h>

namespace game
{
	namespace structs
	{
		struct Color
		{
			float r, g, b, a;
		};

		enum Team
		{
			Red, Blue
		};

		struct MultiplayerWeapon
		{
			float getReloadTime() { return *(float*)(this + 0x74); }
			float getSpreadAngle() { return *(float*)(this + 0x48); }
		};

		struct ClientPlayer
		{
			int getMaxHealth() { return *(int*)(this + 0x40); }
			int getHealth() { return *(int*)(this + 0x3C); }

			bool isLocal() 
			{ 
				uintptr_t base = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
				return (((bool (*)(ClientPlayer*)) (base + 0x36BDB0)))(this); 
			}

			void DisplayName()
			{
				uintptr_t base = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
				(((void (*)(ClientPlayer*)) (base + 0x35DA80)))(this);
			}

			void OutlineDisplay(Color color)
			{
				uintptr_t base = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
				(((void (*)(ClientPlayer*, Color)) (base + 0x35E710)))(this, color);
			}

			Team getTeam() { return *(Team*)(this + 0x118); }

			MultiplayerWeapon* getCurrentWeapon() { return *(MultiplayerWeapon**)(this + 0xA8); }
		};
	}

	extern structs::ClientPlayer* localPlayer;
}