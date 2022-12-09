auto Hooks::DoMovement(Projectile* p, float deltaTime) -> void
{ 
	if (!p || !p->isAuthoritative())
		return Hooks::DoMovementhk.get_original< decltype(&DoMovement)>()(p, deltaTime);

	__try
	{
	}
	__except (true)
	{
		printf("DoMovement Crash");
	}


	Hooks::DoMovementhk.get_original< decltype(&DoMovement)>()(p, deltaTime);
}