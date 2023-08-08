#pragma once

#include <utility>
#include <cstdint>

namespace dug::string
{
	inline constexpr size_t npos = static_cast<size_t>(-1);

	template <typename char_type = char>
	constexpr size_t length(const char_type* str)
	{
		return str[0] == '\0' ? 0 : length(str + 1) + 1;
	}

	template <typename char_type = char>
	constexpr size_t find(const char_type* str, char_type c)
	{
		for (size_t i = 0; i < length(str); ++i)
			if (c == str[i]) return i;
		return npos;
	}

	template <typename char_type = char>
	constexpr size_t distance(const char_type* str, char_type first, char_type second)
	{
		return find(str, second) - find(str, first);
	}

#if INTPTR_MAX == INT32_MAX
	constexpr size_t FNVOffset = 2166136261;
	constexpr size_t FNVPrime = 16777619;
#elif INTPTR_MAX == INT64_MAX
	constexpr size_t FNVOffset = 0xcbf29ce484222325;
	constexpr size_t FNVPrime = 1099511628211;
#else
	#error "Unkown architecture"
#endif

	template <typename char_type = char>
	constexpr size_t hash(const char_type* str)
	{
		size_t result = FNVOffset;
		for (size_t i = 0; i < length(str); ++i)
		{
			result ^= str[i]; result *= FNVPrime;
		}
		return result;
	}

	template <typename char_type, size_t N>
	struct fixed_string
	{
		char_type data[N + 1] = { static_cast<char_type>(0) };

		template <size_t... seq>
		consteval fixed_string(const char_type* str, size_t start, std::index_sequence<seq...>)
			: data{ str[start + seq]... }
		{
		}

		template <size_t... seq>
		consteval fixed_string(const char_type* str, std::index_sequence<seq...> s)
			: fixed_string(str, 0, s)
		{
		}

		consteval bool operator==(const char_type* str) const
		{
			if (N != string::length(str))
				return false;

			for (size_t i = 0; i < N; ++i)
				if (data[i] != str[i]) return false;
			return true;
		}

		constexpr operator const char_type* () const
		{
			return data;
		}
	};
}