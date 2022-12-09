struct fired_projectile {
	Projectile* original;
	Projectile* fake;
	float fired_at;
	int updates;
};

std::array<fired_projectile, 32> fired_projectiles;


static Vector3 SimulateProjectile(Vector3& position, Vector3& velocity, float& partialTime, float travelTime, Vector3 gravity, float drag, float timestep)
{
	float num = timestep;
	Vector3 origin = position;
	if (partialTime > 0)
	{
		float num2 = num - partialTime;
		if (travelTime < num2)
		{
			origin = position;
			position += velocity * travelTime;
			partialTime += travelTime;
		//	printf("Partial Time 1 %f\n", partialTime);
		//	printf("Travel Time 2 %f\n", travelTime);
			return origin;
		}
		origin = position;
		position += velocity * num2;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
		travelTime -= num2;
		//printf("Travel Time 1 %f\n", travelTime);
	}

	int num3 = int(travelTime / num);

	for (int i = 0; i < num3; i++)
	{
		origin = position;
		position += velocity * num;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
	}
	partialTime = travelTime - num * (float)num3;
	//printf("Partial Time 3 %f \n", partialTime);
	printf("Travel Time 3 %f \n", travelTime);
	if (partialTime > 0)
	{
		origin = position;
		position += velocity * partialTime;
	}
	return origin;
}

Vector3 Simulate(bool returnvelocity, bool sendtoserver, Vector3& pos, float& part, Projectile* pr) {
	pos = pr->sentPosition();
	Vector3 prev = pr->tumbleAxis();
	part = pr->tumbleSpeed();
	float travel = max(pr->traveledTime() - pr->closeFlybyDistance(), 0);

	Vector3 gr = Physics::gravity(); //static Vector3 get_gravity();


	Vector3 origin = SimulateProjectile(pos, prev, part, travel, gr * pr->gravityModifier(), pr->drag(), 0.03125f);

	if (sendtoserver) {
		pr->sentPosition() = pos;
		pr->tumbleAxis() = prev;
		pr->tumbleSpeed() = part;
		pr->closeFlybyDistance() = pr->traveledTime();
	}

	if (returnvelocity) return prev;

	return origin;
}
auto CustomHook::OnProjectileShootRpc(std::uint64_t instance) -> void
{
	if (rust::globals::initalized)
	{
		do {
			if (!memory::valid_pointer(LocalPlayer::Entity()) || !memory::valid_pointer(camera))
				break;

			if (!memory::valid_pointer(rust::globals::target))
				break;

			const auto weapon = LocalPlayer::Entity()->item();
			if (!memory::valid_pointer(weapon))
				break;

			if (weapon->info()->category() != Enums::ItemCategory::Weapon)
				break;

			const auto base_projectile = weapon->heldEntity();
			if (!memory::valid_pointer(base_projectile))
				break;

			const auto il2cppClass = *reinterpret_cast<Il2CppClass**>(base_projectile);
			if (!memory::valid_pointer(il2cppClass))
				break;

			const auto createdProjectiles = base_projectile->createdProjectiles();
			if (!memory::valid_pointer(createdProjectiles))
				break;

			const auto projectile_list = *reinterpret_cast<BaseProjectile**>(createdProjectiles + 0x10);
			if (!memory::valid_pointer((PVOID)projectile_list))
				break;

			const auto shoot_list = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(instance + 0x18) + 0x10);
			if (!memory::valid_pointer((PVOID)shoot_list))
				break;

			const auto shoot_list_size = *reinterpret_cast<int*>(*reinterpret_cast<std::uintptr_t*>(instance + 0x18) + 0x18);

			if (shoot_list_size <= 0)
				break;


			float travel_time = 0.f;

			Vector3 m_aim_angle = Vector3::Zero();

			Vector3 start_position = Vector3::Zero();
			Vector3 original_velocity = Vector3::Zero();

			bool manipulated = false;

			bool visible = false;


			for (size_t idx{ 0 }; idx < shoot_list_size; idx++)
			{
				const auto projectile_shoot = *reinterpret_cast<uintptr_t*>(shoot_list + 0x20 + idx * 0x8);
				if (!memory::valid_pointer(projectile_shoot))
					break;

				start_position = *reinterpret_cast<Vector3*>(projectile_shoot + 0x18);
				original_velocity = *reinterpret_cast<Vector3*>(projectile_shoot + 0x24);




				if (Input::GetKey(Enums::KeyCode::X)) {
					auto rpcposv2 = start_position;
					if (rust::globals::spoofed_eye_pos != Vector3(0, 0, 0))
					{
						// rpc_position += misc::manipulate(esp::local_player, target.pos);
						start_position += (rust::globals::spoofed_eye_pos);
						visible = IsVisible(start_position, rust::globals::target->get_bone_transform(Enums::head)->position());
						if (start_position != rpcposv2)
						{
							manipulated = true;

							if (visible)
							{
								visible = true;
								*reinterpret_cast<Vector3*>(projectile_shoot + 0x18) = start_position;
							}
						}
					}
				}


				//	*reinterpret_cast<Vector3*>(projectile_shoot + 0x24) = m_aim_angle;




			}

			for (size_t idx{ 0 }; idx < projectile_list->list_size(); idx++)
			{
				const auto projectile = *reinterpret_cast<Projectile**>(projectile_list + 0x20 + (idx * 0x8));

				if (!memory::valid_pointer(projectile))
					continue;

				auto mag = base_projectile->primaryMagazine();
				if (!memory::valid_pointer(mag))
					continue;


				auto ammo = mag->ammoType();
				if (!memory::valid_pointer(ammo))
					continue;

				const auto component = (ItemModProjectile*)ammo->GetComponent(Il2CppWrapper::Type("", "ItemModProjectile"));




				Vector3 a;
				SimulateProjectile(rust::globals::target, start_position, rust::globals::target->get_bone_transform(Enums::head)->position(), m_aim_angle, a, travel_time, projectile, base_projectile, component);

			}


			for (size_t idx{ 0 }; idx < shoot_list_size; idx++)
			{
				const auto projectile_shoot = *reinterpret_cast<uintptr_t*>(shoot_list + 0x20 + idx * 0x8);
				if (!memory::valid_pointer(projectile_shoot))
					continue;



				if (rust::globals::target || manipulated) {
					*reinterpret_cast<Vector3*>(projectile_shoot + 0x24) = m_aim_angle;
				}
			}
			for (size_t idx{ 0 }; idx < projectile_list->list_size(); idx++)
			{
				const auto projectile = *reinterpret_cast<Projectile**>(projectile_list + 0x20 + (idx * 0x8));

				if (!memory::valid_pointer(projectile))
					continue;


				fired_projectile f = { projectile, nullptr, Time::fixedTime(), 1 };
				for (size_t i = 0; i < 32; i++)
				{
					if (fired_projectiles[i].fired_at <= 10.f) {
						fired_projectiles[i] = f;
						break;
					}
				}

				projectile->currentVelocity() = m_aim_angle;



				

				visible = IsVisible(start_position, rust::globals::target->get_bone_transform(Enums::head)->position());
				if (visible)
				{

					if (manipulated)
					{
						auto g = projectile->get_gameObject();
						if (!memory::valid_pointer(g))
							continue;


						auto t = g->get_transform();
						if (!memory::valid_pointer(t))
							continue;

						t->set_position(start_position);
					}
				}
			}
		} while (0);
	}
}

auto CustomHook::ProjectileShootRpc(void* _rcx, void* _rdx, void* a1, std::uint64_t instance, void* a3) -> void
{
	static auto o_func = reinterpret_cast<decltype(&CustomHook::ProjectileShootRpc)>(CustomHook::ProjectileShootRpchk);

	CustomHook::OnProjectileShootRpc(instance);

	return o_func(_rcx, _rdx, a1, instance, a3);
}

static bool has_initialized{ false };


auto initAimbot() -> void
{
	if (!has_initialized)
	{
		static auto initialize_method = utl::pattern::find(L"GameAssembly.dll", "48 83 EC 48 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ?");
		static auto il2cpp_codegen_initialize_method = reinterpret_cast<void (*)(unsigned int)>(initialize_method);

		for (size_t idx{ 0 }; idx < 56229; idx++)
		{
			il2cpp_codegen_initialize_method(idx);
		}

		fired_projectile placeholder = { nullptr, 0, 1 };
		for (size_t i = 0; i < 32; i++)
			fired_projectiles[i] = placeholder;

		static auto projectile_shoot_sig = utl::pattern::find(L"GameAssembly.dll", "4C 8B 0D ? ? ? ? 48 8B 75 30");
		const auto relative_projectile_shoot = *reinterpret_cast<std::uintptr_t*>(projectile_shoot_sig + *reinterpret_cast<std::int32_t*>(projectile_shoot_sig + 3) + 7);

		if (relative_projectile_shoot)
		{
			const auto projectile_shoot_rpc = **reinterpret_cast<std::uintptr_t***>(relative_projectile_shoot + 0x30);
			HOOK_CUSTOM(projectile_shoot_rpc, CustomHook::ProjectileShootRpchk, &CustomHook::ProjectileShootRpc);
		}
		has_initialized = true;
	}
}