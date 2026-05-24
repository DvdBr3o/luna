#pragma once

#include <filesystem>
#include <cstdint>

namespace luna {
struct Location {
	std::uint32_t line;
	std::uint32_t column;
};

struct SourceLocation {
	std::filesystem::path path;
	Location			  loc;
};

struct SourceRegion {
	std::filesystem::path path;
	Location			  begin;
	Location			  end;
};
}  // namespace luna