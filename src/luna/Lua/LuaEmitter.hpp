#pragma once

#include <mlir/IR/Operation.h>

namespace luna::Lua {
class LuaEmitter {
public:
public:
	auto emit_operation(mlir::Operation* op) -> LuaEmitter& {
		// TODO:
		return *this;
	}

	auto give() && -> std::string { return std::move(_result); }

private:
	std::string _result;
};
}  // namespace luna::Lua