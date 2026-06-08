#include "luna/Parse/Rule.hpp"
#include "pars/Meta.hpp"
#include "pars/Rules/Effect.hpp"
#include "pars/Rules/Char.hpp"
#include "pars/Rules/Choice.hpp"
#include "pars/Rules/Repeat.hpp"
#include "pars/Rules/Fix.hpp"
#include "pars/Rules/Utils.hpp"
#include "pars/Utf.hpp"

#include <catch2/catch_test_macros.hpp>
#include <fmt/core.h>

#include <variant>

namespace luna::tests::parse {
using namespace pars;
using namespace luna::Parse;

struct LunaParserState :
	u8::TextCursorState,  //
	pars::ArenaState<>	  //
{
	constexpr explicit LunaParserState(std::u8string_view sv) : u8::TextCursorState {sv} {}
};

inline constexpr auto match_luna(auto&& rule, std::u8string_view script) -> decltype(auto) {
	return rule.match(LunaParserState {script});
}

TEST_CASE("pars can work.", "[pars]") {
	using RecurResult = Expected<std::monostate, std::monostate>;
	static constexpr auto resursive_parenthesis =
		fix_v2::fix_expected<std::monostate>([](auto&& fx) constexpr {
			// return (cstr(U"()") | sequential(c('('), fx, c(')')))  //
			return (cstr(U"()") | c('(') >> fx >> c(')'))  //
				 ^ result_to([](auto&& res) -> RecurResult {
					   if (res)
						   return std::monostate {};
					   else
						   return tl::make_unexpected(std::monostate {});
				   });
		});
	REQUIRE(match_luna(resursive_parenthesis, u8"((()))"));
}

TEST_CASE("pars can parse embrace utils.", "[pars.rules.utils.embrace]") {
	static constexpr auto r = braced(*c('a'));

	REQUIRE(match_luna(r, u8"{aaaaa}"));
}

TEST_CASE("can parse identifier", "[luna.parse.ident]") {
	REQUIRE(value_of(match_luna(val_ident, u8"hello")) == u8"hello");
	REQUIRE(value_of(match_luna(val_ident, u8"hello123")) == u8"hello123");
	REQUIRE(value_of(match_luna(val_ident, u8"Hello123A")) == u8"Hello123A");

	REQUIRE(value_of(match_luna(op_ident, u8"+=")) == u8"+=");
	REQUIRE(value_of(match_luna(op_ident, u8"--")) == u8"--");
	REQUIRE(value_of(match_luna(op_ident, u8">>")) == u8">>");

	// REQUIRE(match_luna(val_currying_apply, u8"a b c"));
	// REQUIRE(match_luna(op_apply, u8"a += c"));
}

TEST_CASE("can parse member access grammer", "[luna.parse.access.member]") {
	// TODO:
}

}  // namespace luna::tests::parse