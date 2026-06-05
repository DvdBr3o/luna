#pragma once

#include <concepts>
#include <functional>
#include <new>

namespace luna {
template<typename A>
concept Allocator = requires(A a, std::size_t n) {
	typename std::remove_cvref_t<A>::value_type;
	{ a.allocate(n) } -> std::same_as<typename std::remove_cvref_t<A>::value_type*>;
	{ a.deallocate(std::declval<typename std::remove_cvref_t<A>::value_type*>(), n) };
};

template<typename F>
struct MustCall {
	F f;

	explicit MustCall(F&& f) : f(std::forward<F>(f)) {}

	MustCall(const MustCall&) = delete;
	MustCall(MustCall&&)	  = delete;
	template<typename TT>
	operator TT() = delete;

	template<typename... Args>
	constexpr auto operator()(Args&&... args) && {
		return f(std::forward<Args>(args)...);
	}
};

template<typename T>
[[nodiscard]] inline constexpr auto alloc(Allocator auto&& a) -> T* {
	return MustCall {[&a]<typename... Args>(Args&&... args) {
		auto* ptr = a.allocate(1);
		return new (ptr) T {std::forward<Args>(args)...};
	}};
}

template<typename T, typename... Args>
inline constexpr auto alloc(Allocator auto&& a, Args&&... args) -> T* {
	auto* ptr = a.allocate(1);
	return new (ptr) T {std::forward<Args>(args)...};
}

}  // namespace luna