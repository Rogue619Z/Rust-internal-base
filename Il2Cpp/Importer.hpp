#include "Crt.hpp"


#define SAPPHIRE_FUNC( mod, type ) reinterpret_cast< decltype( &type ) >( sapphire::get_exported_function( sapphire::get_sapphire_module( ##mod ), #type ) )
#define SAPPHIRE_TYPE( mod, type ) reinterpret_cast< type >( sapphire::get_exported_function( sapphire::get_sapphire_module( ##mod ), #type ) );

namespace sapphire {
#define contains_record( address, type, field ) ( ( type* )( ( char* )( address ) - ( std::uintptr_t )( & ( (type* ) 0 ) -> field ) ) )
#define loword(l) ((std::uint16_t)(((std::uintptr_t)(l)) & 0xffff))

	struct saph_module_t
	{
		void* base;
		const wchar_t* name;
		size_t size;
		saph_module_t(void* b, const wchar_t* n, size_t s) : base(b), name(n), size(s) {}
		saph_module_t() : base(0), name(L""), size(0) {}
	};

	namespace nt
	{
		struct list_entry
		{
			struct list_entry* Flink;
			struct list_entry* Blink;
		};

		struct unicode_string
		{
			unsigned short Length;
			unsigned short MaximumLength;
			wchar_t* Buffer;
		};

		struct peb_ldr_data
		{
			unsigned long Length;
			unsigned long Initialized;
			const char* SsHandle;
			list_entry InLoadOrderModuleList;
			list_entry InMemoryOrderModuleList;
			list_entry InInitializationOrderModuleList;
		};

		struct peb
		{
			unsigned char   Reserved1[2];
			unsigned char   BeingDebugged;
			unsigned char   Reserved2[1];
			const char* Reserved3[2];
			peb_ldr_data* Ldr;
		};

		struct ldr_data_table_entry
		{
			list_entry InLoadOrderModuleList;
			list_entry InMemoryOrderLinks;
			list_entry InInitializationOrderModuleList;
			void* DllBase;
			void* EntryPoint;
			union {
				unsigned long SizeOfImage;
				const char* _dummy;
			};
			unicode_string FullDllName;
			unicode_string BaseDllName;
		};

		struct image_dos_header
		{
			unsigned short e_magic;
			unsigned short e_cblp;
			unsigned short e_cp;
			unsigned short e_crlc;
			unsigned short e_cparhdr;
			unsigned short e_minalloc;
			unsigned short e_maxalloc;
			unsigned short e_ss;
			unsigned short e_sp;
			unsigned short e_csum;
			unsigned short e_ip;
			unsigned short e_cs;
			unsigned short e_lfarlc;
			unsigned short e_ovno;
			unsigned short e_res[4];
			unsigned short e_oemid;
			unsigned short e_oeminfo;
			unsigned short e_res2[10];
			long e_lfanew;
		};

		struct image_file_header
		{
			unsigned short Machine;
			unsigned short NumberOfSections;
			unsigned long TimeDateStamp;
			unsigned long PointerToSymbolTable;
			unsigned long NumberOfSymbols;
			unsigned short SizeOfOptionalHeader;
			unsigned short Characteristics;
		};

		struct image_export_directory
		{
			unsigned long Characteristics;
			unsigned long TimeDateStamp;
			unsigned short MajorVersion;
			unsigned short MinorVersion;
			unsigned long Name;
			unsigned long Base;
			unsigned long NumberOfFunctions;
			unsigned long NumberOfNames;
			unsigned long AddressOfFunctions;
			unsigned long AddressOfNames;
			unsigned long AddressOfNameOrdinals;
		};

		struct image_data_directory
		{
			unsigned long VirtualAddress;
			unsigned long Size;
		};

		struct image_optional_header
		{
			unsigned short Magic;
			unsigned char MajorLinkerVersion;
			unsigned char MinorLinkerVersion;
			unsigned long SizeOfCode;
			unsigned long SizeOfInitializedData;
			unsigned long SizeOfUninitializedData;
			unsigned long AddressOfEntryPoint;
			unsigned long BaseOfCode;
			unsigned long long ImageBase;
			unsigned long SectionAlignment;
			unsigned long FileAlignment;
			unsigned short MajorOperatingSystemVersion;
			unsigned short MinorOperatingSystemVersion;
			unsigned short MajorImageVersion;
			unsigned short MinorImageVersion;
			unsigned short MajorSubsystemVersion;
			unsigned short MinorSubsystemVersion;
			unsigned long Win32VersionValue;
			unsigned long SizeOfImage;
			unsigned long SizeOfHeaders;
			unsigned long CheckSum;
			unsigned short Subsystem;
			unsigned short DllCharacteristics;
			unsigned long long SizeOfStackReserve;
			unsigned long long SizeOfStackCommit;
			unsigned long long SizeOfHeapReserve;
			unsigned long long SizeOfHeapCommit;
			unsigned long LoaderFlags;
			unsigned long NumberOfRvaAndSizes;
			image_data_directory DataDirectory[16];
		};

		struct image_nt_headers {
			unsigned long Signature;
			image_file_header FileHeader;
			image_optional_header OptionalHeader;
		};
	}

	inline auto get_sapphire_module(const wchar_t* name) -> const sapphire::saph_module_t
	{

		const sapphire::nt::peb* peb = reinterpret_cast<sapphire::nt::peb*>(__readgsqword(0x60));
		if (!peb)
			return {}; // how the fuck did we even get here?

		const sapphire::nt::list_entry head = peb->Ldr->InMemoryOrderModuleList;

		for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink)
		{
			sapphire::nt::ldr_data_table_entry* mod = reinterpret_cast<sapphire::nt::ldr_data_table_entry*>(contains_record(curr.Flink, sapphire::nt::ldr_data_table_entry, InMemoryOrderLinks));

			if (mod->BaseDllName.Buffer)
			{
				if (Crt::wcsicmp_insensitive(mod->BaseDllName.Buffer, name))
				{
					return sapphire::saph_module_t{ mod->DllBase, mod->BaseDllName.Buffer, mod->SizeOfImage };
				}
			}
		}

		return {};
	}

	inline auto get_exported_function(const sapphire::saph_module_t module, const char* function) -> const void*
	{
		if (!module.base)
			return {};

		const auto base = reinterpret_cast<std::uintptr_t>(module.base);
		const sapphire::nt::image_dos_header* dos_header = reinterpret_cast<sapphire::nt::image_dos_header*>(base);
		const sapphire::nt::image_nt_headers* nt_header = reinterpret_cast<sapphire::nt::image_nt_headers*>(base + dos_header->e_lfanew);

		const sapphire::nt::image_data_directory* data_directory = reinterpret_cast<const sapphire::nt::image_data_directory*>(&nt_header->OptionalHeader.DataDirectory[0]);
		const sapphire::nt::image_export_directory* image_export_directory = reinterpret_cast<sapphire::nt::image_export_directory*>(base + data_directory->VirtualAddress);

		const auto* const rva_table = reinterpret_cast<const unsigned long*>(base + image_export_directory->AddressOfFunctions);
		const auto* const ord_table = reinterpret_cast<const unsigned short*>(base + image_export_directory->AddressOfNameOrdinals);

		if (image_export_directory)
		{
			for (unsigned int idx{ 0 }; idx < image_export_directory->NumberOfNames; idx++)
			{
				const auto fn_name = reinterpret_cast<const char*>(base + reinterpret_cast<const unsigned long*>(base + image_export_directory->AddressOfNames)[idx]);

				if (Crt::strcmp(fn_name, function))
					return reinterpret_cast<void*>(base + ((std::uint32_t*)(base + image_export_directory->AddressOfFunctions))[ord_table[idx]]);
			}
		}

		return { };
	}
}