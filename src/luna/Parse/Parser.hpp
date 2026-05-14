#pragma once

#include "pars.hpp"

#include <cstdint>
#include <stack>

namespace luna {
struct Indent {
	uint32_t indent;
};

struct IndentState : public std::stack<Indent> {
	IndentState() : std::stack<Indent> {{Indent {0}}} {}
};

struct QueryIndentState :
	pars::QueryTagBase<QueryIndentState>,
	pars::CopyPasteSnapshot<QueryIndentState, IndentState> {
	using QueryableType = IndentState;
};

class LunaParserState :
	public pars::QueryableMixin<pars::QueryParserCursor>,
	public pars::QueryableMixin<QueryIndentState> {
public:
	explicit LunaParserState(std::u8string_view s) :
		QueryableMixin<pars::QueryParserCursor> {{s}} {}

	using QueryableMixin<pars::QueryParserCursor>::query;
	using QueryableMixin<QueryIndentState>::query;
};

using Parser = LunaParserState;
}  // namespace luna