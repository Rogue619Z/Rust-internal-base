#pragma once
#include "safe_mem.h"
#include <cstdint>
#include <vector>
#include <Core.hpp>
static bool show_menu = true;
inline ImDrawList* DrawList;







namespace mem
{
	template<typename T> T read(uintptr_t address) {
		try { return *(T*)address; }
		catch (...) { return T(); }
	}

	template<typename T> void write(uintptr_t address, T value) {
		try { *(T*)address = value; }
		catch (...) { return; }
	}

	template<typename T> T ReadChain(uintptr_t address, std::vector<unsigned int> pointers)
	{
		uintptr_t addr = address;
		for (unsigned int i = 0; i < pointers.size(); ++i)
		{

			mem::read<T>(addr) + pointers[i];
			addr += pointers[i];
		}
		return addr;
	}
}

namespace SDK
{
	uintptr_t Base;
	uintptr_t GameAssembly;
	uintptr_t UnityPlayer;
	uintptr_t Graphics = 0x3635C10;
}



namespace VARS
{
	bool Drawing = true;
	bool drawnpc = true;
	bool Silent = true;
	bool Noclip = false;
	bool Prediction = true;
	bool healthbar = true;
	bool fovcircle = true;
	bool instantoka = false;
	float desiredthickbullet = 0.85f;
	bool fakeadmin = false;
	bool NoRecoil = false;
	float f_circlefov = 90.0f;
	//float desiredfov = 120.0f
	float fov_circle_color[3] = { 255.0f, 255.0f, 255.0f };
}