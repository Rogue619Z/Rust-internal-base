auto Hooks::ClientCycle(BasePlayer* player, float deltaTime) -> void
{


	Hooks::ClientCyclehk.get_original< decltype(&ClientCycle)>()(player, deltaTime);
}