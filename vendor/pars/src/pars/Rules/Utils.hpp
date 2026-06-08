#pragma once

#include "pars/Rules/Char.hpp"
#include "pars/Rules/Transform.hpp"

#include <utility>

namespace pars {
inline constexpr auto embraced(char32_t l, char32_t r) {
	return [=]<typename RuleT>(RuleT&& rule) constexpr {
		return c(l) >> std::forward<RuleT>(rule) >> c(r)  //
			%= value_apply([](auto&&, auto&& r, auto&&) { return std::forward<decltype(r)>(r); });
	};
}

inline constexpr auto parenthesised = embraced('(', ')');
inline constexpr auto bracketed		= embraced('[', ']');
inline constexpr auto braced		= embraced('{', '}');

inline constexpr auto sp			= cset(' ', '\t');

struct TodoRule {
	constexpr auto match(auto&& state) const -> Expected<std::monostate, std::monostate> {
		static_assert(false, "there is still a todo rule to be implemented!");
	}
};

inline constexpr auto todo = TodoRule {};

}  // namespace pars