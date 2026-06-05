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

struct LunaParserState :
	u8::TextCursorState,
	pars::ArenaState<>

{
	constexpr explicit LunaParserState(std::u8string_view sv) : u8::TextCursorState {sv} {}
};

inline constexpr auto match_luna(auto&& rule, std::u8string_view script) -> decltype(auto) {
	return rule.match(LunaParserState {script});
}

TEST_CASE("pars can work.", "[pars]") {
	using RecurResult = Expected<std::monostate, std::monostate>;
	static constexpr auto resursive_parenthesis =
		fix<RecurResult>::of<u8::QueryTextCursor>([](auto&& fx) constexpr {
			return cstr(U"()") | c('(') >> fx >> c(')')	 //
				%= result_to([](auto&& res) -> RecurResult {
					   if (res)
						   return std::monostate {};
					   else
						   return tl::make_unexpected(std::monostate {});
				   });
		});
	REQUIRE(match_luna(resursive_parenthesis, u8"((()))"));
}

TEST_CASE("pars can parse embrace utils.", "[pars.rules.utils.embrace]") {
	static constexpr auto r = bracketed(*c('a'));

	REQUIRE(match_luna(r, u8"{aaaaa}"));
}

TEST_CASE("can parse member access grammer", "[luna.parse.access.member]") {
	//
}

}  // namespace luna::tests::parse