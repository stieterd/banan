#pragma once

#include <Windows.h>

namespace game
{
	inline uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleW(L"GameAssembly.dll"));

	namespace structs
	{
		struct Vector3
		{
			float x, y, z;
		};

		struct Color
		{
			float r, g, b, a;
		};

		enum Team
		{
			Red, Blue
		};

		struct Transform
		{
			void LookAt(Vector3 worldPosition)
			{
				(((void (*)(Transform*, Vector3)) (base + 0x1A7E3A0)))(this, worldPosition);
			}
		};

		struct MultiplayerWeapon
		{
			float getReloadTime() { return *(float*)(this + 0x74); }
			float getSpreadAngle() { return *(float*)(this + 0x48); }

			Transform* getTipTransform() { return *(Transform**)(this + 0x40); }
		};

		struct ClientPlayer
		{
			int getMaxHealth() { return *(int*)(this + 0x40); }
			int getHealth() { return *(int*)(this + 0x3C); }

			bool isLocal() 
			{ 
				return (((bool (*)(ClientPlayer*)) (base + 0x36BDB0)))(this); 
			}

			void DisplayName()
			{
				(((void (*)(ClientPlayer*)) (base + 0x35DA80)))(this);
			}

			void OutlineDisplay(Color color)
			{
				(((void (*)(ClientPlayer*, Color)) (base + 0x35E710)))(this, color);
			}

			Team getTeam() { return *(Team*)(this + 0x118); }

			MultiplayerWeapon* getCurrentWeapon() { return *(MultiplayerWeapon**)(this + 0xA8); }

			Vector3 getDesiredPos() { return *(Vector3*)(this + 0x80); }

			Transform* getHeadTransform() { return *(Transform**)(this + 0x130); }
			Transform* getAimTargetTransform() { return *(Transform**)(this + 0x138); }
		};
	}

	inline structs::ClientPlayer* localPlayer;
}