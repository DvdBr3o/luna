#pragma once

#include "pars/Arena.hpp"
#include "pars/Meta.hpp"
#include "pars/Query.hpp"
#include "pars/Result.hpp"
#include "pars/Rules/Char.hpp"
#include "pars/Rules/Choice.hpp"
#include "pars/Rules/Sequential.hpp"
#include "pars/Utf.hpp"

#include <type_traits>
#include <variant>

namespace pars {
template<typename Self>
struct FixLazy {
	const Self& self;

	using required_queries_type = required_queries_of_rules_t<std::remove_cvref_t<Self>>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const -> decltype(auto) {
		return self.match(std::forward<StateT>(st));
	}
};

/// @brief Fix point Rule, you can view it as a y-combinator in pars rule combination.
///
/// This is rule receives a function/lambda to construct rule with itself recursively.
template<typename ResultT>
struct FixRule {
	FixRule() = delete ("use `with_query`/`with_state` to continue building fix rule.");

	template<typename FnT, typename... QueryTs>
	struct WithQuery {
		PARS_NO_UNIQUE_ADDRESS FnT fn;

		// TODO: also requires query for Arena, since ast node results of most resursively defined
		// rules are also recursively defined in memory layout, that forces a pointer to break the
		// circumstances in which arena is better than `unique_ptr`.

		// using required_queries_type = sig_cat_t<rq<QueryArena<>>, rq<QueryTs...>>;
		using required_queries_type = rq<QueryTs...>;

		template<typename StateT>
		constexpr auto match(StateT&& st) const -> ResultT {
			return std::invoke(fn, *this).match(std::forward<StateT>(st));
		}

		inline friend constexpr auto operator==(const WithQuery& l, const WithQuery& r) -> bool {
			return true;
		}
	};

	template<typename... QueryTs, typename FnT>
	inline static constexpr auto with_query(FnT&& fn) -> WithQuery<FnT, QueryTs...> {
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

namespace pars::fix_v2 {
namespace details::fix_infer {

template<typename RequiredQueries>
struct InferFixRuleRequiredQueriesVoidRule {
	using required_queries_type = RequiredQueries;

	constexpr auto match(auto&& st) const -> Expected<std::monostate, std::monostate> {
		return Expected<std::monostate, std::monostate>(std::monostate {});
	}

	inline friend constexpr auto operator==(
		const InferFixRuleRequiredQueriesVoidRule&,
		const InferFixRuleRequiredQueriesVoidRule&
	) -> bool {
		return true;
	}
};

template<typename FnT, typename CurrentRequiredQueries>
struct infer_fix_rule_required_queries {
	using next_rq = required_queries_of_rules_t<std::remove_cvref_t<decltype(std::invoke(
		std::declval<FnT>(),
		InferFixRuleRequiredQueriesVoidRule<CurrentRequiredQueries> {}
	))>>;

	template<typename NextRq>
	struct DeducingType {
		using type = infer_fix_rule_required_queries<FnT, NextRq>::type;
	};

	template<>
	struct DeducingType<CurrentRequiredQueries> {
		using type = CurrentRequiredQueries;
	};

	using type = DeducingType<next_rq>::type;
};

template<typename FnT, typename CurrentRequiredQueries = rq<QueryArena<>>>
using infer_fix_rule_required_queries_t =
	infer_fix_rule_required_queries<FnT, CurrentRequiredQueries>::type;

template<typename StateT, typename FnT>
struct FixRuleError;

struct FixRuleErrorPlaceholder {};

template<typename FnT>
struct FixRuleValueVoidRule {
	using required_queries_type = rq<>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const
		-> Expected<std::monostate, Arena<FixRuleErrorPlaceholder>> {
		return std::monostate {};
	}

	inline friend constexpr auto operator==(
		const FixRuleValueVoidRule&, const FixRuleValueVoidRule&
	) -> bool {
		return true;
	}
};

template<typename StateT, typename FnT>
struct FixRuleError {
	using type = rule_error_t<StateT, std::invoke_result_t<FnT, FixRuleValueVoidRule<FnT>>>;
};

}  // namespace details::fix_infer

template<typename ValueT, typename FnT>
struct FixRule {
	PARS_NO_UNIQUE_ADDRESS FnT fn;

	using required_queries_type = details::fix_infer::infer_fix_rule_required_queries_t<FnT>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const
		-> Expected<Arena<ValueT>, Arena<typename details::fix_infer::FixRuleError<StateT, FnT>::type>> {
		auto&&			state		= std::forward<StateT>(st);
		ArenaAllocator& arena		= query_arena<>(state);
		ArenaAllocator& error_arena = query_error_arena<>(state);
		auto			res			= std::invoke(fn, *this).match(state);
		if (res)
			return arena.create<ValueT>(std::move(value_of(res)));
		else
			return error_arena.create<typename details::fix_infer::FixRuleError<StateT, FnT>::type>(
				std::move(error_of(res))
			);
	}
};

template<typename ResultT, typename FnT>
inline constexpr auto fix(FnT&& fn) -> FixRule<value_type_of_t<ResultT>, FnT> {
	return {std::forward<FnT>(fn)};
}

template<typename ValueT, typename FnT>
inline constexpr auto fix_expected(FnT&& fn) -> FixRule<ValueT, FnT> {
	return {std::forward<FnT>(fn)};
}
}  // namespace pars::fix_v2
