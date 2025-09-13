#pragma once

#include "luna/String.hpp"
#include "luna/Variant.hpp"

#include <array>
#include <mapbox/eternal.hpp>

#include <optional>
#include <string_view>
#include <vector>
#include <variant>

namespace luna::lex {
	struct NumberLiteral {};

	struct StringLiteral {};

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
		// Function
		Exclaimation,  // !
		Dollar,		   // $
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
		{  "!",	   Operator::Exclaimation },
		{  "$",			   Operator::Dollar },
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
			{		  Operator::Exclaimation,  "!" },
			{			  Operator::Dollar,	"$" },
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

	struct Identifier {};

	struct Indent {
		std::size_t indent = 0;
	};

	struct Token {
		using TokenKind = std::variant<
			NumberLiteral,	//
			StringLiteral,	//
			Keyword,		//
			Operator,		//
			Identifier,		//
			Indent			//
			>;

		TokenKind		   kind;
		u8::StringView	   span;
		bool			   joint = false;

		inline friend auto to_string(const Token& token) {
			return std::visit(
				overload {
					[&](const NumberLiteral& numlit) {
						return std::format("NUMLIT({})", token.span);
					},
					[&](const StringLiteral& strlit) {
						return std::format("STRLIT({})", token.span);
					},
					[&](const Keyword& kw) { return std::format("KEYWORD({})", token.span); },
					[&](const Operator& op) { return std::format("OPERATOR({})", token.span); },
					[&](const Identifier& id) { return std::format("IDENTIFIER({})", token.span); },
					[&](const Indent& indent) { return std::format("INDENT({})", indent.indent); },
				},
				token.kind
			);
		}
	};

	class TokenStream : public std::vector<Token> {
	public:
		using vector::vector;

		template<typename... Args>
		explicit TokenStream(u8::String&& script, Args&&... args) :
			_script(std::move(script)), vector(std::forward<Args>(args)...) {}

		inline friend auto& operator<<(std::ostream& os, const TokenStream& ts) {
			for (const auto& tok : ts)
				if (!std::holds_alternative<Indent>(tok.kind))
					os << to_string(tok) << ' ' << (tok.joint ? "JOINT" : "") << '\n';
				else
					os << std::format("INDENT({})\n", std::get<Indent>(tok.kind).indent);
			return os;
		}

		[[nodiscard]] auto script() const -> u8::StringView { return _script.view(); }

	private:
		u8::String _script;
	};

	struct TokResult {
		Token		   token;
		u8::StringView rest_script;
	};

	template<typename T>
	struct _is_tok_handler : public std::false_type {};

	template<>
	struct _is_tok_handler<std::optional<TokResult> (&)(u8::StringView)> : public std::true_type {};

	inline static auto handle_tok(u8::StringView& script) -> std::optional<TokResult> {
		return std::nullopt;
	}

	template<typename Handler0, typename... Handler>
		requires _is_tok_handler<Handler0>::value && ((_is_tok_handler<Handler>::value) && ...)
	auto handle_tok(u8::StringView script, Handler0&& handler0, Handler&&... handler)
		-> std::optional<TokResult> {
		if (auto tok = (std::forward<Handler0>(handler0))(script))
			return tok;
		else
			return handle_tok(script, std::forward<Handler>(handler)...);
	}

	/* utils */
	inline static auto is_digit(Char32 c) -> bool {
		return U'0' <= c && c <= U'9';
	}

	inline static auto is_lowercase_alpha(Char32 c) -> bool {
		return U'a' <= c && c <= U'z';
	}

	inline static auto is_uppercase_alpha(Char32 c) -> bool {
		return U'A' <= c && c <= U'Z';
	}

	inline static auto is_alpha(Char32 c) -> bool {
		// Considering about performance and size, luna currently does not support unicode xid.
		return is_lowercase_alpha(c) || is_uppercase_alpha(c);
	}

	inline static auto is_space(Char32 c) -> bool {
		return c == ' ' | c == '\t';
	}

	inline static auto is_identifier_start(Char32 c) -> bool {
		return is_alpha(c) || c == U'_';
	}

	inline static auto is_identifier_continue(Char32 c) -> bool {
		return is_alpha(c) || is_digit(c) || c == U'_';
	}

	inline static auto clean_spaces(u8::StringView script) -> u8::StringView {
		auto it = script.iter_first();
		while (it != script.end() && *it != '\n' && is_space(*it)) ++it;
		return { it, script.end() };
	}

	inline static auto is_joint(u8::StringView script) -> bool {
		if (script.empty())
			return false;
		else
			return !is_space(script[0]);
	}

	inline static auto lex_num_literal_bin(u8::StringView script) -> u8::StringView {
		u8::Cursor	cursor = script;
		std::size_t len	   = 0;
		while (const auto c = cursor.bump())
			if (c == '_' || c == '1' || c == '0')
				++len;
			else
				break;
		return script.substr(0, len);
	}

	using PartialTokPos = std::size_t;

	struct PartialTokRes {
		u8::StringView tok;
		u8::StringView rst;
	};

	inline static auto partial_tok(u8::StringView sv, PartialTokPos pos) -> PartialTokRes {
		return { sv.substr(0, pos), sv.substr(pos) };
	}

	inline static auto is_hex_digit(Char32 c) -> bool {
		return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
	}

	inline static auto lex_hex_numlit(u8::StringView script) -> std::optional<PartialTokPos> {
		u8::Cursor	cursor	  = script;
		std::size_t pos		  = 0;
		bool		decimaled = false;

		while (const auto c = cursor.bump())
			if (is_hex_digit(c))
				++pos;
			else if (!decimaled && c == '.')
				++pos, decimaled = true;
			else
				break;

		return pos;
	}

	inline static auto lex_bin_numlit(u8::StringView script) -> std::optional<PartialTokPos> {
		u8::Cursor	cursor = script;
		std::size_t pos	   = 0;

		while (const auto c = cursor.bump())
			if (c == '0' || c == '1')
				++pos;
			else
				break;

		return pos;
	}

	inline static auto lex_dec_integer(u8::StringView script) -> std::optional<PartialTokPos> {
		u8::Cursor	cursor = script;
		std::size_t pos	   = 0;

		if (const auto sign = cursor.bump())
			if (sign == '+' || sign == '-' || is_digit(sign)) {
				++pos;
				while (const auto c = cursor.bump())
					if (is_digit(c))
						++pos;
					else
						break;
				return pos;
			}

		return std::nullopt;
	}

	inline static auto lex_dec_numlit(u8::StringView script) -> std::optional<PartialTokPos> {
		u8::Cursor	cursor	  = script;
		std::size_t pos		  = 0;
		bool		decimaled = false;
		bool		exponeted = false;	// e.g. 1e-3

		while (const auto c = cursor.bump())
			if (is_digit(c) || c == '_')
				++pos;
			else if (!decimaled && c == '.')
				++pos, decimaled = true;
			else if (!exponeted && (c == 'e' || c == 'E')) {
				if (const auto par = lex_dec_integer(script.substr(pos + 1)))
					return pos + 1 + *par;
			} else
				break;

		return pos;
	}

	inline static auto lex_unsigned_num_literal(u8::StringView script)
		-> std::optional<PartialTokPos> {
		u8::Cursor cursor = script;
		if (const auto num0 = cursor.bump()) {
			if (num0 == '0') {	// non 10-base num literal
				if (const auto numbase = cursor.bump())
					switch (numbase) {
						case 'b':				  /* BIN */
							if (const auto pos = lex_bin_numlit(script.substr(2)))
								return *pos + 2;  // 2 for `0b`
							else
								return std::nullopt;

						case 'x':				  /* HEX */
							if (const auto pos = lex_hex_numlit(script.substr(2)))
								return *pos + 2;  // 2 for `0x`
							else
								return std::nullopt;

						default: /* DEC */	// TODO: Whether support oct num literal?
							if (const auto pos = lex_dec_numlit(script))
								return *pos;
					}
				else					  // it is literally `0`
					return 1;
			} else if (is_digit(num0)) {  // normal decimal literal
				if (const auto pos = lex_dec_numlit(script))
					return *pos;
			}
		}
		return std::nullopt;
	}

	inline static auto lex_num_literal(u8::StringView script) -> std::optional<TokResult> {
		// should support:
		// 123412139142      	// integer
		// 1323.2313221      	// float
		// 1e3               	// e
		// 10_000_000			// separator
		// 0x1ABBFF				// hex
		// 0b100101				// bin

		u8::Cursor cursor = script;
		if (const auto sign = cursor.bump()) {
			if (sign == '+' || sign == '-') {
				if (const auto pos = lex_unsigned_num_literal(script.substr(1))) {
					const auto [tok, rst] = partial_tok(script, *pos + 1);
					return TokResult {
						.token = {
							.kind = NumberLiteral {},
							.span = tok,
							.joint = is_joint(rst),
						},
						.rest_script = rst,
					};
				}
			} else if (const auto pos = lex_unsigned_num_literal(script)) {
				const auto [tok, rst] = partial_tok(script, *pos);
				return TokResult {
					.token = {
						.kind = NumberLiteral {},
						.span = tok,
						.joint = is_joint(rst),
					},
					.rest_script = rst,
				};
			}
		}

		return std::nullopt;
	}

	inline static auto lex_str_literal(u8::StringView script) -> std::optional<TokResult> {
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

		u8::Cursor	cursor = script;
		std::size_t pos	   = 0;

		if (const auto lbr = cursor.bump()) {
			if (lbr == U'\'') {	 // '...'
				pos = 1;
				while (const auto c = cursor.bump())
					if (c != '\'')
						++pos;
					else if (c == '\\') {  // escape
						cursor.bump();
						pos += 2;
					} else {
						++pos;
						const auto [tok, rst] = partial_tok(script, pos);
						return TokResult {
							.token = {
								.kind = StringLiteral{},
								.span = tok,
								.joint = is_joint(rst),
							},
							.rest_script = rst,
						};
					}
			} else if (lbr == U'\"') {	// "..."
				pos = 1;
				while (const auto c = cursor.bump())
					if (c == U'\\') {  // escape
						cursor.bump();
						pos += 2;
					} else if (c == U'\"') {
						++pos;
						const auto [tok, rst] = partial_tok(script, pos);
						return TokResult {
							.token = {
								.kind = StringLiteral{},
								.span = tok,
								.joint = is_joint(rst),
							},
							.rest_script = rst,
						};
					} else
						++pos;
			} else if (lbr == '[') {  // [[...]]
				if (const auto lbrr = cursor.bump(); lbrr == '[') {
					pos = 2;
					while (const auto c = cursor.bump()) {
						if (c != ']')
							++pos;
						else {	// c == ']'
							pos += 2;
							const auto [tok, rst] = partial_tok(script, pos);
							return TokResult {
									.token = {
										.kind = StringLiteral{},
										.span = tok,
										.joint = is_joint(rst),
									},
									.rest_script = rst,
								};
						}
					}
				}
			}
		}

		return std::nullopt;
	}

	inline static auto lex_operator(u8::StringView script) -> std::optional<TokResult> {
		static constexpr auto MAX_OP_LEN = 2;
		for (auto i = MAX_OP_LEN; i > 0; --i) {
			if (script.size() >= i) {
				auto ops = script.substr(0, i);
				if (auto op = operator_map.find(reinterpret_cast<const std::string_view&>(ops));
					op != operator_map.end()) {
					return TokResult {
						.token = {
							.kind = op->second,
							.span = ops,
							.joint = is_joint(script.substr(i)),
						},
						.rest_script = clean_spaces(script.substr(i)),
					};
				}
			}
		}
		return std::nullopt;
	}

	inline static auto lex_identifier(u8::StringView script) -> std::optional<TokResult> {
		if (is_identifier_start(script[0])) {
			auto		it = script.iter_first(0);
			std::size_t sz = 0;

			// find identifier span
			while (is_identifier_continue(*it)) {
				++it;
				++sz;
				if (it == script.end())
					break;
			}

			auto span = script.substr(0, sz);
			if (auto kw = keyword_map.find(reinterpret_cast<const std::string_view&>(span));
				kw != keyword_map.end())
				return TokResult {
				.token = {
					.kind = kw->second,
					.span = span,
					.joint = is_joint(u8::StringView { it, script.end() }),
				},
				.rest_script = clean_spaces(u8::StringView { it, script.end() }),
				};
			else
				return TokResult {
				.token = {
					.kind = Identifier {},
					.span = span,
					.joint = is_joint(u8::StringView { it, script.end() }),
				},
				.rest_script = clean_spaces(u8::StringView { it, script.end() }),
				};

		} else
			return std::nullopt;
	}

	inline static auto lex_indent(u8::StringView script) -> std::optional<TokResult> {
		if (script[0] != '\n')
			return std::nullopt;

		std::size_t indent = 0;
		auto		it	   = script.iter_first(1);
		while (it != script.end() && is_space(*it)) ++indent, ++it;

		auto rest = u8::StringView { it, script.end() };

		return TokResult {
			.token = { 
				.kind  = Indent { indent },
				.span  = u8::StringView { script.begin(), it },
				.joint = is_joint(rest), 
			},
			.rest_script = rest,
		};
	}
}  // namespace luna::lex

namespace luna {
	inline static auto tokenize(u8::String&& script) -> lex::TokenStream {
		lex::TokenStream ts { std::move(script) };

		auto			 sv = ts.script();

		while (							 //
			auto res = lex::handle_tok(	 //
				sv,
				lex::lex_num_literal,
				lex::lex_str_literal,
				lex::lex_operator,
				lex::lex_identifier,
				lex::lex_indent
			)
		) {
			ts.emplace_back(res->token);
			sv = res->rest_script;
			if (sv.empty())
				break;
		}

		if (!sv.empty())
			std::cout << "[ERROR] Encountered lex error!\n";

		return ts;
	}
}  // namespace luna