
auto Hooks::OnDisconnected(Connection* connect) -> void
{





	Hooks::OnDisconnectedhk.get_original< decltype(&OnDisconnected)>()(connect);
}