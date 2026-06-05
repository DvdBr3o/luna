#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <variant>

namespace luna {
template<typename H, typename... VTs>
inline constexpr auto absl_hash_variant(H h, const std::variant<VTs...>& v) -> H {
	return H::combine(std::move(h), v.index(), v);
}
}  // namespace luna
