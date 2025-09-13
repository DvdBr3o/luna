#pragma once

#include "luna/IndexSpan.hpp"
#include "luna/String.hpp"
#include "luna/Variant.hpp"

#include <utf8/cpp20.h>

#include <optional>
#include <span>
#include <type_traits>
#include <variant>
#include <vector>
#include <string_view>

namespace luna::lex {
	using CodeSpan = std::span<char>;

	struct OwnLen {
		std::size_t len;
	};

	enum class Spacing : std::uint8_t {
		Alone,
		Joint,
	};

	struct Literal {};

	// enum class KeywordKind : std::uint32_t {
	// 	Local,	// local
	// 	Function,
	// 	// Logic
	// 	And,  // and
	// 	Or,	  // or
	// 	Not,  // not
	// 	// Loop
	// 	For,  // for
	// 	// In,
	// 	While,	// while
	// 	Goto,	// goto
	// 	Break,	// break
	// 	// Branch
	// 	If,		 // if
	// 	Elseif,	 // elseif
	// 	Else,	 // else
	// 	// Reserved Value
	// 	True,	// true
	// 	False,	// false
	// 	Nil,	// nil
	// 	/* Luna Specific */
	// 	Type,  // type
	// };

	// struct Keyword {
	// 	using Kind = KeywordKind;
	// };

	struct Identifier {
		// U8String value;
	};

	enum class OperatorKind : std::uint32_t {
		// Arithmetic
		Add,	   // +
		Minus,	   // -
				   // arithmetic minus
				   // unary minus
		Multiply,  // *
		Devide,	   // /
		Exponent,  // ^
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
		TribleDot,	// ...
		// String
		DoubleDot,	// ..
		// Other
		Comment,   // --
		LParen,	   // (
		RParen,	   // )
		LBracket,  // [
		RBracket,  // ]
		LBrace,	   // {
		RBrace,	   // }
	};

	struct Operator : public OwnLen {
		using Kind = OperatorKind;
	};

	struct Space {
		bool		indent = false;
		std::size_t value  = 0;
	};

	using TokenKind = std::variant<
		Literal,	 //
		Identifier,	 //
		Operator,	 //
		Space		 //
		>;

	struct Token {
		TokenKind token;
		IndexSpan span;

		using Kind = TokenKind;
	};

	class TokenStream : public std::vector<Token> {
	public:
		using vector::vector;

		template<typename... Args>
		explicit TokenStream(u8::StringView script, Args&&... args) :
			_script(script), vector(std::forward<Args>(args)...) {}

		friend auto& operator<<(std::ostream& os, const TokenStream& self) {
			for (const auto& tok : self)
				std::visit(
					overload {
						[&](const Literal& tokk) {
							os << std::format("Literal({})", self._script[tok.span]) << " ";
						},
						[&](const Identifier& tokk) {
							os << std::format("Identifier({})", self._script[tok.span]) << " ";
						},
						[&](const Operator& tokk) {
							os << std::format("Operator({})", self._script[tok.span]) << " ";
						},
						[&](const Space& tokk) {
							os << std::format("Space({})", self._script[tok.span]) << " ";
						},
					},
					tok.token
				);
			return os;
		}

	private:
		u8::StringView _script;
	};

	class Lexer {
	public:
		using Char = u8::StringView::Char;
		enum class Error {
			Eof = 0,
		};

	public:
		Lexer(u8::StringView script) : _script(script) {}

	public:
		auto lex() -> TokenStream;

	private:
		auto _next_token() -> std::optional<Token>;

		/* subpatterns */
		template<typename T>
		struct _is_tok_handler : public std::false_type {};

		template<>
		struct _is_tok_handler<std::optional<Token> (Lexer::*)()> : public std::true_type {};

		template<typename Handler0, typename... Handler>
			requires _is_tok_handler<Handler0>::value && ((_is_tok_handler<Handler>::value) && ...)
		auto _handle_tok(Handler0&& handler0, Handler&&... handler) -> std::optional<Token> {
			if (auto tok = (this->*std::forward<Handler0>(handler0))())
				return tok;
			else
				return _handle_tok(std::forward<Handler>(handler)...);
		}

		inline static auto _handle_tok() -> std::optional<Token> { return std::nullopt; }

		auto			   _tok_indent() -> std::optional<Token>;
		auto			   _tok_number_literal() -> std::optional<Token>;
		auto			   _tok_string_literal() -> std::optional<Token>;
		auto			   _tok_identifier() -> std::optional<Token>;

		/* utils */

		inline static auto _is_digit(Char c) -> bool { return U'0' <= c && c <= U'9'; }

		inline static auto _is_lowercase_alpha(Char c) -> bool { return U'a' <= c && c <= U'z'; }

		inline static auto _is_uppercase_alpha(Char c) -> bool { return U'A' <= c && c <= U'Z'; }

		inline static auto _is_alpha(Char c) -> bool {
			// Considering about performance and size, luna currently does not support unicode xid.
			return _is_lowercase_alpha(c) || _is_uppercase_alpha(c);
		}

		inline static auto _is_space(Char c) -> bool { return c == ' ' | c == '\t'; }

		inline static auto _is_identifier_start(Char c) -> bool {
			return _is_alpha(c) || c == U'_';
		}

		inline static auto _is_identifier_continue(Char c) -> bool {
			return _is_alpha(c) || _is_digit(c) || c == U'_';
		}

	private:
		u8::StringView _script;
		u8::Cursor	   _cursor = _script;
	};

	inline static auto tokenize(std::string_view script) -> TokenStream;

}  // namespace luna::lex

namespace luna::lex {
	inline auto Lexer::lex() -> TokenStream {
		TokenStream ts { _script };
		ts.reserve(_script.size() / 10);

		while (auto t = _next_token()) ts.emplace_back(*t);

		return ts;
	}

	inline auto Lexer::_next_token() -> std::optional<Token> {
		if (!_cursor.ended()) {
			return _handle_tok(
				&Lexer::_tok_indent,
				&Lexer::_tok_number_literal,
				&Lexer::_tok_identifier,
				&Lexer::_tok_string_literal
			);
		} else
			return std::nullopt;
	}

	inline auto Lexer::_tok_indent() -> std::optional<Token> {
		Space indent;

		if (_cursor.first() == '\n')
			indent.indent = true;
		else if (_is_space(_cursor.first()))
			indent.indent = false;
		else
			return std::nullopt;

		while (auto c = _cursor.bump())
			if (_is_space(c))
				++indent.value;
			else
				break;

		return Token {
			indent,
			indent.value + static_cast<std::size_t>(indent.indent),	 // '\n' is in indent too
		};
	}

	inline auto Lexer::_tok_number_literal() -> std::optional<Token> {
		// should support:
		// 123412139142      	// integer
		// 1323.2313221      	// float
		// 1e3               	// e
		// 10_000_000			// separator
		// 0x1ABBFF				// hex
		// 0b100101				// bin
		return std::nullopt;
	}

	inline auto Lexer::_tok_string_literal() -> std::optional<Token> {
		// should support:
		// 'hello'					// single quote
		// "world"					// double quote
		// [[hello world]]			// bracket quote
		// [[hello					// multiline quote
		// [[second line world]]
		// r"C:\User\DvdBr3o"		// raw string
		// f"hello, {a}"			// format string
		// "\n" "\t" ...			// common escape
		// "\u00A9"					// unicode escape
		// "\U0001F600"				// utf32 escape
		return std::nullopt;
	}

	inline auto Lexer::_tok_identifier() -> std::optional<Token> {
		if (!_is_identifier_start(_cursor.first()))
			return std::nullopt;

		auto		beg = _cursor;
		auto		end = beg;
		std::size_t len = 0;

		while (auto c = _cursor.bump())
			if (_is_identifier_continue(c))
				++len;
			else
				break;

		return Token {
			.token = {},
			.span  = { static_cast<size_t>(beg - _script.begin()), len },
		};
	}

	inline static auto tokenize(u8::StringView script) -> TokenStream {
		return Lexer { script }.lex();
	}
}  // namespace luna::lex
