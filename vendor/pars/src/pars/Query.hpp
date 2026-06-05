#pragma once

#include "pars/Meta.hpp"

#include <utility>

namespace pars {
template<typename T>
concept QueryTagC = requires { typename T::Queryable; };

template<QueryTagC QueryT>
struct QueryState {
	QueryT::Queryable queryable;

	// TODO: provide reflection info of queryable type, and provide a aggregation tools for state
	// derived from multiple `QueryState`.

	constexpr auto query(this auto&& self, QueryT) -> decltype(auto) {
		return (self.QueryState::queryable);
	}

	template<typename Derived>
	inline friend constexpr auto query(Derived&& derived, QueryT) -> decltype(auto)
		requires std::derived_from<std::remove_cvref_t<Derived>, QueryState>
	{
		return (std::forward_like<Derived>(static_cast<QueryState&>(derived)).queryable);
	}
};

template<typename QueryableT>
struct QueryTag {
	using Queryable = QueryableT;

	template<typename Self, typename QueryableTT>
	constexpr auto operator()(this Self&& self, QueryableTT&& queryable) -> decltype(auto) {
		return query(std::forward<QueryableTT>(queryable), Self {});
	}
};

template<typename T, typename QueryT>
inline constexpr auto query(T&& t, QueryT q) -> decltype(auto)
	requires requires { t.query(q); }
{
	return (t.query(q));
}

template<typename T, typename QueryT>
using query_t = decltype(query(std::declval<T>(), std::declval<QueryT>()));

template<typename... Ts>
using required_queries_of_rules_t =
	tuple_cup_t<typename std::remove_cvref_t<Ts>::required_queries_type...>;

}  // namespace pars
