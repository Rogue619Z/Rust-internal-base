void get_sphere_points_z(std::vector<Vector3>& re, float radius, unsigned int sectors = 20, unsigned int rings = 20)
{
	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	for (r = 0; r < rings; r++)
		for (s = 0; s < sectors; s++)
		{
			float y = sin(-(M_PI / 2) + M_PI * r * R);
			float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			x *= radius;
			y *= radius;
			z *= radius;

			re.push_back(Vector3(x, y, z));
		}
}
static float Max3(float f1, float f2, float f3)
{
	return max(max(f1, f2), f3);
}
auto EyeManipulationAngle(BasePlayer* local, BasePlayer* target) -> void
{
	if (!memory::valid_pointer(rust::globals::target))
		return;


	Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->get_up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);

	Vector3 target_pos = target->get_bone_transform(47)->position();

	Vector3 choice = Vector3::Zero();

	if (IsVisible(re_p, target_pos)) {
		rust::globals::spoofed_eye_pos = Vector3::Zero();
		return;
	}


	//float mm_max_eye = ((0.01f + ((desyncTime + 2.f / 60.f + 0.125f)	* LocalPlayer::Entity()->MaxEyeVelocity())));

	auto _right = LocalPlayer::Entity()->eyes()->MovementRight();
	auto forward = LocalPlayer::Entity()->eyes()->MovementForward();

	std::vector<Vector3> arr = {};


	get_sphere_points_z(arr, rust::globals::max_spoofed_eye_distance);

	for (auto& s : arr) {
		Vector3 point = re_p + s;

		//DDraw::Sphere(point, 0.05f, Color(99, 23, 75, 100), 0.2f, true);

		if (!IsVisible(point, re_p))
			continue;

		if (!IsVisible(point, target_pos))
			continue;

		if (!ValidateEyePos(local, point))
			continue;

		if (!ValidateEyePos(local, re_p))
			continue;



		//DDraw::Sphere(point, 0.18f, 2.0f);

		choice = s;
		break;
	}
	if (choice.Empty()) {
		rust::globals::spoofed_eye_pos = Vector3::Zero();
		return;
	}


	rust::globals::spoofed_eye_pos = choice;
}