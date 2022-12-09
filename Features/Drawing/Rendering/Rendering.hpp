namespace renderer
{
	namespace player_array
	{
		class base_vector
		{
		public:
			base_vector(BasePlayer* player, Vector3 playerPos, Vector3 localPos, bool LOS)
			{
				this->player = player;
				this->player_pos = playerPos;
				this->local_pos = localPos;
				this->LineOfSight = LOS;
			}
			BasePlayer* player = nullptr;
			Vector3 player_pos = { 0,0,0 };
			Vector3 local_pos = { 0,0,0 };
			bool LineOfSight = false;

		};
		std::vector<base_vector> base_temp_vector_list;
		std::vector<base_vector> base_vector_list;
	}



	static auto get_target(BasePlayer* player) -> float
	{
		if (!player)
			return 1000.0f;

		Vector2 ScreenPos;
		if (!camera->WorldToScreen(player->transform()->position(), ScreenPos)) return 1000.0f;
		return Vector2(Screen::width() / 2, Screen::height() / 2).Distance(ScreenPos);
	}
	auto add_text(ImVec2 pos, char* text, ImColor color) -> void
	{
		auto DrawList = ImGui::GetForegroundDrawList();
		auto wText = text;

		auto Size = ImGui::CalcTextSize(wText);
		pos.x -= Size.x / 2.f;
		pos.y -= Size.y / 2.f;

		//	ImGui::PushFont(m_font);

		DrawList->AddText(ImVec2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0, 255), wText);
		DrawList->AddText(ImVec2(pos.x - 1, pos.y - 1), ImColor(0, 0, 0, 255), wText);
		DrawList->AddText(ImVec2(pos.x, pos.y), color, wText);

		//	ImGui::PopFont();
	}
}