#pragma once

#include "luna/Parse/Ast.hpp"
#include "luna/Eval/Val.hpp"

namespace luna::Eval {
inline constexpr auto lift(const CstNum& cstnum) -> Parse::ast::Expr {
	return {Parse::ast::NumLit {cstnum.num}};
}

inline constexpr auto lift(const CstStr& cststr) -> Parse::ast::Expr {
	return {Parse::ast::StrLit {cststr.str}};
}

inline auto lift(const Clo& clo) -> Parse::ast::Expr {
	return {Parse::ast::Lambda {
		// std::make_unique<Parse::ast::Expr>(clo.expr)
	}};
}
}  // namespace luna::Eval