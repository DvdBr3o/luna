#pragma once

#include <cstdint>
#include <variant>

namespace luna {
	struct ScopeBase {
		std::uint32_t depth;
	};

	struct LambdaScope : public ScopeBase {
        
    };

	struct TableScope : public ScopeBase {
        
    };

	using Scope = std::variant<LambdaScope, TableScope>;
}  // namespace luna