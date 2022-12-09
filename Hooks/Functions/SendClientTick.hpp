
auto Hooks::SendClientTick(BasePlayer* player) -> void
{
	if (!player || player->HasFlag(Enums::Sleeping))
		return 	Hooks::SendClientTickhk.get_original< decltype(&SendClientTick)>()(player);

	__try
	{
		Vector3 current = player->transform()->position();
		Vector3 old = player->lastSentTick()->position();
	//	Vector3 vector4 = player->lastSentTick()->position();
		Vector3 overrided = Vector3(current.x, current.y, current.z);


		IsFlying(false, player);


		//if (AntiHackV::FlyHack::flyhackDistanceVertical >= (AntiHackV::FlyHack::flyhackDistanceVerticalMax))
		//{
		//	overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
		//}
		//if (AntiHackV::FlyHack::flyhackDistanceHorizontal >= (AntiHackV::FlyHack::flyhackDistanceHorizontalMax))
		//{
		//	overrided = Vector3(old.x, overrided.y, old.z);
		//}
		//if (AntiHackV::FlyHack::flyhackDistanceHorizontal > AntiHackV::FlyHack::flyhackDistanceHorizontalMax || AntiHackV::FlyHack::flyhackDistanceVertical > AntiHackV::FlyHack::flyhackDistanceVerticalMax)
		//{
		//	if (overrided != current) {
		//		player->ForcePositionTo(overrided);
		//	}
		//}
	
	}
	__except (true)
	{
		printf("Nibba");
	}


	Hooks::SendClientTickhk.get_original< decltype(&SendClientTick)>()(player);
}