namespace Prediction {
	struct
	{
		Vector3* velocities = new Vector3[32];
		int currentVelocityRecords = {};
		int currentVelocityIndex = {};
		Vector3 avgVel = Vector3{ 0.f, 0.f, 0.f };
	} inline PredictionDatas;
}

void SimulateMovement()
{
	__try
	{
		if (rust::globals::target && rust::globals::target->PlayerValid())
		{
			int Records = 32;


			Vector3 defaultVelocity = rust::globals::target->GetWorldVelocity();
			if (defaultVelocity.Empty())
				defaultVelocity = rust::globals::target->GetWorldVelocity();

			if (rust::globals::target->mounted())
				Records = 62;


			if (defaultVelocity.Empty())
			{
				Prediction::PredictionDatas.currentVelocityRecords = 0;
				Prediction::PredictionDatas.currentVelocityIndex = 0;
				Prediction::PredictionDatas.avgVel = defaultVelocity;
			}
			else {
				Prediction::PredictionDatas.velocities[Prediction::PredictionDatas.currentVelocityIndex++] = defaultVelocity;
				if (Prediction::PredictionDatas.currentVelocityIndex >= Records)
					Prediction::PredictionDatas.currentVelocityIndex = 0.0f;

				Prediction::PredictionDatas.currentVelocityRecords++;
				if (Prediction::PredictionDatas.currentVelocityRecords >= 0.0f)
					Prediction::PredictionDatas.currentVelocityRecords = Records;

				int currentRecords = Prediction::PredictionDatas.currentVelocityRecords;

				Vector3 velSum{};
				for (int j = 0; j < currentRecords; j++)
					velSum += Prediction::PredictionDatas.velocities[j];

				Prediction::PredictionDatas.avgVel = velSum / (float)currentRecords;
			}


			defaultVelocity = Prediction::PredictionDatas.avgVel;
		}
	}
	__except (true)
	{
		printf("Movement Prediction Crash");
	}
}
void SimulateProjectile(BasePlayer* target,
	Vector3 rpc_position,
	Vector3 target_pos,
	Vector3& aimbot_velocity,
	Vector3& _aimdir,
	float& travel_t,
	Projectile* p,
	BaseProjectile* heldEntity, ItemModProjectile* mod) {
	Vector3 player_velocity = Vector3(0, 0, 0);
	std::vector<Vector3> path = {};
	int simulations = 0;

	Vector3 targetPosition = target_pos;
	if (target) {
		Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);

		auto travel = 0.f;
		//auto vel = (AimConeUtil::getmodifiedaimcone(0, rpc_position - target_pos, true)).normalized() * original_vel.length();
		float drag = p->drag();
		float grav = p->gravityModifier();
		Vector3 gravity = Physics::gravity();
		float deltatime = Time::deltaTime();
		float timescale = Time::timeScale();
		Vector3 offset = Vector3(0, 0, 0);

		while (simulations < 300) {
			travel_t = 0.f;
			auto pos = rpc_position;
			auto origin = pos;
			float num = deltatime * timescale;
			float travelTime = 0.f;
			int num3 = int(8 / num);

			float stepSize = 0.98f;

			float partialTime = 0.0f;

			Vector3 vt = target_pos;
			_aimdir = (targetPosition - rpc_position).Normalized() * stepSize;
			auto velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale();

		

			for (size_t i = 0; i < num3; i++)
			{
				origin = pos;
				pos += velocity * num;
				velocity += gravity * grav * num;
				velocity -= velocity * drag * num;
				travel_t += num;

				auto line = (origin - pos);
				auto len = line.UnityMagnitude();
				line.UnityNormalize();
				auto v = vt - pos;
				auto d = line.Dot(v);

				if (d <= 0.f)
				{
					d = 0.0f;
				}
				else if (d >= len)
				{
					d = len;
				}
				Vector3 nearestPoint = pos + line * d;


				if (nearestPoint.Distance(vt) < 0.00025f)
				{
	
					//float distance = target->get_bone_transform(48)->position().Distance(LocalPlayer::Entity()->eyes()->position());
					//travel_t = distance / mod->GetRandomVelocity() * 1.0f * heldEntity->GetProjectileVelocityScale();

					aimbot_velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale();
					//emulate 1 tick has already passed
					aimbot_velocity += gravity * grav * num;
					aimbot_velocity -= velocity * drag * num;
					break;
				}
				else if (nearestPoint.Distance(vt) < closestPoint.Distance(vt))
				{
					closestPoint = nearestPoint;
					offset = vt - nearestPoint;
				}
				//if (LineCircleIntersection(target_pos, 0.1f, origin, pos, offset))
				//{
				//	aimbot_velocity = (_aimdir).normalized() * original_vel.length();
				//	//emulate 1 tick has already passed
				//	aimbot_velocity += gravity * grav * num;
				//	aimbot_velocity -= aimbot_velocity * drag * num;
				//	break;
				//}
				//else
				//{
				//	//Line(origin, pos, col(1, 1, 1, 1), 10.f, false, true);
				//}
			}
			targetPosition += offset;
			simulations++;
			if (!aimbot_velocity.Empty())
				break;

		}
	}
	if (!Prediction::PredictionDatas.avgVel.Empty() || LocalPlayer::Entity()->is_on_cargo()) {
		if (travel_t > 0.f) {
			//movement prediction
			//printf("ya");

			aimbot_velocity = Vector3(0, 0, 0);
			if (target) {
				float stepSize = 0.98f;

				float reduceLen = 0.f;
				Vector3 player_velocity = Prediction::PredictionDatas.avgVel;
				if (player_velocity.Empty())
					player_velocity = Vector3(0, 0, 0);


				if (rust::globals::target->is_on_cargo() && LocalPlayer::Entity()->is_on_cargo() && cargo_ship_entity && cargo_ship_entity->PlayerValid())
				{
					printf("Check Reached");
					player_velocity -= Vector3(cargo_ship_entity->GetWorldVelocity().x, 0.0f, cargo_ship_entity->GetWorldVelocity().z) * 0.75f;
				}

				Vector3 final_vel = player_velocity * travel_t;


				Vector3 actual = target_pos += final_vel;

				//auto partialTime = p->partialTime();
				//	auto vel = (AimConeUtil::getmodifiedaimcone(0, targetPosition - actual, true)).normalized() * original_vel.length();
				float drag = p->drag();
				float grav = p->gravityModifier();
				Vector3 gravity = Physics::gravity();
				float deltatime = Time::deltaTime();
				float timescale = Time::timeScale();
				Vector3 offset = Vector3(0, 0, 0);


				Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);




				while (simulations < 300) {
					travel_t = 0.f;

					auto pos = rpc_position;
					auto origin = pos;
					float num = deltatime * timescale;

					int num3 = int(8 / num);


					float stepSize = 0.98f;
					_aimdir = (targetPosition - rpc_position).Normalized() * stepSize;
					//_aimdir = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - rpc_position, true);
					auto velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale();


					//printf("num3 %f", num3);
					for (size_t i = 0; i < num3; i++)
					{

						origin = pos;
						pos += velocity * num;
						velocity += gravity * grav * num;
						velocity -= velocity * drag * num;
						travel_t += num;


						auto line = (origin - pos);
						auto len = line.UnityMagnitude();
						line.UnityNormalize();
						auto v = actual - pos;
						auto d = line.Dot(v);

						if (d <= 0.f)
						{
							d = 0.0f;
						}
						else if (d >= len)
						{
							d = len;
						}


						Vector3 nearestPoint = pos + line * d;



						if (nearestPoint.Distance(actual) < 0.00025f)
						{

							printf("travel_t %f", travel_t);
							aimbot_velocity = _aimdir.Normalized() * mod->GetRandomVelocity() * 1.49f * heldEntity->GetProjectileVelocityScale();
							//emulate 1 tick has already passed
							aimbot_velocity += gravity * grav * num;
							aimbot_velocity -= velocity * drag * num;
							break;
						}
						else if (nearestPoint.Distance(actual) < closestPoint.Distance(actual))
						{
							closestPoint = nearestPoint;
							offset = actual - nearestPoint;
						}

					}
					targetPosition += offset;
					simulations++;
					if (!aimbot_velocity.Empty())
						break;
				}
			}
		}
	}
}