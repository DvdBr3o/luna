#pragma once

#include "luna/Parse/Parser.hpp"
#include "luna/Parse/Ast.hpp"
#include "pars/Rules/Fix.hpp"
#include "pars/Utf.hpp"

namespace luna::Parse {
inline constexpr auto expr =
	pars::fix<ast::Expr>::of<pars::u8::QueryTextCursor, QueryIndentState>([](auto&& expr) {
		static constexpr auto val = c('a');
		return val | c('b') >> expr;
	});
}  // namespace luna::Parse