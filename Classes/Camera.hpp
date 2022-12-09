class Camera;

Camera* camera = nullptr;
class Camera
{
public:
	CLASS("UnityEngine", "Camera");

	static auto main() -> Camera*
	{
		METHOD(Camera *(**)(), get_current);
		return get_current();
	}
	auto WorldToScreenPoint(Vector3 pos) -> Vector3
	{
		static auto WorldToScreenPoint = *reinterpret_cast<Vector3(**)(Camera*, Vector3)>(StaticClass()->GetMethodFromName("WorldToScreenPoint", 1));
		return WorldToScreenPoint(this, pos);
	}
	bool WorldToScreen(Vector3 position, Vector2& screen)
	{
		if (!this || !camera) return false;

		Vector3 ret = WorldToScreenPoint(position);
		ret.y = Screen::height() - ret.y;
		screen =
		{
			ret.x,
			ret.y
		};

		return ret.z > 0.0f;
	}

};