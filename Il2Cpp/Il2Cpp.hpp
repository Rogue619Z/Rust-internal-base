#include "Crt.hpp"

namespace memory
{
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}
	template<typename t>
	inline auto valid_pointer(t pointer) -> bool {
		return (pointer && pointer > (t)0x400000 && pointer < (t)0x7FFFFFFFFFFF);
	}
}

#define CLASS( nameSpace, className ) static Il2CppClass* StaticClass()										\
									  {																		 \
										return Il2CppWrapper::GetClassFromName(nameSpace, className);         \
									  }	                                                                       																	

#define STATIC_MEMBER( type, name ) static type & name( ) { static auto field_##name = uintptr_t( StaticClass( )->GetFieldFromName( #name ) ); return *reinterpret_cast< type* >( field_##name ); }
#define METHOD( type, name ) static auto name = *reinterpret_cast< type >( StaticClass( )->GetMethodFromName( #name ) );																	   
#define MEMBER( type, name ) type & name( ) { static uintptr_t name = StaticClass( )->GetFieldFromName( #name, true ); return *reinterpret_cast< type* >( this + name ); }
#define FIELD( name ) static std::uintptr_t name =  StaticClass( )->GetFieldFromName( #name, true );

class Il2CppField
{
public:
	auto il2cpp_field_get_offset() -> Il2CppField*
	{
		static auto il2cpp_field_get_offset = reinterpret_cast<Il2CppField * (*)(Il2CppField*)>(Crt::il2cpp_export("il2cpp_field_get_offset"));
		return il2cpp_field_get_offset(this);
	}

	auto il2cpp_field_get_name() -> const char*
	{
		static auto il2cpp_field_get_name = reinterpret_cast<const char* (*)(Il2CppField*)>(Crt::il2cpp_export("il2cpp_field_get_name"));
		return il2cpp_field_get_name(this);
	}

	auto il2cpp_field_static_get_value(uintptr_t* i) -> Il2CppField*
	{
		static auto il2cpp_field_static_get_value = reinterpret_cast<Il2CppField * (*)(Il2CppField*, uintptr_t*)>(Crt::il2cpp_export("il2cpp_field_static_get_value"));
		return il2cpp_field_static_get_value(this, i);
	}
};

class Il2CppMethod
{
public:
	auto il2cpp_method_get_param_count() -> int
	{
		static auto il2cpp_method_get_param_count = reinterpret_cast<int (*)(Il2CppMethod*)>(Crt::il2cpp_export("il2cpp_method_get_param_count"));
		return il2cpp_method_get_param_count(this);
	}
};

class Il2CppType
{
public:
	auto il2cpp_type_get_object() -> Il2CppType*
	{
		static auto il2cpp_type_get_object = reinterpret_cast<Il2CppType * (*)(Il2CppType*)>(Crt::il2cpp_export(__func__));
		return il2cpp_type_get_object(this);
	}
};

class Il2CppObject {
public:

};

class Il2CppClass : public Il2CppObject
{
private:
	auto il2cpp_class_get_fields(uintptr_t* iter) -> Il2CppField*
	{
		static auto il2cpp_class_get_fields = reinterpret_cast<Il2CppField * (*)(Il2CppClass*, uintptr_t*)>(Crt::il2cpp_export("il2cpp_class_get_fields"));
		return il2cpp_class_get_fields(this, iter);
	}

	auto il2cpp_class_get_methods(uintptr_t* iter) -> Il2CppMethod*
	{
		static auto il2cpp_class_get_methods = reinterpret_cast<Il2CppMethod * (*)(Il2CppClass*, uintptr_t*)>(Crt::il2cpp_export("il2cpp_class_get_methods"));
		return il2cpp_class_get_methods(this, iter);
	}

	auto FieldInternal(const char* name, bool offset = true) -> Il2CppField*
	{
		auto iterator = uintptr_t();

		while (auto field = il2cpp_class_get_fields(&iterator))
		{
			auto field_name = field->il2cpp_field_get_name();
			if (!field_name || !memory::valid_pointer(field_name))
				break;

			if (!Crt::strcmp(field_name, name))
				continue;

			if (!offset)
				return field;

			return field->il2cpp_field_get_offset();
		}

		return { };
	}
public:
	auto parent() -> Il2CppClass*
	{
		return *reinterpret_cast<Il2CppClass**>(this + 0x58);
	}

	auto static_fields() -> uintptr_t
	{
		return *reinterpret_cast<uintptr_t*>(this + 0xB8);
	}

	auto il2cpp_class_get_type() -> Il2CppType*
	{
		static auto il2cpp_class_get_type = reinterpret_cast<Il2CppType * (*)(Il2CppClass*)>(Crt::il2cpp_export("il2cpp_class_get_type"));
		return il2cpp_class_get_type(this);
	}

	auto GetMethodFromName(const char* name, int arg_count = -1, const char* arg_name = "", int selected_arg = -1) -> Il2CppMethod*
	{
		auto iterator = uintptr_t();

		while (auto method = il2cpp_class_get_methods(&iterator))
		{
			auto method_name = *reinterpret_cast<const char**>(method + 0x10);

			if (!memory::valid_pointer(method_name))
				continue;

			if (Crt::strcmp(method_name, name))
			{
				auto param_count = method->il2cpp_method_get_param_count();

				if (arg_count >= 0 && param_count != arg_count)
					continue;

				if (selected_arg >= 0 && arg_name)
				{
					auto args = *reinterpret_cast<std::uintptr_t*>(method + 0x28);

					if (selected_arg > param_count)
						continue;
					char* param_name;

					if (param_count > 0)
						param_name = *reinterpret_cast<char**>(args + (selected_arg - 1) * 0x18);
					else
						param_name = (char*)("-");

					if (!memory::valid_pointer(param_name))
						continue;

					if (!param_name || !Crt::strcmp(param_name, arg_name))
						continue;
				}

				return method;
			}

		}

		return { };
	}

	auto GetFieldFromName(const char* name, bool offset = true) -> uintptr_t
	{
		if (offset)
			return uintptr_t(FieldInternal(name));

		auto field = FieldInternal(name, false);

		uintptr_t ret{ };
		field->il2cpp_field_static_get_value(&ret);

		return ret;
	}
};

class Il2CppString
{
public:
	decltype(auto) il2cpp_string_new()
	{

	}
};

class Il2CppImage
{
public:
	decltype(auto) il2cpp_class_from_name(const char* name_space, const char* klass)
	{
		static auto il2cpp_class_from_name = reinterpret_cast<Il2CppClass * (*)(Il2CppImage*, const char*, const char*)>(Crt::il2cpp_export("il2cpp_class_from_name"));
		return il2cpp_class_from_name(this, name_space, klass);
	}
};

class Il2CppAssemblies
{
public:

	decltype(auto) il2cpp_assembly_get_image()
	{
		static auto il2cpp_assembly_get_image = reinterpret_cast<Il2CppImage * (*)(Il2CppAssemblies*)>(Crt::il2cpp_export(__func__));
		return il2cpp_assembly_get_image(this);
	}
};

class Il2CppDomain
{
public:
	decltype(auto) il2cpp_domain_get_assemblies(uintptr_t* list)
	{
		static auto il2cpp_domain_get_assemblies = reinterpret_cast<Il2CppAssemblies * *(*)(Il2CppDomain*, uintptr_t*)>(Crt::il2cpp_export(__func__));
		return il2cpp_domain_get_assemblies(this, list);
	}

	static decltype(auto) il2cpp_domain_get()
	{
		static auto il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (*)()>(Crt::il2cpp_export("il2cpp_domain_get"));
		return il2cpp_domain_get();
	}
};

class Il2CppWrapper
{
public:
	static decltype(auto) il2cpp_thread_attach()
	{
		static auto il2cpp_thread_attach = reinterpret_cast<void(*)()>(Crt::il2cpp_export("il2cpp_thread_attach"));
		return il2cpp_thread_attach();
	}

	template< typename t >
	static decltype(auto) il2cpp_object_new(void* object)
	{
		static auto il2cpp_object_new = reinterpret_cast<t(*)(void*)>(Crt::il2cpp_export(__func__));
		return il2cpp_object_new(object);
	}

	static auto GetClassFromName(const char* nameSpace, const char* className) -> Il2CppClass*
	{
		auto domain = Il2CppDomain::il2cpp_domain_get();

		auto assembly_count = uint64_t();
		auto assemblies = domain->il2cpp_domain_get_assemblies(&assembly_count);

		for (size_t idx{ 0 }; idx < assembly_count; idx++)
		{
			auto image = assemblies[idx]->il2cpp_assembly_get_image();
			if (!image)
				continue;
			auto klass = image->il2cpp_class_from_name(nameSpace, className);
			if (!klass)
				continue;

			return klass;
		}

		return {};
	}


	static auto Type(const char* nameSpace, const char* className) -> void*
	{
		auto klass = GetClassFromName(nameSpace, className);
		if (!klass)
			return { };

		return klass->il2cpp_class_get_type()->il2cpp_type_get_object();
	}

};