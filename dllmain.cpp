#include "Core/Core.hpp"

bool DllMain(void*, std::uint32_t callReason, void*)
{
	if (callReason != 1)
		return false;

	if (AllocConsole()) {
		SetConsoleTitleA("[+] Debug Console");
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	}

	Il2CppWrapper::il2cpp_thread_attach();
	{
		if (MH_Initialize() != MH_OK)
			return false;

		Hooks::Start();

	}
	ConsoleLOG("Injected");






	return true;

}