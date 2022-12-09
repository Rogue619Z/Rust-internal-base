namespace Drawing
{
	ImDrawList* DrawList = nullptr;

	void CenterText(const char* text)
	{
		if (text == nullptr)
			return;

		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();


	}
	inline void DrawFilledBox(const Vector2& vecStart, const Vector2& vecEnd, ImU32 col) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(vecStart.x, vecStart.y), ImVec2(vecStart.x + vecEnd.x, vecStart.y + vecEnd.y), col);
	}

	inline void DrawOutlineBox(const Vector2& pos, const Vector2& size, ImU32 col) {

		float thickness = 1.0f;

		DrawFilledBox(Vector2(pos.x, pos.y - thickness), Vector2(size.x + 1, thickness), col);
		DrawFilledBox(Vector2(pos.x, pos.y + size.y), Vector2(size.x + 1, thickness), col);

		DrawFilledBox(Vector2(pos.x - thickness, pos.y - thickness), Vector2(thickness, size.y + thickness * 2), col);
		DrawFilledBox(Vector2(pos.x + size.x, pos.y - thickness), Vector2(thickness, size.y + thickness * 2), col);
	}
	void CTHookIndicators() {
		Vector2 FlyHackBarSize = Vector2(600, 8);
		int FlyHackYStart = 50; // 50 looks perfect Y
		float xs = screen_center.x, ys = screen_center.y;

		DrawList = ImGui::GetBackgroundDrawList();
		struct Indicator_t { ImColor color; std::string text; bool draw_bar = false; float percentage = 0.f; };
		std::vector< Indicator_t > indicators{ };

		if (Input::GetKey(Enums::KeyCode::X)) {
			float desyncTime = rust::globals::last_tick_time;
			auto percentage = (((desyncTime) * 100.0f)) / 100;
			Indicator_t ind{ };
			ind.color = ImColor(215, 230, 10);
			ind.text = ("DESYNC TIME");
			ind.draw_bar = true;
			ind.percentage = percentage;

			indicators.push_back(ind);
		}

		// iterate and draw indicators.
		for (size_t i{ }; i < indicators.size(); ++i) {
			auto& indicator = indicators[i];

			float xs = 80, ys = screen_size.y - 67 - (32 * i);

			Vector2 BarSize = Vector2(110, 10);

			if (indicator.draw_bar) {
				DrawFilledBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x, BarSize.y), ImColor{ 0, 0, 0, 255 });
				DrawFilledBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x * (indicator.percentage), BarSize.y), indicator.color);
				DrawOutlineBox(Vector2(xs - BarSize.x / 2, ys), Vector2(BarSize.x, BarSize.y), ImColor{ 0, 0, 0 });

				DrawList->AddText({ 25 + BarSize.x / 2 - ImGui::CalcTextSize(indicator.text.c_str()).x / 2, screen_size.y - 80 - (32 * i) }, indicator.color, indicator.text.c_str());
			}
			else
				DrawList->AddText({ 25 + BarSize.x / 2 - ImGui::CalcTextSize(indicator.text.c_str()).x / 2, screen_size.y - 80 - (24 * i) }, indicator.color, indicator.text.c_str());
		}

		// replace with checkbox (2lazy rn im almost sleeping) owo
		if (true) {
			DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0, 255 });
			DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x * (AntiHackV::FlyHack::flyhackDistanceVertical / AntiHackV::FlyHack::flyhackDistanceVerticalMax), FlyHackBarSize.y), ImColor(255, 0, 0));
			DrawOutlineBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0 });
		}

		if (true) {
			DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(FlyHackBarSize.x, FlyHackBarSize.y), ImColor{ 0, 0, 0, 255 });
			DrawFilledBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(FlyHackBarSize.x * (AntiHackV::FlyHack::flyhackDistanceHorizontal / AntiHackV::FlyHack::flyhackDistanceHorizontalMax), FlyHackBarSize.y), ImColor(255, 0, 0));
			DrawOutlineBox(Vector2(xs - FlyHackBarSize.x / 2, FlyHackYStart + (FlyHackBarSize.y + 5)), Vector2(600, FlyHackBarSize.y), ImColor{ 0, 0, 0 });
		}
	}
	inline void DrawHealthBar(const Vector2& vecStart, const Vector2& vecEnd, float distance, int health, int maxhealth) {
		// i literally tried to do dynamic color like green to red but this shit aint working i dont fucking know why and this is so embarassing but i dont really care at this point anymore im just frustrated... i really hate to do uncompleted stuff but i dont really care anymore im really fucking shitt right now and i just did nigger stuff and idk i dont care
		auto x = vecStart.x;
		auto y = vecStart.y;

		auto w = vecEnd.x - vecStart.x;
		auto h = vecEnd.y - vecStart.y;

		auto Percentage = health * (h / maxhealth);
		float HeightOffset = max(w / 8.f, 8.f);

		DrawOutlineBox(Vector2(x - HeightOffset - 1, y), Vector2(2, h), ImColor(0, 0, 0, 170));
		DrawFilledBox(Vector2(x - HeightOffset - 1, y), Vector2(2, h), ImColor(0, 0, 0, 170));
		DrawFilledBox(Vector2(x - HeightOffset - 1, y + h - Percentage), Vector2(2, Percentage), ImColor(0, 200, 0, 255));
	}
	inline void CreateLine(Vector3 p0, Vector3 p1, ImColor color)
	{
		TempILines.push_front(ILine(p0, p1, color));
	}

	inline void CreateBoneLine(int b0, int b1, ImColor color, BasePlayer* basePlayer)
	{
		if (b0 == Enums::BoneList(Enums::BoneList::head))
		{
			auto bb = basePlayer->get_bone_transform(Enums::BoneList(b0))->position();
			CreateLine(bb, basePlayer->get_bone_transform(Enums::BoneList(b1))->position(), color);
		}
		else CreateLine(basePlayer->get_bone_transform(Enums::BoneList(b0))->position(), basePlayer->get_bone_transform(Enums::BoneList(b1))->position(), color);
	}
	static auto SkeletonESP(BasePlayer* basePlayer, ImColor Skeleton) -> void
	{
		if (true)
		{
			CreateBoneLine(Enums::BoneList(Enums::head), Enums::BoneList(Enums::neck), Skeleton, basePlayer);

			{
				CreateBoneLine(Enums::BoneList(Enums::neck), Enums::BoneList(Enums::l_clavicle), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_clavicle), Enums::BoneList(Enums::l_upperarm), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_upperarm), Enums::BoneList(Enums::l_forearm), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_forearm), Enums::BoneList(Enums::l_ulna), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_ulna), Enums::BoneList(Enums::l_hand), Skeleton, basePlayer);
			}

			{
				CreateBoneLine(Enums::BoneList(Enums::neck), Enums::BoneList(Enums::r_clavicle), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_clavicle), Enums::BoneList(Enums::r_upperarm), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_upperarm), Enums::BoneList(Enums::r_forearm), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_forearm), Enums::BoneList(Enums::r_ulna), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_ulna), Enums::BoneList(Enums::r_hand), Skeleton, basePlayer);
			}

			CreateBoneLine(Enums::BoneList(Enums::neck), Enums::BoneList(Enums::spine4), Skeleton, basePlayer);
			CreateBoneLine(Enums::BoneList(Enums::spine4), Enums::BoneList(Enums::spine3), Skeleton, basePlayer);
			CreateBoneLine(Enums::BoneList(Enums::spine3), Enums::BoneList(Enums::spine2), Skeleton, basePlayer);
			CreateBoneLine(Enums::BoneList(Enums::spine2), Enums::BoneList(Enums::spine1), Skeleton, basePlayer);
			{
				CreateBoneLine(Enums::BoneList(Enums::spine1), Enums::BoneList(Enums::l_hip), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::spine1), Enums::BoneList(Enums::l_hip), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_hip), Enums::BoneList(Enums::l_knee), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_knee), Enums::BoneList(Enums::l_ankle_scale), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_ankle_scale), Enums::BoneList(Enums::l_foot), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::l_foot), Enums::BoneList(Enums::l_toe), Skeleton, basePlayer);
			}

			{
				CreateBoneLine(Enums::BoneList(Enums::spine1), Enums::BoneList(Enums::r_hip), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::spine1), Enums::BoneList(Enums::r_hip), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_hip), Enums::BoneList(Enums::r_knee), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_knee), Enums::BoneList(Enums::r_ankle_scale), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_ankle_scale), Enums::BoneList(Enums::r_foot), Skeleton, basePlayer);
				CreateBoneLine(Enums::BoneList(Enums::r_foot), Enums::BoneList(Enums::r_toe), Skeleton, basePlayer);
			}
		}
	}

	static auto player_loop() -> void
	{
		if (!LocalPlayer::Entity())
			return;

		if (!DrawList)
			DrawList = ImGui::GetWindowDrawList();

		if (!camera)
			return;


		//CTHookIndicators();

		//for (const ILine& iLine : ILines)
		//{
		//	Vector2 startPosition; Vector2 endPosition;

		//	auto p0w = unity::w2s(iLine.Start, startPosition);
		//	auto p1w = unity::w2s(iLine.End, endPosition);
		//	if ((p0w && p1w))
		//		DrawList->AddLine(ImVec2(startPosition.x, startPosition.y), ImVec2(endPosition.x, endPosition.y), iLine.Color);
		//}



		for (renderer::player_array::base_vector& basePlayerV3 : renderer::player_array::base_vector_list)
		{
			const auto& player = basePlayerV3.player;

			if (!memory::valid_pointer(player))
				continue;


			ImColor color = ImColor{ 255, 0, 0, 255 };
			if (basePlayerV3.LineOfSight)
			{
				color = ImColor{ 0, 255, 0, 255 };
			}

			//SkeletonESP(player, color);


			Vector2 footPos = Vector2::Zero();
			if (unity::w2s(basePlayerV3.player_pos, footPos))
			{
				float y = 0.0f;

				if (true)
				{
					char buf[64] = { 0 }; sprintf_s(buf, "%ls", player->_displayName()->buffer);

					renderer::add_text(ImVec2(footPos.x, footPos.y + y), buf, color);
				}
				y += 12.0f;
				if (true)
				{
					char buf[64] = { 0 }; sprintf_s(buf, "%.f HP", player->_health());

					renderer::add_text(ImVec2(footPos.x, footPos.y + y), buf, color);
				}
				y += 12.0f;
				if (true)
				{
					char buf[64] = { 0 }; sprintf_s(buf, "%.f M", basePlayerV3.local_pos.Distance(basePlayerV3.player_pos));

					renderer::add_text(ImVec2(footPos.x, footPos.y + y), buf, color);
				}
			}
		}

	}
}
																	