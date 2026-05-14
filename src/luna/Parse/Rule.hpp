#pragma once

#include "luna/Parse/Ast.hpp"
#include "luna/Parse/Parser.hpp"

#include "pars.hpp"

namespace luna {
using pars::c;
using pars::cnot;
using pars::cran;
using pars::cset;
using pars::cstr;
using pars::DynamicRule;
using pars::fix;
using pars::value_to;
using pars::with_effect;

extern const DynamicRule<AstNode> expr;

// Format
constexpr auto packed_of(char32_t lpack, char32_t rpack) {
	return [lpack, rpack]<typename RuleT>(RuleT&& rule) constexpr {
		return (c(lpack) >> std::forward<RuleT>(rule) >> c(rpack))
			 % value_to([](auto&&, auto&& v, auto&&) { return std::forward<decltype(v)>(v); });
	};
}

constexpr auto parenthesised = packed_of('(', ')');
constexpr auto bracketed	 = packed_of('[', ']');
constexpr auto braced		 = packed_of('{', '}');

constexpr auto sp			 = cset(' ', '\t');

constexpr auto indent		 = with_effect<QueryIndentState>([](auto&& st) {

});

// Value Identifier
constexpr auto val_ident_start = cran('a', 'z') | cran('A', 'Z') | c('_');
constexpr auto val_ident_cont  = val_ident_start | cran('0', '9');
constexpr auto val_ident	   =  //
	(val_ident_start >> *val_ident_cont) % value_to([](auto&& start, auto&& cont) -> ValIdent {
		ValIdent ident;
		ident.ident.reserve(1 + cont.size());
		utf8::append(start, std::back_inserter(ident.ident));
		utf8::utf32to8(cont.begin(), cont.end(), std::back_inserter(ident.ident));
		return ident;
	});

// Operator Identifier
// TODO: performance suboptimal, consider using PEG match priority to avoid this.
constexpr auto op_ident_reserved = cstr(U"=>") | cstr(U"->");
constexpr auto op_ident_start	 = cset('+', '-', '*', '/', '^', '%', '=', '!', '&', '|', '?', '~');
constexpr auto op_ident_cont	 = op_ident_start;
constexpr auto op_ident			 =	//
	(!op_ident_reserved >> op_ident_start >> *op_ident_cont)
	% value_to([](auto&&, auto&& start, auto&& cont) -> OpIdent {
		  OpIdent ident;
		  ident.ident.reserve(1 + cont.size());
		  utf8::append(start, std::back_inserter(ident.ident));
		  utf8::utf32to8(cont.begin(), cont.end(), std::back_inserter(ident.ident));
		  return ident;
	  });

constexpr auto ident =
	(val_ident | op_ident) % value_to([](auto&& ident) -> Ident { return {ident}; });

// Number Literal
constexpr auto numlit = +cran('0', '9') % value_to([](auto&& digits) -> NumLit {
	NumLit lit = {0};
	for (const auto digit : digits) {
		lit.lit *= 10;
		lit.lit += digit - '0';
	}
	return lit;
});

// String Literal
constexpr auto strlit_escape =	//
	(c('\\') >> (c('\'') | c('\"') | c('\\') | c('t') | c('n')))
	% value_to([](auto, auto esc) -> char32_t {
		  switch (esc) {
			  case '\'': return '\'';
			  case '\"': return '\"';
			  case '\\': return '\\';
			  case 't': return '\t';
			  case 'n': return '\n';
			  default: break;
		  }
		  return U'\0';
	  });

constexpr auto strlit_chars_to_u8(auto&& cs) {
	std::u8string strlit;
	strlit.reserve(cs.size());
	utf8::utf32to8(cs.begin(), cs.end(), std::back_inserter(strlit));
	return strlit;
};

constexpr auto single_quote_strlit =  //
	(c('\'') >> *(strlit_escape | cnot('\n', '\'')) >> c('\''))
	% value_to([](auto, auto&& cs, auto) { return strlit_chars_to_u8(cs); });

constexpr auto double_quote_strlit =  //
	(c('\"') >> *(strlit_escape | cnot('\n', '\"')) >> c('\"'))
	% value_to([](auto, auto&& cs, auto) { return strlit_chars_to_u8(cs); });

constexpr auto long_bracket_strlit_char =
	cnot(']') | ((c(']') >> !c(']')) % value_to([](auto ch, auto) -> char32_t { return ch; }));

constexpr auto long_bracket_strlit =  //
	(cstr(U"[[") >> *long_bracket_strlit_char >> cstr(U"]]"))
	% value_to([](auto&&, auto&& cs, auto&&) { return strlit_chars_to_u8(cs); });

constexpr auto strlit = (single_quote_strlit | double_quote_strlit | long_bracket_strlit)
					  % value_to([](auto&& s) -> StrLit { return std::forward<decltype(s)>(s); });

// Call Syntax
constexpr auto val_callable =
	fix<std::variant<ValIdent, NumLit, StrLit, AstNode>>([](auto&& callable) {
		return val_ident | numlit | strlit | parenthesised(expr);
	});
constexpr auto op_callable	 = op_ident;
constexpr auto atom_fn_call	 = val_callable >> parenthesised(expr);
constexpr auto curry_fn_call = 0;

// Expression
const DynamicRule<AstNode> expr = dyna(ident % value_to([](auto&&) { return AstNode(); }));
}  // namespace luna