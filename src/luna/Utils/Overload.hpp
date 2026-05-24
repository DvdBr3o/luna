#pragma once

#include <concepts>
#include <variant>

namespace luna {
template<typename... Ts>
struct overload : Ts... {
	using Ts::operator()...;
};

template<typename V, typename... Ts>
inline constexpr auto operator|(V&& v, overload<Ts...>&& o) -> decltype(auto) {
	return std::visit(std::forward<overload<Ts...>>(o), std::forward<V>(v));
}
}  // namespace luna