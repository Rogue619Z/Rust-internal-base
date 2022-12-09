
class Model
{
public:
	CLASS("", "Model");

	MEMBER(Transform*, headBone);
	MEMBER(Transform*, eyeBone);
	MEMBER(uintptr_t, boneTransforms);
};

class BaseEntity : public BaseNetworkable
{
public:
	CLASS("", "BaseEntity");

	MEMBER(Model*, model);

	auto GetParentVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), GetParentVelocity);
		return GetParentVelocity(this);
	}
	auto CenterPoint() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), CenterPoint);
		return CenterPoint(this);
	}
	auto ClosestPoint(Vector3 pos) -> Vector3
	{
		if (!this || pos == Vector3::Zero()) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*, Vector3), ClosestPoint);
		return ClosestPoint(this, pos);
	}
	auto GetWorldVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), GetWorldVelocity);
		return GetWorldVelocity(this);
	}
	auto GetLocalVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), GetLocalVelocity);
		return GetLocalVelocity(this);
	}
	auto GetLocalVelocityClient() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), GetLocalVelocityClient);
		return GetLocalVelocityClient(this);
	}
	auto GetInheritedThrowVelocity(Vector3 direction) -> Vector3
	{
		if (!this || direction == Vector3::Zero()) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*, Vector3), GetInheritedThrowVelocity);
		return GetInheritedThrowVelocity(this, direction);
	}
	auto GetInheritedDropVelocity() -> Vector3
	{
		if (!this) return Vector3::Zero();
		METHOD(Vector3(**)(BaseEntity*), GetInheritedDropVelocity);
		return GetInheritedDropVelocity(this);
	}
	auto BoundsPadding() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), BoundsPadding);
		return BoundsPadding(this);
	}
	auto MaxVelocity() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), MaxVelocity);
		return MaxVelocity(this);
	}
	auto WaterFactor() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), WaterFactor);
		return WaterFactor(this);
	}
	auto AirFactor() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), AirFactor);
		return AirFactor(this);
	}
	auto MaxHealth() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), MaxHealth);
		return MaxHealth(this);
	}
	auto Health() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), Health);
		return Health(this);
	}
	auto GetExtrapolationTime() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), GetExtrapolationTime);
		return GetExtrapolationTime(this);
	}
	auto GetInterpolationDelay() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), GetInterpolationDelay);
		return GetInterpolationDelay(this);
	}
	auto InheritedVelocityScale() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), InheritedVelocityScale);
		return InheritedVelocityScale(this);
	}
	auto GetInterpolationInertia() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), GetInterpolationInertia);
		return GetInterpolationInertia(this);
	}
	auto GetInterpolationSmoothing() -> float
	{
		if (!this) return 0.0f;
		METHOD(float(**)(BaseEntity*), GetInterpolationSmoothing);
		return GetInterpolationSmoothing(this);
	}
	auto UpdateCullingBounds() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseEntity*), UpdateCullingBounds);
		return UpdateCullingBounds(this);
	}
	auto UpdateCullingSpheres() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseEntity*), UpdateCullingSpheres);
		return UpdateCullingSpheres(this);
	}
	auto DestroyShared() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseEntity*), DestroyShared);
		return DestroyShared(this);
	}
	auto RegisterForCulling() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseEntity*), RegisterForCulling);
		return RegisterForCulling(this);
	}
	auto DebugDrawCullingBounds() -> void
	{
		if (!this) return;
		METHOD(void(**)(BaseEntity*), DebugDrawCullingBounds);
		return DebugDrawCullingBounds(this);
	}
	auto CheckVisibility() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseEntity*), CheckVisibility);
		return CheckVisibility(this);
	}
	auto IsOutside() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseEntity*), IsOutside);
		return IsOutside(this);
	}
	auto get_IsNpc() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseEntity*), get_IsNpc);
		return get_IsNpc(this);
	}
	auto InheritedVelocityDirection() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseEntity*), InheritedVelocityDirection);
		return InheritedVelocityDirection(this);
	}
	void ServerRPC(const wchar_t* func) {
		if (!this) return;
		auto off = reinterpret_cast<void (*)(BaseEntity*, unity_system::string)>(*reinterpret_cast<uintptr_t*>(StaticClass()->GetMethodFromName("ServerRPC", 1, "funcName")));
		return off(this, unity_system::string(func));
	}
};