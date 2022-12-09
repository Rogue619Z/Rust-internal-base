class SafeExecution {
private:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};

class Component
{
public:
	CLASS("UnityEngine", "Component");

	auto transform() -> Transform*
	{
		if (!this) return nullptr;
		METHOD(Transform * (**)(Component*), get_transform);
		return get_transform(this);
	}
	//GameObject* gameObject() {
	//	if (!this) return nullptr;
	//	static auto off = (std::uintptr_t)StaticClass()->GetMethodFromName("get_gameObject");
	//	return SafeExecution::Execute<GameObject*>(off, nullptr, this);
	//}
	auto get_gameObject() -> GameObject*
	{
		if (!this) return nullptr;
		METHOD(GameObject * (**)(Component*), get_gameObject);
		return get_gameObject(this);
	}
	auto GetComponent(void* type) -> Component*
	{
		if (!this) return nullptr;
		METHOD(Component * (**)(Component*, void*), GetComponent);
		return GetComponent(this, type);
	}
	const char* class_name() {
		if (!this) return "";
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	uint32_t class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
};