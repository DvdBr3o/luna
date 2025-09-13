#pragma once

#include <string_view>
#include <unordered_map>

namespace luna {
	class CommandLine {
	public:
		// TODO:    
	private:
		std::unordered_map<std::string_view, std::string_view> _args;
	};
}  // namespace luna