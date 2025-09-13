#pragma once

#include <cstddef>

namespace luna {
	inline static consteval auto bit(std::size_t x) {
		return 1 << x;
	}
}  // namespace luna