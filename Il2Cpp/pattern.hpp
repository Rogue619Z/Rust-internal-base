#include "Crt.hpp"
#include "Importer.hpp"

#include <stdlib.h>
#include <stdarg.h>
#include <algorithm>

#define in_range( x, a, b ) ( x >= a && x <= b ) 
#define get_bits( x ) ( in_range( ( x & (~0x20) ), 'A', 'F' ) ? ( ( x & ( ~0x20 ) ) -'A' + 0xa ):( in_range( x, '0', '9' ) ? x - '0' : 0 ) )
#define get_byte( x ) ( get_bits( x[ 0 ] ) << 4 | get_bits( x[ 1 ] ) )

namespace utl {
	namespace pattern
	{
		inline auto find(uintptr_t range_start, uintptr_t range_end, const char* pattern) -> const std::uintptr_t
		{
			const char* pattern_bytes = pattern;

			uintptr_t first_match = 0;

			for (auto cur_byte = range_start; cur_byte < range_end; cur_byte++)
			{
				if (!*pattern_bytes)
					return first_match;

				if (*(uint8_t*)pattern_bytes == '\?' || *(uint8_t*)cur_byte == static_cast<uint8_t>(get_byte(pattern_bytes)))
				{
					if (!first_match)
						first_match = cur_byte;

					if (!pattern_bytes[2])
						return first_match;

					if (*(uint16_t*)pattern_bytes == '\?\?' || *(uint8_t*)pattern_bytes != '\?')
						pattern_bytes += 3;
					else
						pattern_bytes += 2;
				}
				else
				{
					pattern_bytes = pattern;
					first_match = 0;
				}
			}

			return 0;
		}

		inline auto find(const wchar_t* mod, const char* pattern) -> const std::uintptr_t
		{
			auto module = sapphire::get_sapphire_module(mod);

			uintptr_t range_start = std::uintptr_t(module.base);
			uintptr_t range_end = range_start + std::uintptr_t(module.size);

			return find(range_start, range_end, pattern);
		}
	}
}