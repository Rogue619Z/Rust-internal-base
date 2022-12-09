auto Hooks::TraceAll(HitTest* p, void* traces, int layerMask) -> void
{
	if (!p) return Hooks::TraceAllhk.get_original< decltype(&TraceAll)>()(p, traces, layerMask);


	if (rust::globals::target && rust::globals::target->PlayerValid()) {

		if (IsVisible(LocalPlayer::Entity()->get_bone_transform(48)->position() + rust::globals::spoofed_eye_pos, rust::globals::target->get_bone_transform(48)->position())) {
			layerMask &= ~1218519041;
		}
	}


	Hooks::TraceAllhk.get_original< decltype(&TraceAll)>()(p, traces, layerMask);
}