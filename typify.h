#pragma once

#include "string_utils.h"

namespace dug::typify
{
	namespace detail
	{
		template <typename... T>
		consteval const char* function_name()
		{
			return __FUNCSIG__;
		}
	}

	template <typename char_type, typename... T>
	constexpr auto basic_get()
	{
#ifdef _MSC_VER
		constexpr char START = '<';
		constexpr char END = '>';
#elif defined(__GNUC__)
		constexpr char START = '{';
		constexpr char END = '}';
#endif

		constexpr const char_type* f = detail::function_name<T...>();

		constexpr size_t start = string::find(f, START) + 1;
		constexpr size_t end = string::find(f, END);

		return string::fixed_string<char_type, end - start>(f, start, std::make_index_sequence<end - start>{});
	}

	template <typename... T>
	constexpr auto get()
	{
		return basic_get<char, T...>();
	}
}