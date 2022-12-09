#include "../../Hooks/Hooks.hpp"
static auto box(BasePlayer* player, CornerBox cornerBox) -> void
{
}
auto Hooks::UnityGui(OnGUI* DDraw) -> void
{
	if (!LocalPlayer::Entity())
		return;

	if (!camera)
		return;


	const auto current = Event::current();
	const auto event_type = current->type();

	if (event_type == EventType::Repaint)
	{
		//camera = Camera::main();

		if (rust::globals::target != nullptr) {
			if (!rust::globals::target->PlayerValid() || rust::globals::target->IsDead() || renderer::get_target(rust::globals::target) > 500.0f) {
				rust::globals::target = nullptr;
			}
		}

		if (const auto visiblePlayerList = BasePlayer::playerList())
		{
			if (!memory::valid_pointer(visiblePlayerList))
				return;

			const auto buffer = std::uintptr_t(visiblePlayerList->vals->buffer);
			if (!memory::valid_pointer(buffer))
				return;

			const auto size = std::int32_t(visiblePlayerList->vals->size);
			if (size <= 0)
				return;

			for (size_t idx{ 0 }; idx <= size; idx++)
			{

				const auto& player = *reinterpret_cast<BasePlayer**>(buffer + 0x20 + (idx * 0x8));


				if (!memory::valid_pointer(player))
					continue;

				if (player == LocalPlayer::Entity())
					continue;

				if (!player->PlayerValid())
					continue;

				if (player->IsDead())
					continue;

				if (!player->model())
					continue;

				if (!memory::valid_pointer(player->transform()))
					continue;

				//if (!memory::valid_pointer(player->transform()->position()))
				//	continue;

				//if (player->playerModel()->PlayerNPC())
				//	continue;
			

				auto LineOfSight = IsVisible(LocalPlayer::Entity()->get_bone_transform(48)->position() + rust::globals::spoofed_eye_pos, player->get_bone_transform(48)->position());

				renderer::player_array::base_temp_vector_list.push_back(renderer::player_array::base_vector(player, player->transform()->position(), LocalPlayer::Entity()->transform()->position(), LineOfSight));


				if (renderer::get_target(player) < 500.0f) {
					if (rust::globals::target == nullptr)
						rust::globals::target = player;
					else if (renderer::get_target(rust::globals::target) > renderer::get_target(player))
						rust::globals::target = player;

				}

			}
			ILines = TempILines;
			TempILines.clear();

			renderer::player_array::base_vector_list = renderer::player_array::base_temp_vector_list;
			renderer::player_array::base_temp_vector_list.clear();
		}
	}
}