
auto Hooks::ClientUpdate(BasePlayer* player) -> void
{
	if (!player && !player->PlayerValid())
		return Hooks::ClientUpdatehk.get_original< decltype(&ClientUpdate)>()(player);


	Hooks::ClientUpdatehk.get_original< decltype(&ClientUpdate)>()(player);
}