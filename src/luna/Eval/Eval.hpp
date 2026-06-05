#pragma once

#include "luna/Eval/Val.hpp"
#include "luna/Eval/Env.hpp"
#include "luna/Parse/Ast.hpp"
#include "luna/Utils/Arena.hpp"

namespace luna::Eval {
inline auto eval(const Parse::ast::ValIdent& val_ident, const Tbl& env) -> Val {
	return {};
}

inline auto eval(const Parse::ast::Lambda& lambda, const Tbl& env) -> Val {
	namespace ast = Parse::ast;

	ExpClo::Env			  env_exp;
	ScratchArenaAllocator scratch;

	*lambda.body
		| overload {
			[&](const ast::ValIdent& val_ident) {
				// TODO:
				// env_exp[val_ident.ident] = env.tbl.at(scratch.create<Val>(eval(val_ident, env)));
			},
			[](auto&& e) {},
		};

	// clang-format off
	return {Clo{ExpClo{
		.env = std::move(env_exp),
		.exp = *lambda.body,
	}}};
	// clang-format on
}

inline auto eval(const Parse::ast::FnCall& fncall, const Tbl& env) -> Val {
	namespace ast = Parse::ast;
}

}  // namespace luna::Eval
