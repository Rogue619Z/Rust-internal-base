class Magazine
{
public:
	CLASS("", "Magazine");

	int& contents()
	{
		__try
		{
			auto& ptr = *(int*)(this + 0x1C);
			return ptr;
		}
		__except (true)
		{
			printf("%s - Exception Occurred.", __FUNCTION__);
		}
		auto n = nullptr;
		return reinterpret_cast<int&>(n);
	}
	ItemDefinition* ammoType()
	{
		__try
		{
			return *(ItemDefinition**)(this + 0x20);
		}
		__except (true)
		{
			printf("%s - Exception Occurred.", __FUNCTION__);
		}
		return nullptr;
	}
	MEMBER(int, capacity);
	//MEMBER(ItemDefinition*, ammoType);
};
class AttackEntity  //not correct but may work???
{
public:
	CLASS("", "AttackEntity");

	MEMBER(float, nextAttackTime);
	MEMBER(float, repeatDelay);
	MEMBER(float, deployDelay);
	MEMBER(float, timeSinceDeploy);

	auto StartAttackCooldown(float test) -> void
	{
		if (!this) return;
		METHOD(void(**)(AttackEntity*, float), StartAttackCooldown);
		return StartAttackCooldown(this, test);
	}

	auto HasAttackCooldown() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(AttackEntity*), HasAttackCooldown);
		return HasAttackCooldown(this);
	}
};
class BaseProjectile : public AttackEntity
{
public:
	CLASS("", "BaseProjectile");

	MEMBER(float, NoiseRadius);
	MEMBER(float, projectileVelocityScale);
	MEMBER(float, automatic);
	MEMBER(float, reloadTime);
	MEMBER(float, aimSway);
	MEMBER(float, aimSwaySpeed);
	MEMBER(bool, isReloading);
	MEMBER(float, nextReloadTime);
	MEMBER(float, lastShotTime);
	MEMBER(float, aimCone);
	MEMBER(float, hipAimCone);
	MEMBER(float, aimConePenaltyMax);
	MEMBER(float, aimconePenaltyRecoverDelay);
	MEMBER(float, aimconePenaltyPerShot);
	MEMBER(float, sightAimConeScale);
	MEMBER(float, hipAimConeScale);
	MEMBER(float, sightAimConeOffset);
	MEMBER(int, currentBurst);
	MEMBER(float, stancePenaltyScale);
	MEMBER(std::uintptr_t, createdProjectiles);
	MEMBER(float, aimconePenaltyRecoverTime);

	MEMBER(Magazine*, primaryMagazine);

	auto DoReload() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DoReload);
		return DoReload(this);
	}

	auto DoAttack() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DoAttack);
		return DoAttack(this);
	}

	auto BeginCycle() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), BeginCycle);
		return BeginCycle(this);
	}

	auto LaunchProjectile() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), LaunchProjectile);
		return LaunchProjectile(this);
	}
	auto GetProjectileVelocityScale(bool getMax = false) -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseProjectile*, bool), GetProjectileVelocityScale);
		return GetProjectileVelocityScale(this, getMax);
	}
	auto UpdateAmmoDisplay() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), UpdateAmmoDisplay);
		return UpdateAmmoDisplay(this);
	}

	auto ShotFired() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), ShotFired);
		return ShotFired(this);
	}

	auto DidAttackClientside() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseProjectile*), DidAttackClientside);
		return DidAttackClientside(this);
	}

	auto list_size() -> std::uint32_t { return *reinterpret_cast<std::uint32_t*>(this + 0x18); }
};