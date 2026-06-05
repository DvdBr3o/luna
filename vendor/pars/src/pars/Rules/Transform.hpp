#pragma once

#include "pars/Meta.hpp"
#include "pars/Query.hpp"
#include "tl/expected.hpp"

#include <concepts>
#include <type_traits>
#include <utility>

namespace pars {
template<typename RuleT, typename FnT>
struct ValueTransformRule {
	RuleT rule;
	FnT	  fn;

	using required_queries_type = required_queries_of_rules_t<RuleT>;

	template<typename StateT>
	using Value = std::invoke_result_t<FnT, rule_value_t<StateT, RuleT>>;
	template<typename StateT>
	using Error = rule_error_t<StateT, RuleT>;
	template<typename StateT>
	using Result = Expected<Value<StateT>, Error<StateT>>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const -> Result<StateT> {
		auto res = rule.match(std::forward<StateT>(st));
		if (res)
			std::invoke(fn, std::move(value_of(res)));
		else
			return tl::make_unexpected(std::move(error_of(res)));
	}

	inline friend constexpr auto operator==(
		const ValueTransformRule& l, const ValueTransformRule& r
	) -> bool {
		return l.rule == r.rule;
	}
};	// namespace pars

template<typename FnT>
struct ValueTransformFunctor {
	FnT fn;
};

template<typename RuleT, typename FnT>
inline constexpr auto operator%=(RuleT&& rule, ValueTransformFunctor<FnT>&& functor)
	-> ValueTransformRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename RuleT, typename FnT>
inline constexpr auto operator^(RuleT&& rule, ValueTransformFunctor<FnT>&& functor)
	-> ValueTransformRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename FnT>
inline constexpr auto value_to(FnT&& fn) -> ValueTransformFunctor<FnT> {
	return {std::forward<FnT>(fn)};
}

template<typename RuleT, typename FnT>
struct ValueApplyRule {
	RuleT rule;
	FnT	  fn;

	using required_queries_type = required_queries_of_rules_t<RuleT>;

	template<typename StateT>
	using Value = apply_result_t<FnT, rule_value_t<StateT, RuleT>>;
	template<typename StateT>
	using Error = rule_error_t<StateT, RuleT>;
	template<typename StateT>
	using Result = Expected<Value<StateT>, Error<StateT>>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const -> Result<StateT> {
		auto res = rule.match(std::forward<StateT>(st));
		if (res)
			return std::apply(
				[&]<typename... ResTs>(ResTs&&... res) {
					return std::invoke(fn, std::forward<ResTs>(res)...);
				},
				std::move(value_of(res))
			);
		else
			return tl::make_unexpected(std::move(error_of(res)));
	}
};

template<typename FnT>
struct ValueApplyFunctor {
	FnT fn;
};

template<typename RuleT, typename FnT>
inline constexpr auto operator%=(RuleT&& rule, ValueApplyFunctor<FnT>&& functor)
	-> ValueApplyRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename RuleT, typename FnT>
inline constexpr auto operator^(RuleT&& rule, ValueApplyFunctor<FnT>&& functor)
	-> ValueApplyRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename FnT>
inline constexpr auto value_apply(FnT&& fn) -> ValueApplyFunctor<FnT> {
	return {std::forward<FnT>(fn)};
}

template<typename RuleT, typename... FnTs>
struct ValueVisitRule {
	RuleT				rule;
	std::tuple<FnTs...> fns;

	using required_queries_type = required_queries_of_rules_t<RuleT>;

	template<typename StateT>
	using Value = decltype(std::visit(
		std::declval<overload<FnTs...>>(), std::declval<rule_value_t<StateT, RuleT>>()
	));
	template<typename StateT>
	using Error = rule_error_t<StateT, RuleT>;
	template<typename StateT>
	using Result = Expected<Value<StateT>, Error<StateT>>;

	template<typename StateT>
	constexpr auto match(StateT&& st) const -> Result<StateT> {
		auto res = rule.match(std::forward<StateT>(st));
		if (res)
			return std::apply(
				[&](auto&&... fns) {
					return std::visit(
						overload {std::forward<FnTs>(fns)...},
						std::move(res.value())
					);
				},
				fns
			);
		else
			return tl::make_unexpected(std::move(error_of(res)));
	}
};

template<typename FnT>
struct ValueVisitFunctor {
	FnT fn;
};

template<typename RuleT, typename FnT>
inline constexpr auto operator%=(RuleT&& rule, ValueVisitFunctor<FnT>&& functor)
	-> ValueVisitRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename RuleT, typename FnT>
inline constexpr auto operator^(RuleT&& rule, ValueVisitFunctor<FnT>&& functor)
	-> ValueApplyRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename FnT>
inline constexpr auto value_visit(FnT&& fn) -> ValueVisitFunctor<FnT> {
	return {std::forward<FnT>(fn)};
}

template<typename RuleT, typename FnT>
struct ResultTransformRule : RuleT {
	FnT fn;

	template<typename StateT>
	constexpr auto match(StateT&& st) const {
		return std::invoke(fn, this->RuleT::match(std::forward<StateT>(st)));
	}

	inline friend constexpr auto operator==(
		const ResultTransformRule& l, const ResultTransformRule& r
	) -> bool {
		return l.rule == r.rule;
	}
};

template<typename FnT>
struct ResultTransformFunctor {
	FnT fn;
};

template<typename RuleT, typename FnT>
inline constexpr auto operator%=(RuleT&& rule, ResultTransformFunctor<FnT>&& functor)
	-> ResultTransformRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename RuleT, typename FnT>
inline constexpr auto operator^(RuleT&& rule, ResultTransformFunctor<FnT>&& functor)
	-> ResultTransformRule<RuleT, FnT> {
	return {std::forward<RuleT>(rule), std::forward<FnT>(functor.fn)};
}

template<typename FnT>
inline constexpr auto result_to(FnT&& fn) -> ResultTransformFunctor<FnT> {
	return {std::forward<FnT>(fn)};
}

}  // namespace pars
