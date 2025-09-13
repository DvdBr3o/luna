#pragma once

namespace luna {
	template<typename... Ts>
	struct overload : Ts... {
		using Ts::operator()...;
	};

	struct VariantEqual {
		template<typename T, typename U>
		auto operator()(T&& lhs, U&& rhs) const -> bool {
			return false;
		}

		template<typename T>
		auto operator()(T&& lhs, T&& rhs) const -> bool {
			return lhs == rhs;
		}
	};

	inline static constexpr auto variant_equal = VariantEqual {};
}  // namespace luna