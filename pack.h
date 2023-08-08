#pragma once

using size_t = decltype(sizeof(nullptr));

#include <utility>

namespace dug::pack
{
	namespace detail
	{
		template <size_t N, typename Arg, typename... Args>
		struct nth_value_impl
		{
			static_assert(N <= sizeof...(Args), "Invalid index for nth_value<N, Args>!");
			
			using type = typename nth_value_impl<N - 1, Args...>::type;

			static constexpr type eval(Arg&&, Args&&... args)
			{
				return nth_value_impl<N - 1, Args...>::eval(std::forward<Args>(args)...);
			}
		};

		template <typename Arg, typename... Args>
		struct nth_value_impl<0, Arg, Args...>
		{
			using type = Arg;

			static constexpr type eval(Arg&& arg, Args&&...)
			{
				return std::forward<Arg>(arg);
			}
		};
	}

	template <size_t N, typename... Args>
	constexpr decltype(auto) nth_value(Args&&... args)
	{
		return detail::nth_value_impl<N, Args...>::eval(std::forward<Args>(args)...);
	}

	template <typename... Args>
	constexpr decltype(auto) first_value(Args&&... args)
	{
		return nth_value<0>(std::forward<Args>(args)...);
	}

	template <typename... Args>
	constexpr decltype(auto) last_value(Args&&... args)
	{
		return (std::forward<Args>(args), ...);
	}

	template <size_t N, typename... Args>
	using nth_type = detail::nth_value_impl<N, Args...>::type;

	template <typename... Args>
	using first_type = nth_type<0, Args...>;

	template <typename... Args>
	using last_type = nth_type<sizeof...(Args) - 1, Args...>;
}