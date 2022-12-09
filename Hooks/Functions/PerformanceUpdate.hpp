
auto Hooks::PerformanceUpdate(void* instance) -> void
{
	//unity::matrix = unity::viewMatrix();
	static auto visiblePlayerList = BasePlayer::playerList();

	if (!visiblePlayerList || visiblePlayerList->vals->size == 0 || !memory::valid_pointer(visiblePlayerList) || !camera)
	{
	//	unity::matrix = unity::viewMatrix();
		camera = Camera::main();
		rust::globals::target = nullptr;
	}


	Hooks::PerformanceUpdatehk.get_original<decltype(&PerformanceUpdate)>()(instance);
}