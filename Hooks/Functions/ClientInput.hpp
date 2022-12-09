#include "../Hooks.hpp"



float GetHitDist(Projectile* p) {
	float travel = p->traveledTime();

	float num6 = (travel + 2 / 60 + 0.03125f) * 1.5f;
	float maxdist = 0.1f + num6 * 5.5f;
	return maxdist;
}

auto Hooks::ClientInput(BasePlayer* player, uintptr_t* input_state) -> void
{


	if (!player || !input_state) return Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(player, input_state);




	__try
	{
		initAimbot();


		do {

			const auto weapon = LocalPlayer::Entity()->item();
			if (!memory::valid_pointer(weapon))
				break;


			if (weapon->info()->category() == Enums::ItemCategory::Weapon)
			{
				const auto base_projectile = weapon->heldEntity();
				if (!memory::valid_pointer(base_projectile))
					break;


				if (rust::globals::target && rust::globals::target->PlayerValid()) {

					if (Input::GetKey(Enums::KeyCode::X)) {
						if (IsVisible(rust::globals::target->get_bone_transform(48)->position(), LocalPlayer::Entity()->eyes()->position() + rust::globals::spoofed_eye_pos)) {
							if (base_projectile->primaryMagazine()->contents() != 0 && !base_projectile->isReloading()) {
								float NextShot = base_projectile->repeatDelay();

								if (Time::fixedTime() > NextShot && base_projectile->timeSinceDeploy() > base_projectile->deployDelay()) {
									if (!base_projectile->HasAttackCooldown()) {
										base_projectile->LaunchProjectile();
										base_projectile->primaryMagazine()->contents()--;
										base_projectile->UpdateAmmoDisplay();
										base_projectile->ShotFired();
										base_projectile->DidAttackClientside();
										base_projectile->BeginCycle();
									}
									//	player->SendClientTick();
								}
							}
						}
					}
					SimulateMovement();
				}
				for (int i = 0; i < 32; i++)
				{
					auto current = fired_projectiles[i];
					if (current.fired_at <= 2.f)
						continue;

					auto projectile = current.original;
					if (!projectile->isAuthoritative())
						continue;

					if (!projectile->isAlive())
						continue;

					if (!rust::globals::target)
						continue;

					Transform* bonetrans = rust::globals::target->get_bone_transform(48);
					Vector3 target_bone = bonetrans->position(); //target_bone.y -= 0.8f;

					auto current_position = projectile->transform()->position();

					auto dist = target_bone.Distance(current_position);

					float num2 = 1.0f + 0.5f;
					float num8 = 2.0f / 60.0f;
					float num9 = 2.0f * max(max(Time::deltaTime(), Time::smoothDeltaTime()), Time::fixedDeltaTime());
					float num11 = (rust::globals::last_tick_time + num8 + num9) * num2;
					auto pv = rust::globals::target->GetParentVelocity().Magnitude();
					float mags = pv;
					float num15 = 0.1f + num11 * mags + 0.1f;
					dist += num15;


					//projectile->thickness() = 0.85f;


					float maxDist = 1.9f;
					float maxDistMounted = 6.f;
					//printf("maxDist Dist %f \n", maxDist);

					if (dist < maxDist)
					{


						auto newpos = Vector3::move_towards(current_position, target_bone, 1.0f);
						projectile->transform()->set_position(newpos);


						float time = 0;
						Vector3 pos{};
						Vector3 attackStart = Simulate(false, true, pos, time, projectile);

						bool canIgnore = true;
						canIgnore = IsVisible(projectile->sentPosition(), projectile->currentPosition() + projectile->currentVelocity().Normalized() * 0.01f, 0);//(uintptr_t)esp::local_player);


						HitTest* ht = projectile->hitTest();
						if (ht)
						{
							if (canIgnore)
							{
								projectile->thickness() = 0.85f;

								ht->DidHit() = true;
								ht->HitEntity() = (rust::globals::target);
								ht->HitTransform() = bonetrans;
								ht->HitPoint() = bonetrans->InverseTransformPoint(newpos);
								ht->HitNormal() = bonetrans->InverseTransformDirection(newpos);
								//Ray r(p->transform()->position(), newpos);


								ht->AttackRay() = Ray(projectile->transform()->position(), newpos);


								projectile->DoHit(ht, newpos, ht->HitNormalWorld());
							}
							else
							{
								projectile->integrity() = 0.03f;
								projectile->integrity() = 0;
							}
						}
	
					}
				}
			}
		} while (0);

		//Matrix4x4::identity();

		float timeSinceLastTick = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime());
		rust::globals::last_tick_time = max(0.f, min(timeSinceLastTick, 1.f));

	
		float num = 1.5f;
		float eye_clientframes = 2.0f;
		float eye_serverframes = 2.0f;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * Max3(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
		float num4 = (rust::globals::last_tick_time + num2 + num3) * num;


		float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().Magnitude();
		float num6 = player->BoundsPadding() + num4 * num5; 

		rust::globals::max_spoofed_eye_distance = num6;


		if (Input::GetKey(Enums::KeyCode::X)) 
		{
			player->clientTickInterval() = 1.0f;
		}
		else
		{
			player->clientTickInterval() = 0.05f;
		}

		if (Input::GetKey(Enums::KeyCode::X)) {
			EyeManipulationAngle(player, rust::globals::target);
		}
		else if (!rust::globals::spoofed_eye_pos.Empty()) {
			rust::globals::spoofed_eye_pos = Vector3(0, 0, 0);
		}

		//float desyncTimeRaw = max(Time::realtimeSinceStartup() - player->lastSentTickTime(), 0.f);
		//float desyncTimeClamped = max(desyncTimeRaw, 1.f);

		//float num = 1.5f;
		//float eye_clientframes = 2.0f;
		//float eye_serverframes = 2.0f;
		//float num2 = eye_clientframes / 60.f;
		//float num3 = eye_serverframes * max(Time::deltaTime(), Time::fixedDeltaTime());
		//float num4 = 0.1f + (Time::realtimeSinceStartup() - player->lastSentTickTime() + num2 + num3) * num;

		//float num5 = player->MaxEyeVelocity() + player->GetParentVelocity().Magnitude();

		//float MaxEyeDistance = player->BoundsPadding() + num4 * num5;


		//auto time = Time::realtimeSinceStartup();//UnityEngine::Time::get_realtimeSinceStartup();
		//float _timeSinceLastTick = time - player->lastSentTickTime();
		//float timeSinceLastTickClamped = max(0.f, min(_timeSinceLastTick, 1.f));
		//float maxDist = 0.1f + (timeSinceLastTickClamped + 2.f / 60.f) * 1.5f * player->MaxEyeVelocity();


		//if (player->infir)
	

		OnGUI::Get();
	}
	__except (true)
	{
		ConsoleLOG("Hook Crash [Client Input]");
	}





	Hooks::ClientInputhk.get_original< decltype(&ClientInput)>()(player, input_state);

}