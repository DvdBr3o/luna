#pragma once

#include <string_view>
#include <cstdint>

namespace luna {
	struct SourceLocation {
		std::string_view::const_iterator where;
		std::uint32_t					 line;
		std::uint32_t					 col;
	};

	struct SourceLocationScope {
		SourceLocation from;
		SourceLocation to;
	};
}  // namespace luna
