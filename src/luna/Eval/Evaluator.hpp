#pragma once

#include "luna/Eval/Val.hpp"
#include "luna/Parse/Ast.hpp"

#include <absl/container/flat_hash_map.h>

#include <memory_resource>
#include <span>

namespace luna::Eval {
class Evaluator {
public:
	using Env = Env;

public:
	explicit Evaluator(std::span<char> buffer);

public:
	auto eval(const Parse::ast::Expr& expr) -> Val;

private:
	template<typename ValT, typename... Args>
	auto alloc_val(Args&&... args) -> ValT& {
		auto* ptr = _arena.allocate(sizeof(ValT));
		new (ptr) ValT {std::forward<Args>(args)...};
		return *(ValT*)ptr;
	}

private:
	std::pmr::monotonic_buffer_resource _arena;
	Env									_env;
};
}  // namespace luna::Eval