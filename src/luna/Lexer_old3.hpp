#pragma once

#include "luna/String.hpp"
#include "luna/Variant.hpp"

#include <mapbox/eternal.hpp>

#include <format>
#include <string_view>
#include <variant>

namespace luna::lex {
	struct NumberLiteral {
		double val;
	};

	struct StringLiteral {
		std::string val;
	};

	struct Identifier {
		std::string_view id;
	};

	enum class Keyword : std::uint8_t {
		Local,	// local
		Function,
		// Logic
		And,  // and
		Or,	  // or
		Not,  // not
		// Loop
		For,  // for
		// In,
		While,	// while
		Goto,	// goto
		Break,	// break
		// Branch
		If,		 // if
		Elseif,	 // elseif
		Else,	 // else
		// Reserved Value
		True,	// true
		False,	// false
		Nil,	// nil
		/* Luna Specific */
		Type,  // type
	};

	inline static constexpr auto keyword_map = mapbox::eternal::map<std::string_view, Keyword>({
		{  "local",  Keyword::Local },
		{	  "and",	 Keyword::And },
		{	  "or",		Keyword::Or },
		{	  "not",	 Keyword::Not },
		{	  "for",	 Keyword::For },
		{  "while",  Keyword::While },
		{	  "goto",	  Keyword::Goto },
		{  "break",  Keyword::Break },
		{	  "if",		Keyword::If },
		{ "elseif", Keyword::Elseif },
		{	  "else",	  Keyword::Else },
		{	  "true",	  Keyword::True },
		{  "false",  Keyword::False },
		{	  "nil",	 Keyword::Nil },
		{	  "type",	  Keyword::Type },
	});
	inline static constexpr auto keyword_to_string =
		mapbox::eternal::map<Keyword, std::string_view>({
			{  Keyword::Local,  "local" },
			{	  Keyword::And,	"and" },
			{	  Keyword::Or,	   "or" },
			{	  Keyword::Not,	"not" },
			{	  Keyword::For,	"for" },
			{  Keyword::While,  "while" },
			{	  Keyword::Goto,	 "goto" },
			{  Keyword::Break,  "break" },
			{	  Keyword::If,	   "if" },
			{ Keyword::Elseif, "elseif" },
			{	  Keyword::Else,	 "else" },
			{	  Keyword::True,	 "true" },
			{  Keyword::False,  "false" },
			{	  Keyword::Nil,	"nil" },
			{	  Keyword::Type,	 "type" },
	});

	inline static auto to_string(Keyword kw) -> std::string {
		return std::string { keyword_to_string.at(kw) };
	}

	enum class Operator : std::uint8_t {
		// Arithmetic
		Add,	   // +
		Minus,	   // -
				   // arithmetic minus
				   // unary minus
		Multiply,  // *
		Devide,	   // /
		Exponent,  // ^
		Assign,	   // =
		// Bitwise
		BitwiseAnd,			 // &
		BitwiseOr,			 // |
		BitwiseExclusiveOr,	 // ~
		// Logic
		Equal,		   // ==
		NotEqual,	   // ~=
		LessThan,	   // <
		GreaterThan,   // >
		LessEqual,	   // <=
		GreaterEqual,  // >=
		// Table
		Sharp,		// #
		Colon,		// :
		Comma,		// ,
		Dot,		// .
		AntiSlash,	// `\`
		// String
		Concat,	 // ..
		// Other
		Comment,		   // --
		LeftParenthesis,   // (
		RightParenthesis,  // )
		LeftBracket,	   // [
		RightBracket,	   // ]
		LeftBrace,		   // {
		RightBrace,		   // }
	};

	inline static constexpr auto operator_map = mapbox::eternal::map<std::string_view, Operator>({
		{  "+",				Operator::Add },
		{  "-",			   Operator::Minus },
		{  "*",		   Operator::Multiply },
		{  "/",			   Operator::Devide },
		{  "^",		   Operator::Exponent },
		{  "=",			   Operator::Assign },
		{  "&",		   Operator::BitwiseAnd },
		{  "|",		   Operator::BitwiseOr },
		{  "~", Operator::BitwiseExclusiveOr },
		{ "==",				Operator::Equal },
		{ "~=",			Operator::NotEqual },
		{  "<",		   Operator::LessThan },
		{  ">",		   Operator::GreaterThan },
		{ "<=",			Operator::LessEqual },
		{ ">=",		Operator::GreaterEqual },
		{  "#",			   Operator::Sharp },
		{  ":",			   Operator::Colon },
		{  ",",			   Operator::Comma },
		{  ".",				Operator::Dot },
		{ "\\",			Operator::AntiSlash },
		{ "..",				Operator::Concat },
		{ "--",			Operator::Comment },
		{  "(",	   Operator::LeftParenthesis },
		{  ")",   Operator::RightParenthesis },
		{  "[",		   Operator::LeftBracket },
		{  "]",	   Operator::RightBracket },
		{  "{",		   Operator::LeftBrace },
		{  "}",		   Operator::RightBrace },
	});
	inline static constexpr auto operator_to_string =
		mapbox::eternal::map<Operator, std::string_view>({
			{				Operator::Add,	 "+" },
			{			  Operator::Minus,  "-" },
			{			  Operator::Multiply,  "*" },
			{			  Operator::Devide,	"/" },
			{			  Operator::Exponent,  "^" },
			{			  Operator::Assign,	"=" },
			{		  Operator::BitwiseAnd,	"&" },
			{		  Operator::BitwiseOr,  "|" },
			{ Operator::BitwiseExclusiveOr,	"~" },
			{			  Operator::Equal, "==" },
			{			  Operator::NotEqual, "~=" },
			{			  Operator::LessThan,  "<" },
			{		  Operator::GreaterThan,	 ">" },
			{		  Operator::LessEqual, "<=" },
			{		  Operator::GreaterEqual, ">=" },
			{			  Operator::Sharp,  "#" },
			{			  Operator::Colon,  ":" },
			{			  Operator::Comma,  "," },
			{				Operator::Dot,	 "." },
			{		  Operator::AntiSlash, "\\" },
			{			  Operator::Concat, ".." },
			{			  Operator::Comment, "--" },
			{	  Operator::LeftParenthesis,	 "(" },
			{	  Operator::RightParenthesis,  ")" },
			{		  Operator::LeftBracket,	 "[" },
			{		  Operator::RightBracket,  "]" },
			{		  Operator::LeftBrace,  "{" },
			{		  Operator::RightBrace,	"}" },
	});

	auto to_string(Operator op) -> std::string {
		return std::string { operator_to_string.at(op) };
	}

	struct Indent {
		std::size_t indent = 0;
	};

	struct Token {
		using Kind = std::variant<
			NumberLiteral,	//
			StringLiteral,	//
			Identifier,		//
			Keyword,		//
			Operator,		//
			Indent			//
			>;

		enum Spacing {
			Joint,
			Separated,
		};

		Kind		   token;
		u8::StringView span;
		Spacing		   spacing;
	};

	inline static auto to_string(const Token::Kind& token) -> std::string {
		return std::visit(
			overload {
				[](const NumberLiteral& lit) -> std::string {
					return std::format("NUMBER_LIT({})", lit.val);
				},
				[](const StringLiteral& lit) -> std::string {
					return std::format("STRING_LIT({})", lit.val);
				},
				[](const Identifier& id) -> std::string {
					return std::format("IDENTIFIER({})", id.id);
				},
				[](const Keyword& kw) -> std::string {
					return std::format("KEYWORD({})", to_string(kw));
				},
				[](const Operator& op) -> std::string {
					return std::format("OPERATOR({})", to_string(op));
				},
				[](const Indent& idn) -> std::string {
					return std::format("INDENT({})", idn.indent);
				},
			},
			token
		);
	}

	class TokenStream : public std::vector<Token> {
	public:
		using vector::vector;

		inline friend auto& operator<<(std::ostream& os, const TokenStream& self) {
			for (const auto& token : self) os << to_string(token.token) + " ";
			return os;
		}

		explicit TokenStream(std::string&& script) : _script(script) {}

	private:
		std::string _script;
	};

	class Lexer {
	public:
	private:
	};

	inline static auto _is_space(Char32 c) -> bool {
		return c == ' ' | c == '\t';
	}

	inline static auto lex_indent(u8::StringView& script) -> std::optional<Token> {
		if (script[0] != U'\n')
			return std::nullopt;

		Indent indent;
		// TODO:
	}

	inline static auto lex_identifier(u8::StringView& script) -> std::optional<Token> {
		return Token { Identifier { "what?" } };
	}

	inline static auto lex_operator(u8::StringView& script) -> std::optional<Token> {
		return std::nullopt;
	}

	template<typename T>
	struct _is_tok_handler : public std::false_type {};

	template<>
	struct _is_tok_handler<std::optional<Token> (&)(u8::StringView&)> : public std::true_type {};

	inline static auto _handle_tok(u8::StringView& script) -> std::optional<Token> {
		return std::nullopt;
	}

	template<typename Handler0, typename... Handler>
		requires _is_tok_handler<Handler0>::value && ((_is_tok_handler<Handler>::value) && ...)
	auto _handle_tok(u8::StringView& script, Handler0&& handler0, Handler&&... handler)
		-> std::optional<Token> {
		if (auto tok = (std::forward<Handler0>(handler0))(script))
			return tok;
		else
			return _handle_tok(script, std::forward<Handler>(handler)...);
	}

	inline static auto next_token(u8::StringView& script) -> std::optional<Token> {
		return _handle_tok(
			script,
			lex_identifier,	 //
			lex_indent,		 //
			lex_operator	 //
		);
	}

	inline static auto tokenize(std::string&& script) -> TokenStream {
		TokenStream	   ts;
		u8::StringView s = reinterpret_cast<std::u8string_view&&>(script);

		while (auto tk = next_token(s)) ts.emplace_back(std::move(*tk));

		return ts;
	}

	inline static auto tokenize(const u8::String& script) -> TokenStream {
		auto script_cpy = script;
		return tokenize(static_cast<std::string&&>(script_cpy));
	}
}  // namespace luna::lex
