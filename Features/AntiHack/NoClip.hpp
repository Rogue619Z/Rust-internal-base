static float NoClipRadius(float margin)
{
	return 0.5f - margin;
}
//bool TestNoClipping(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool spHerecast) {
//	int num = 429990145;
//	//Ulog("6");
//	Vector3 normalized = (newPos - oldPos).normalized();
//	Vector3 vector = oldPos - normalized * backtracking;
//	float magnitude = (newPos - vector).magnitude();
//
//	typedef bool (*RayCast)(Ray, float, int);
//
//	bool flag = Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
//	//bool flag = ((RayCast)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2527850))(Ray(vector, normalized), magnitude + radius, 429990145); //public static bool Raycast(Ray ray, float maxDistance, int layerMask) { }
//
//	//bool flag = Physics::Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
//	if (!flag || spHerecast) {
//		typedef bool (*Sphere)(Ray, float, float, int);
//
//		flag = SphereCast(Ray(vector, normalized), radius, magnitude, 429990145);
//		//	flag = ((Sphere)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2528890))(Ray(vector, normalized), radius, magnitude, 429990145);
//
//	}
//	return flag;
//}
bool TestNoClipping(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool spHerecast) {
	int num = 429990145;
	//Ulog("6");
	Vector3 normalized = (newPos - oldPos).Normalized();
	Vector3 vector = oldPos - normalized * backtracking;
	float magnitude = (newPos - vector).Magnitude();

	typedef bool (*RayCast)(Ray, float, int);

	bool flag = Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
	//bool flag = ((RayCast)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2527850))(Ray(vector, normalized), magnitude + radius, 429990145); //public static bool Raycast(Ray ray, float maxDistance, int layerMask) { }

	//bool flag = Physics::Raycast(Ray(vector, normalized), magnitude + radius, 429990145);
	if (!flag || spHerecast) {
		typedef bool (*Sphere)(Ray, float, float, int);

		flag = SphereCast(Ray(vector, normalized), radius, magnitude, 429990145);
		//	flag = ((Sphere)(LI_MODULE_SAFE_("GameAssembly.dll") + 0x2528890))(Ray(vector, normalized), radius, magnitude, 429990145);

	}
	return flag;
}
bool ValidateEyePos(BasePlayer* player, Vector3 eyePos)
{

	bool flag = true;

	if (true)
	{
		float num = 1.5f;
		float eye_clientframes = 2.0f;
		float eye_serverframes = 2.0f;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * max(Time::deltaTime(), max(Time::smoothDeltaTime(), Time::fixedDeltaTime()));
		float num4 = (rust::globals::last_tick_time + num2 + num3) * num;



		//float mm_max_eye = LocalPlayer::Entity()->BoundsPadding() + num4 * LocalPlayer::Entity()->MaxEyeVelocity();
		int layerMask = (int)2162688;
		//	int layerMask = (true ? 10551296 : 2162688);
		if (true)
		{


			float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().Magnitude();
			float num6 = player->BoundsPadding() + num4 * num5;
			float num7 = player->eyes()->position().Distance(eyePos);
			if (num7 > num6)
			{
				flag = false;
			}
		}
		if (true)
		{
			float num8 = std::abs(player->GetMountVelocity().y + player->GetParentVelocity().y);
			float num9 = player->BoundsPadding() + num4 * num8 + player->GetJumpHeight();
			float num10 = std::abs(player->eyes()->position().y - eyePos.y);
			if (num10 > num9)
			{
				flag = false;
			}
		}

		Vector3 position2 = player->eyes()->position();
		Vector3 vector2 = eyePos;
		float num11 = position2.Distance(vector2);
		if (num11 > 0.06f)
		{
			if (TestNoClipping(player, position2, vector2, NoClipRadius(0.21f), 0.01f, true))
			{
				flag = false;
			}
		}
		else if (num11 > 0.01f && TestNoClipping(player, position2, vector2, 0.01f, 0.01f, true))
		{
			flag = false;
		}
		if (!flag)
		{
		}
	}
	return flag;
}