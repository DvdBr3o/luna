#pragma once

#include "luna/Source.hpp"
#include "pars/Query.hpp"
#include "pars/Utf.hpp"

#include <cstdint>
#include <stack>

namespace luna::Parse {
struct Indent {
	uint32_t indent;
};

struct IndentState : public std::stack<Indent> {
	IndentState() : std::stack<Indent> {{Indent {0}}} {}
};

struct QueryIndentState : pars::QueryTag<IndentState> {};

struct LunaParserState :
	pars::QueryState<pars::u8::QueryTextCursor>,
	pars::QueryState<QueryIndentState> {
	explicit LunaParserState(std::u8string_view script) :
		pars::QueryState<pars::u8::QueryTextCursor> {script},
		pars::QueryState<QueryIndentState> {} {}
};

using Parser = LunaParserState;
}  // namespace luna::Parse