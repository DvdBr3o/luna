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
#include "pars/Rules/Utils.hpp"
#include "pars/Utf.hpp"

#include <utf8/cpp20.h>

#include <iterator>
#include <ranges>
#include <string>
#include <string_view>

namespace luna::Parse {
using namespace pars;

inline constexpr auto u32to8		  = [](std::u32string_view sv) { return utf8::utf32tou8(sv); };

inline constexpr auto val_ident_start = cran('a', 'z') | cran('A', 'Z');
static_assert(std::same_as<rule_value_t<LunaParserState, decltype(val_ident_start)>, char32_t>);
inline constexpr auto val_ident_cont = val_ident_start | cran('0', '9');
inline constexpr auto val_ident		 =	//
	val_ident_start >> *val_ident_cont	//
	^ value_apply([](auto start, auto&& cont) -> std::u32string {
		  std::u32string s {start};
		  s.append_range(cont | std::views::as_rvalue);
		  return s;
	  })
	^ value_to(u32to8);

inline constexpr auto op_ident =
	+cset('+', '-', '*', '/', '^', '@', '#', '!', '^', '&', '=', '<', '>')	//
	^ value_to([](auto&& cs) -> std::u32string {
		  std::u32string result;
		  result.reserve(cs.size());
		  result.append_range(std::forward<decltype(cs)>(cs));
		  return result;
	  })
	^ value_to(u32to8);

inline constexpr auto val_currying_apply = fix_v2::fix_expected<ast::Apply>([](auto&& expr) {
	const auto item = (val_ident | parenthesised(op_ident) | expr)	//
					^ value_visit([](auto&& v) -> ast::Apply::Item { return {v}; });

	return item >> *sp >> item	//
		 ^ value_apply([](auto&& applyer, auto&&, auto&& applyee) -> ast::Apply {
			   return {
				   .applyer = std::forward<decltype(applyer)>(applyer),
				   .applyee = std::forward<decltype(applyee)>(applyee),
			   };
		   });
});

inline constexpr auto op_apply			 = todo;

inline constexpr auto expr =
	fix<ast::Expr>::with_query<pars::u8::QueryTextCursor, QueryIndentState>([](auto&& expr) {
		return val_ident | op_ident;
	});
}  // namespace luna::Parse
