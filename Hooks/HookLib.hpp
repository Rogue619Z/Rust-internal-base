#pragma once

#include "Minhook/include/minhook.h"

class Pointer
{
private:
	uintptr_t m_original{ 0 };
public:
	auto InitialiseHook(void* ourFunction, const char* nameSpace, const char* klass, const char* method, int argCount = -1) -> void
	{
		auto il2cppMethod = *reinterpret_cast<uintptr_t*>(Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, argCount));
		m_original = *reinterpret_cast<uintptr_t*>(il2cppMethod);
		*reinterpret_cast<void**>(il2cppMethod) = ourFunction;
	}
};

class VMT
{
private:
	std::uintptr_t m_original{ 0 };
public:

	auto InitialiseHook(const char* nameSpace, const char* klass, const char* method, void* ourFunction, int argCount = -1) -> void
	{
		const auto searchMethod = *reinterpret_cast<std::uintptr_t*>(Il2CppWrapper::GetClassFromName(nameSpace, klass)->GetMethodFromName(method, argCount));
		const auto classBase = *reinterpret_cast<std::uintptr_t*>(Il2CppWrapper::GetClassFromName(nameSpace, klass));

		if (searchMethod == std::uintptr_t(ourFunction))
		{
			return;
		}
		else
		{
			printf("init hook sucessfully");
		}

		for (auto idx{ classBase }; idx <= classBase + 0x1500; idx += 0x1) {
			const auto Address = *reinterpret_cast<std::uintptr_t*>(idx);
			if (Address == searchMethod)
			{
				m_original = searchMethod;
				*reinterpret_cast<uintptr_t*>(idx) = std::uintptr_t(ourFunction);
			}
		}
	}


	template< typename type >
	auto get_original() -> type { return reinterpret_cast<type>(m_original); }

};
class HookLib
{
private:
	uintptr_t m_original{ 0 };
public:

	auto InitializeHook(const char* name_space, const char* klass, const char* method, void* our_function) -> void
	{
		auto function = *reinterpret_cast<void**>(Il2CppWrapper::GetClassFromName(name_space, klass)->GetMethodFromName(method));

		if (!function)
		{
			printf("[ DEBUG ] Failed to hook %s.\n", method);
		}
		else
			printf("[ DEBUG ] Hooked %s.\n", method);

		MH_CreateHook((void*)function, our_function, (void**)&m_original);
		MH_EnableHook(function);
	}


	template< typename t>
	auto get_original() -> t
	{
		return reinterpret_cast<t>(m_original);
	}
};