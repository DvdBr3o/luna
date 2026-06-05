#pragma once

#include "pars/Arena.hpp"
#include "pars/Meta.hpp"

namespace pars {
/// @brief Fix point Rule, you can view it as a y-combinator in pars rule combination.
///
/// This is rule receives a function/lambda to construct rule with itself recursively.
template<typename ResultT>
struct FixRule {
	FixRule() = delete ("use `of` to continue building fix rule.");

	template<typename FnT, typename... QueryTs>
	struct Of {
		PARS_NO_UNIQUE_ADDRESS FnT fn;

		// TODO: also requires query for Arena, since ast node results of most resursively defined
		// rules are also recursively defined in memory layout, that forces a pointer to break the
		// circumstances in which arena is better than `unique_ptr`.
		// using required_queries_type = tuple_cup_t<std::tuple<QueryArena<>>,
		// std::tuple<QueryTs...>>;
		using required_queries_type = std::tuple<QueryTs...>;

		template<typename StateT>
		constexpr auto match(StateT&& st) const -> ResultT {
			return std::invoke(fn, *this).match(std::forward<StateT>(st));
		}

		inline friend constexpr auto operator==(const Of& l, const Of& r) -> bool { return true; }
	};

	template<typename... QueryTs, typename FnT>
	inline static constexpr auto of(FnT&& fn) -> Of<FnT, QueryTs...> {
		return {std::forward<FnT>(fn)};
	}

	// template<typename StateT, typename FnT>
	// inline static constexpr auto of_state(FnT&& fn) -> templ_from_type_tuple_t<Of,
	// tuple_cup_t<std::tuple<FnT>, std>> { 	return {std::forward<FnT>(fn)};
	// }
};

template<typename ResultT>
using fix = FixRule<ResultT>;

}  // namespace pars
