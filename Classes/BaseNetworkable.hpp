

class BaseNetworkable : public Component
{
public:
	CLASS("", "BaseNetworkable");

	MEMBER(std::uintptr_t*, net);

	bool PlayerValid() {
		if (!this) return false;
		return !this->PlayerDestroyed() && this->net() != nullptr;
	}
	auto PlayerDestroyed() -> bool
	{
		if (!this) return false;
		static auto k__BackingField = Il2CppWrapper::GetClassFromName("", "BaseNetworkable")->GetFieldFromName("<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + k__BackingField);
	}
	auto HasParent() -> bool
	{
		if (!this) return false;
		METHOD(bool(**)(BaseNetworkable*), HasParent);
		return HasParent(this);
	}
	auto get_ShortPrefabName() -> unity_system::string
	{
		if (!this) return 0;
		METHOD(unity_system::string(**)(BaseNetworkable*), get_ShortPrefabName);
		return get_ShortPrefabName(this);
	}
	auto GetParentEntity() -> std::uintptr_t
	{
		if (!this) return 0;
		METHOD(std::uintptr_t(**)(BaseNetworkable*), GetParentEntity);
		return GetParentEntity(this);
	}
	static auto clientEntities() -> ListDictionary*
	{
		static auto clientEntities = reinterpret_cast<ListDictionary*>(Il2CppWrapper::GetClassFromName("", "BaseNetworkable")->GetFieldFromName("clientEntities", false));
		return clientEntities;
	}
};