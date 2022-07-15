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
		};
	}
}
