auto Hooks::DoHit(Projectile* p, HitTest* test, Vector3 point, Vector3 normal) -> bool
{
	__try
	{
		if (p || p->isAlive() || p->isAuthoritative()) {

			auto lol = test->HitEntity();
			if (!memory::valid_pointer(lol))
				return Hooks::DoHithk.get_original< decltype(&DoHit)>()(p, test, point, normal);

			auto go = p->get_gameObject();
			if (!memory::valid_pointer(go))
				return Hooks::DoHithk.get_original< decltype(&DoHit)>()(p, test, point, normal);


			if (go && !lol) {
				if (go->layer() == 0 || go->layer() == 24) {
					return false;
				}
			}

			if (lol) {
				if (lol->class_name_hash() == STATIC_CRC32("CargoShip") || lol->class_name_hash() == STATIC_CRC32("BaseOven")
					|| lol->class_name_hash() == STATIC_CRC32("TreeEntity") || lol->class_name_hash() == STATIC_CRC32("OreResourceEntity")
					|| lol->class_name_hash() == STATIC_CRC32("CH47HelicopterAIController") || lol->class_name_hash() == STATIC_CRC32("MiniCopter")
					|| lol->class_name_hash() == STATIC_CRC32("BoxStorage") || lol->class_name_hash() == STATIC_CRC32("Workbench")
					|| lol->class_name_hash() == STATIC_CRC32("VendingMachine") || lol->class_name_hash() == STATIC_CRC32("Barricade")
					|| lol->class_name_hash() == STATIC_CRC32("BuildingPrivlidge") || lol->class_name_hash() == STATIC_CRC32("LootContainer")
					|| lol->class_name_hash() == STATIC_CRC32("HackableLockedCrate") || lol->class_name_hash() == STATIC_CRC32("ResourceEntity")
					|| lol->class_name_hash() == STATIC_CRC32("RidableHorse") || lol->class_name_hash() == STATIC_CRC32("MotorRowboat")
					|| lol->class_name_hash() == STATIC_CRC32("ScrapTransportHelicopter") || lol->class_name_hash() == STATIC_CRC32("JunkPile")
					|| lol->class_name_hash() == STATIC_CRC32("MiningQuarry") || lol->class_name_hash() == STATIC_CRC32("WaterCatcher")
					|| lol->class_name_hash() == STATIC_CRC32("RHIB")) {
					return false;
				}
			}
		}
	}
	__except (true)
	{
		printf("DoHit Crash");
	}


	return Hooks::DoHithk.get_original< decltype(&DoHit)>()(p, test, point, normal);
}