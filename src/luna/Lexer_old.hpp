#pragma once

#include "luna/Variant.hpp"
#include "luna/SourceLocation.hpp"
#include "luna/Input.hpp"

#include <ostream>
#include <tl/expected.hpp>
#include <mapbox/eternal.hpp>

#include <format>
#include <string_view>
#include <vector>
#include <span>
#include <variant>
#include <iostream>

namespace luna {
	struct LexError {
		enum class Type {
			StringQuoteNotClosed,
		} type;

		static constexpr auto to_what(Type type) -> CodeView;

		CodeView			  what = to_what(type);
	};

	template<typename T>
	using LexResult = tl::expected<T, LexError>;

	using Indent	= std::uint32_t;

	enum class Keyword : std::uint32_t {
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
	inline static constexpr auto to_string_view(Keyword keyword) -> CodeView;

	enum class Operator : std::uint32_t {
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

	inline static auto to_symbol(Operator op) -> std::string {
		switch (op) {
			case Operator::Add: return "+";
			case Operator::Minus: return "-";
			case Operator::Multiply: return "*";
			case Operator::Devide: return "/";
			case Operator::Exponent: return "^";
			case Operator::BitwiseAnd: return "&";
			case Operator::BitwiseOr: return "|";
			case Operator::BitwiseExclusiveOr: return "~";
			case Operator::Equal: return "==";
			case Operator::NotEqual: return "~=";
			case Operator::LessThan: return "<";
			case Operator::GreaterThan: return ">";
			case Operator::LessEqual: return "<=";
			case Operator::GreaterEqual: return ">=";
			case Operator::Sharp: return "#";
			case Operator::Colon: return ":";
			case Operator::Comma: return ",";
			case Operator::Dot: return ".";
			case Operator::AntiSlash: return "`";
			case Operator::Concat: return "..";
			case Operator::Comment: return "--";
			case Operator::LeftParenthesis: return "(";
			case Operator::RightParenthesis: return ")";
			case Operator::LeftBracket: return "[";
			case Operator::RightBracket: return "]";
			case Operator::LeftBrace: return "{";
			case Operator::RightBrace: return "}";
		}
	}

	inline static auto to_string_view(Operator op) -> std::string {
		return to_symbol(op);
	}

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

	struct Identifier : public CodeView {
		using CodeView::CodeView;

		explicit Identifier(CodeView literal) : CodeView(literal) {}
	};

	struct Literal : public CodeView {
		using CodeView::CodeView;

		explicit Literal(CodeView literal) : CodeView(literal) {}
	};

	struct Token : public std::variant<Indent, Keyword, Operator, Identifier, Literal> {
		using variant::variant;

		friend auto& operator<<(std::ostream& os, const Token& token) {
			std::cout << "what?\n";
			std::visit(
				overload {
					[&os](const Indent& tok) { os << std::format("Indent({})", tok); },
					[&os](const Keyword& tok) {
						os << std::format("Keyword({})", to_string_view(tok));
					},
					[&os](const Operator& tok) {
						os << std::format("Operator({})", to_string_view(tok));
					},
					[&os](const Identifier& tok) {
						os << std::format("Identifier({})", static_cast<std::string_view>(tok));
					},
					[&os](const Literal& tok) {
						os << std::format("Literal({})", static_cast<std::string_view>(tok));
					},
				},
				token
			);
			return os;
		}

		friend inline auto operator==(const Token& lhs, const Token& rhs) -> bool {
			return lhs.index() == rhs.index() && std::visit(variant_equal, lhs, rhs);
		}

		friend inline auto to_string(const Token& token) -> std::string {
			std::string str;

			std::visit(
				overload {
					[](const Indent& indent) { std::cout << std::format("\nIndent({})", indent); },
					[](const Keyword& keyword) {
						std::cout << std::format("Keyword({})", to_string_view(keyword));
					},
					[](const Operator& op) {
						std::cout << std::format("Operator({})", to_symbol(op));
					},
					[](const Identifier& id) {
						std::cout << std::format("Identifier({})", std::string(id));
					},
					[](const Literal& listeral) {
						std::cout << std::format("Literal({})", std::string(listeral));
					},
				},
				token
			);

			return str;
		}
	};

	struct DebuggableToken : public Token {
		SourceLocationScope location;
	};

	class TokenStream : public std::vector<Token> {
	public:
		using vector::iterator;
		using vector::vector;

	public:
		friend constexpr auto operator==(const TokenStream& lhs, const TokenStream& rhs) -> bool {
			if (lhs.size() != rhs.size())
				return false;
			for (std::size_t i = 0; i < lhs.size(); ++i)
				if (lhs[i] != rhs[i])
					return false;
			return true;
		}
	};

	using TokenStreamView = std::span<Token>;

	constexpr auto LexError::to_what(Type type) -> CodeView {
		switch (type) {
			case LexError::Type::StringQuoteNotClosed:
				return "String quote `\"`/`\'` is not closed.";
		}
	}

	namespace details::lex {
		auto lex_indent(TokenStream& ts, CodeView code) -> LexResult<CodeView> {
			std::uint32_t depth = 0;
			auto		  it	= code.begin() + 1;
			while (*it == '\t') ++depth, ++it;
			ts.emplace_back(Indent { depth });
			return code.substr(depth);
		}

		template<char quote>
		auto lex_string_literal(TokenStream& ts, CodeView code) -> LexResult<CodeView> {
			std::size_t len = 0;
			for (auto it = code.begin() + 1; it != code.end(); ++it, ++len)
				if (*it == quote) {
					ts.emplace_back(Literal { code.substr(1, len) });
					return code.substr(len + 1);
				}

			return tl::make_unexpected<LexError>({ LexError::Type::StringQuoteNotClosed });
		}

		inline static auto lex_number_literal(TokenStream& ts, CodeView code)
			-> LexResult<CodeView> {
			std::size_t len = 0;
			for (auto it = code.begin(); it != code.end(); ++it, ++len)
				if (!('0' <= *it && *it <= '9')) {
					ts.emplace_back(Literal {});
					return code.substr(len);
				}

			return {};
		}

		inline static auto lex_space_separator(TokenStream& ts, CodeView code)
			-> LexResult<CodeView> {
			auto i = 0;
			while ((code[i] == ' ' || code[i] == '\t') && i < code.size()) ++i;
			// ts.push_back(SpaceSeparator {});
			return code.substr(i);
		}

		inline static auto lex_multiline_comment(TokenStream& ts, CodeView code)
			-> LexResult<CodeView> {
			return {};
		}

		inline static auto lex_comment(TokenStream& ts, CodeView code) -> LexResult<CodeView> {
			auto it = code.begin();
			while (it++ != code.end())	//
				switch (*it) {
					case '\n': return CodeView { it, code.end() };
					case '[':
						if (*(it + 1) == '[')
							return lex_multiline_comment(ts, CodeView { it + 2, code.end() });
					default: break;
				}

			return CodeView { it, code.end() };
		}

		inline static auto lex_operator(TokenStream& ts, CodeView code) -> LexResult<CodeView> {
			// comment special judge
			using std::operator""sv;
			if (code.substr(0, 2) == "--"sv)
				return lex_comment(ts, code.substr(2));
		}

		inline static auto lex_identifier(TokenStream& ts, CodeView code) -> LexResult<CodeView> {
			auto it = code.begin();
			while (it != code.end() && *it != ' ' && *it != '\t'
				   // TODO: && is not operator char
			)
				++it;

			const auto id = std::string_view { code.begin(), it };
			if (keyword_map.contains(id))
				ts.emplace_back(keyword_map.at(id));
			else
				ts.emplace_back(Identifier { id });

			return code.substr(id.size());
		}

		inline static auto lex(TokenStream& ts, CodeView code) -> LexResult<void> {
			// clang-format off
			#define LUNA_HANDLE_LEX(lex_method)                                                                \
				if (const auto res = lex_method(ts, code.substr(1)))                                           \
					code = *res;                                                                               \
				else                                                                                           \
					return tl::make_unexpected(res.error())
			// clang-format on

			while (code.begin() != code.end()) {
				std::cout << code;
				switch (*code.begin()) {
					// Indent
					case '\n': LUNA_HANDLE_LEX(lex_indent); break;
					// String Literal
					case '\"': LUNA_HANDLE_LEX(lex_string_literal<'\"'>); break;
					case '\'': LUNA_HANDLE_LEX(lex_string_literal<'\''>); break;
					// Numer Literal
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9': LUNA_HANDLE_LEX(lex_number_literal); break;
					// Space between
					case ' ':
					case '\t': LUNA_HANDLE_LEX(lex_space_separator); break;
					// Identifier/Keyword/Operator
					default:
						if (const auto res = lex_operator(ts, code))
							code = *res;
						else if (const auto res = lex_identifier(ts, code))
							code = *res;
						else
							;
						break;
				}
			}
			return {};
		}

		inline static auto lex(CodeView code) -> LexResult<TokenStream> {
			TokenStream ts;
			if (auto res = lex(ts, code); !res)
				return tl::make_unexpected(res.error());
			else
				return std::move(ts);
		}

		inline static auto lex_no_expected(CodeView code) -> TokenStream {
			TokenStream ts;
			lex(ts, code);
			return ts;
		}
	}  // namespace details::lex

	using details::lex::lex;

	namespace details::lexer {
	}
}  // namespace luna

namespace luna {
	inline static constexpr auto to_string_view(Keyword keyword) -> CodeView {
		switch (keyword) {
			case Keyword::Local: return "local";
			case Keyword::Function: return "function";
			// case Keyword::End: return "end";
			// case Keyword::Is: return L"";
			case Keyword::And: return "and";
			case Keyword::Or: return "or";
			case Keyword::Not: return "not";
			case Keyword::For: return "for";
			// case Keyword::In: return "in";
			case Keyword::Type: return "type";
			case Keyword::While: return "while";
			case Keyword::Goto: return "goto";
			case Keyword::Break: return "break";
			case Keyword::If: return "if";
			case Keyword::Elseif: return "elseif";
			case Keyword::Else: return "else";
			case Keyword::True: return "true";
			case Keyword::False: return "false";
			case Keyword::Nil: return "nil";
		}
	}
}  // namespace luna