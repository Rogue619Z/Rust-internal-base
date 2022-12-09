static bool TestFlying(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, bool verifyGrounded)
{
	bool isInAir = false;
	if (verifyGrounded)
	{
		float flyhack_extrusion = AntiHackV::FlyHack::flyhack_extrusion;
		Vector3 vector = (oldPos + newPos) * 0.5f;
		if (!WaterLevel::Test(vector - Vector3(0.f, flyhack_extrusion, 0.f), true, ply))
		{
			float flyhack_margin = AntiHackV::FlyHack::flyhack_margin;
			float radius = ply->GetRadius();
			float height = ply->GetHeight(false);
			Vector3 vector2 = vector + Vector3(0.f, radius - flyhack_extrusion, 0.f);
			Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
			float radius2 = radius - flyhack_margin;
			isInAir = !Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, Enums::QueryTriggerInteraction::Ignore);
			if (isInAir)
			{
			}
		}
	}
	else
	{
		isInAir = (!ply->OnLadder() && !ply->IsSwimming() && !ply->IsOnGround());
	}
	if (isInAir)
	{
		bool flag = false;
		Vector3 vector4 = newPos - oldPos;
		float num2 = std::abs(vector4.y);
		float num3 = vector4.Magnitude2D();
		if (vector4.y >= 0.f)
		{
			AntiHackV::FlyHack::flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num2 < num3)
		{
			AntiHackV::FlyHack::flyhackDistanceHorizontal += num3;
			flag = true;
		}
		if (flag)
		{
			float num4 = max((AntiHackV::FlyHack::flyhackPauseTime > 0.f) ? AntiHackV::FlyHack::flyhack_forgiveness_vertical_inertia : AntiHackV::FlyHack::flyhack_forgiveness_vertical, 0.f);
			float num5 = ply->GetJumpHeight() + num4;
			if (AntiHackV::FlyHack::flyhackDistanceVertical > num5)
			{
				return true;
			}
			AntiHackV::FlyHack::flyhackDistanceVerticalMax = num5;//(num6 * 2) - 2;
			//if (AntiHackV::FlyHack::flyhackDistanceVertical >= AntiHackV::FlyHack::flyhackDistanceVerticalMax)
			//	AntiHackV::FlyHack::flyhackDistanceVertical = AntiHackV::FlyHack::flyhackDistanceVerticalMax;

			float num6 = max((AntiHackV::FlyHack::flyhackPauseTime > 0.f) ? AntiHackV::FlyHack::flyhack_forgiveness_horizontal_inertia : AntiHackV::FlyHack::flyhack_forgiveness_horizontal, 0.f);
			float num7 = 5.f + num6;
			if (AntiHackV::FlyHack::flyhackDistanceHorizontal > num7)
			{
				return true;
			}
			AntiHackV::FlyHack::flyhackDistanceHorizontalMax = num7;//(num8 * 2) - 2; //- (VFlyhack * 2);//(num6 * 2);
			//if (AntiHackV::FlyHack::flyhackDistanceHorizontal >= AntiHackV::FlyHack::flyhackDistanceHorizontalMax)
			//	AntiHackV::FlyHack::flyhackDistanceHorizontal = AntiHackV::FlyHack::flyhackDistanceHorizontalMax;
		}

	}
	else
	{
		AntiHackV::FlyHack::flyhackDistanceVertical = 0.f;
		AntiHackV::FlyHack::flyhackDistanceHorizontal = 0.f;
	}
	return false;
}

bool IsFlying(bool PreventFlyhack, BasePlayer* player)
{
	BasePlayer* ply = player;
	bool result;
	AntiHackV::FlyHack::flyhackPauseTime = max(0.0f, AntiHackV::FlyHack::flyhackPauseTime - Time::deltaTime());
	bool flag = ply->transform()->GetParent() == nullptr;
	Matrix4x4 _mv; _mv.matrix_identity();
	Matrix4x4 matrix4x = flag ? _mv : ply->transform()->GetParent()->get_localToWorldMatrix();
	//Matrix4x4 matrix4x = matrix4x = flag ? matrix4x->matrix_identity() : ply->transform()->GetParent()->get_localToWorldMatrix();

	Vector3 oldPos = flag ? ply->lastSentTick()->position() : matrix4x.MultiplyPoint3x4(ply->lastSentTick()->position());
	Vector3 vector = flag ? ply->transform()->position() : matrix4x.MultiplyPoint3x4(ply->transform()->position());

	result = TestFlying(ply, oldPos, vector, true);

	if (result && PreventFlyhack)
	{
		ply->ForcePositionTo(oldPos);

	}
	return result;
}