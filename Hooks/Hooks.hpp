#pragma once

#include "HookLib.hpp"

#define CREATE_HOOK( type, name, args ) inline static HookLib name##hk; static type name args; // minhook hooking
#define VMT_HOOK( type, name, args ) inline static VMT name##hk; static type name args; //il2cpp hooking but not working ????
#define POINTER_HOOK( type, name, args ) inline static Pointer name##hk; static type name args; //pointer hook

#define HOOK_CUSTOM( addr, orig, repl ) orig = *addr; *addr = reinterpret_cast< std::uintptr_t >( repl ); 


class Hooks
{
private:
	CREATE_HOOK(void, ClientInput, (BasePlayer*, uintptr_t* state));
	CREATE_HOOK(void, UnityGui, (OnGUI*));
	CREATE_HOOK(void, DoMovement, (Projectile*, float));
	CREATE_HOOK(void, TraceAll, (HitTest*, void* traces, int));
	CREATE_HOOK(void, ClientUpdate, (BasePlayer*));
	CREATE_HOOK(bool, DoHit, (Projectile*, HitTest*, Vector3, Vector3));
	CREATE_HOOK(void, PerformanceUpdate, (void*));
	CREATE_HOOK(void, OnDisconnected, (Connection*))
	CREATE_HOOK(void, SendClientTick, (BasePlayer*));
	CREATE_HOOK(void, ClientCycle, (BasePlayer*, float));
public:
	static auto Start() -> void;
	static auto Unhook() -> void;
};
namespace CustomHook
{
	static std::uintptr_t ProjectileShootRpchk;
	static auto ProjectileShootRpc(void* _rcx, void* _rdx, void* a1, std::uint64_t projectile_shoot, void* a3) -> void;
	static auto OnProjectileShootRpc(std::uint64_t instance) -> void;
}

auto Hooks::Start() -> void
{
	const auto SwapChainFn = reinterpret_cast<IDXGISwapChain * (*)()>(utl::pattern::find(L"UnityPlayer.dll", "48 83 ec 28 e8 ? ? ? ? 48 8b 80 a0 03 00 00"))();
	if (!SwapChainFn)
		return;
	static auto SwapChain = *reinterpret_cast<PVOID**> (SwapChainFn);
	static auto PresentAddr = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(SwapChain[8]);
	MH_CreateHook(PresentAddr, Present::PresentHk, &Present::o_present);
	MH_EnableHook(PresentAddr);

	Hooks::PerformanceUpdatehk.InitializeHook("Facepunch", "PerformanceUI", "Update", &Hooks::PerformanceUpdate);
	Hooks::UnityGuihk.InitializeHook("UnityEngine", "DDraw", "OnGUI", &Hooks::UnityGui);
	Hooks::ClientUpdatehk.InitializeHook("", "BasePlayer", "ClientUpdate", Hooks::ClientUpdate);
	Hooks::ClientInputhk.InitializeHook("", "BasePlayer", "ClientInput", &Hooks::ClientInput);
	Hooks::SendClientTickhk.InitializeHook("", "BasePlayer", "SendClientTick", &Hooks::SendClientTick);
	Hooks::DoMovementhk.InitializeHook("", "Projectile", "DoMovement", &Hooks::DoMovement);
	Hooks::DoHithk.InitializeHook("", "Projectile", "DoHit", &Hooks::DoHit);
	Hooks::TraceAllhk.InitializeHook("", "GameTrace", "TraceAll", &Hooks::TraceAll);


	rust::globals::initalized = true;
}

bool doOnce = true;
auto Hooks::Unhook() -> void
{
	if (doOnce) {
		rust::globals::initalized = false;
		camera = nullptr;
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);

		doOnce = true;
	}
	ConsoleLOG("Hooks Unloaded.\n");
}