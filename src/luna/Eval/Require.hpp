#pragma once

#include "luna/Eval/Val.hpp"

#include <fmt/core.h>

#include <filesystem>
#include <ranges>
#include <string_view>

namespace luna::Eval {
/// @brief require a luna module, same as lua `require`.
///
/// @param cwd path of current working module
/// @param mod_path path string of target module, in luna module style e.g. "foo.bar" for
/// "./foo/bar.luna"
inline auto require(const std::filesystem::path& cwd, std::string_view mod_path) -> Val {
	std::filesystem::path target = [mod_path, &cwd]() {
		auto split_view = mod_path | std::views::split('.');
		return std::accumulate(
			split_view.begin(),
			split_view.end(),
			cwd,
			[](const std::filesystem::path& acc, auto sub) {
				return acc / std::string_view {sub.begin(), sub.end()};
			}
		);
	}();
	target.replace_extension("luna");

	// TODO:

	return {};
}
}  // namespace luna::Eval
