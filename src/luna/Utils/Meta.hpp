#pragma once

#include <type_traits>
#include <variant>

namespace luna {
template<typename T, typename... Types>
constexpr size_t get_variant_index() {
	size_t index	   = 0;
	size_t match_index = -1;

	((std::is_same_v<T, Types> ? (match_index = index, false) : (index++, true)) && ...);

	return match_index;
}

template<typename T, typename Variant>
struct variant_index_of;

template<typename T, typename... Types>
struct variant_index_of<T, std::variant<Types...>> {
	static constexpr size_t value = get_variant_index<T, Types...>();
};

template<typename T, typename Variant>
inline constexpr size_t variant_index_of_v = variant_index_of<T, Variant>::value;

}  // namespace luna
