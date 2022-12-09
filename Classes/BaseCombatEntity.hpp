
class BaseCombatEntity : public BaseEntity
{
public:
	CLASS("", "BaseCombatEntity");

	MEMBER(float, startHealth);
	MEMBER(float, _health);
	MEMBER(float, _maxHealth);
	MEMBER(float, deathTime);

	auto IsDead() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseCombatEntity*), IsDead);
		return IsDead(this);
	}
	auto IsAlive() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseCombatEntity*), IsAlive);
		return IsAlive(this);
	}
};