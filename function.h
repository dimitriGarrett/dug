#pragma once

#include "pack.h"

namespace dug::function
{
	namespace detail
	{
		template <bool P, bool C, typename R, typename... Args>
		struct traits
		{
			using return_type = R;

			static constexpr size_t arity = sizeof...(Args);

			static constexpr bool is_pointer = P;
			static constexpr bool is_const = C;

			template <size_t N>
			using arg = pack::nth_type<N, Args...>;
		};
	}

	template <typename L> requires std::is_function_v<L>
	struct traits : public traits<decltype(&L::operator())>
	{
		static constexpr bool is_lambda = true;
	};

	template <typename R, typename... Args> 
	struct traits<R(Args...)> : public detail::traits<false, false, R, Args...> {};
	template <typename R, typename... Args>
	struct traits<R(*)(Args...)> : public detail::traits<true, false, R, Args...> {};
	template <typename R, typename C, typename... Args>
	struct traits<R(C::*)(Args...)> : public detail::traits<false, true, R, Args...> { using class_type = C; };
	template <typename R, typename C, typename... Args>
	struct traits<R(C::*)(Args...) const> : public detail::traits<true, true, R, Args...> { using class_type = C; };
}