#pragma once

#include "luna/Parse/Parser.hpp"
#include "luna/Parse/Parser.hpp"
#include "luna/Parse/Ast.hpp"
#include "pars/Rule.hpp"
#include "pars/Rules/Fix.hpp"
#include "pars/Rules/Char.hpp"
#include "pars/Rules/Choice.hpp"
#include "pars/Rules/Sequential.hpp"
#include "pars/Rules/Repeat.hpp"
#include "pars/Utf.hpp"

#include <iterator>
#include <ranges>
#include <string>
#include <string_view>

namespace luna::Parse {
using namespace pars;

inline constexpr auto val_ident_start = cran('a', 'z') | cran('A', 'Z');
static_assert(std::same_as<rule_value_t<LunaParserState, decltype(val_ident_start)>, char32_t>);
inline constexpr auto val_ident_cont = val_ident_start | cran('0', '9');
inline constexpr auto val_ident		 = val_ident_start >> * val_ident_cont %=
	value_apply([](auto start, auto&& cont) -> std::u32string {
		std::u32string s {start};
		s.append_range(cont | std::views::as_rvalue);
		return s;
	});

inline constexpr auto op_ident =
	+cset('+', '-', '*', '/', '^', '@', '#', '!', '^', '&', '=', '<', '>');

inline constexpr auto expr =
	fix<ast::Expr>::of<pars::u8::QueryTextCursor, QueryIndentState>([](auto&& expr) {
		static constexpr auto val = c('a');
		return val | c('b') >> expr;
	});
}  // namespace luna::Parse