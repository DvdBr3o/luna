#pragma once

#include "luna/Eval/Val.hpp"
#include "luna/Eval/Env.hpp"
#include "luna/Parse/Ast.hpp"

namespace luna::Eval {
inline constexpr auto fn_apply(
	const Env& env, const Parse::ast::Lambda& lambda, const Parse::ast::ExprC auto& expr
) -> Val {
	return {};
}

inline constexpr auto fn_apply(
	const Env& env, const Parse::ast::Ident& ident, const Parse::ast::ExprC auto& expr
) -> Val {
	return {};
}

inline constexpr auto fn_apply(
	const Env& env, const Parse::ast::Table& table, const Parse::ast::ExprC auto& expr
) -> Val {
	return {};
}

template<typename CallerT, typename CalleeT>
concept FnApplyable = requires(Env env, CallerT caller, CalleeT callee) {
	{ fn_apply(env, caller, callee) } -> std::convertible_to<Val>;
};
}  // namespace luna::Eval
