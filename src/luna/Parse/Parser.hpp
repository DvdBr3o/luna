#pragma once

#include "luna/Source.hpp"
#include "pars.hpp"

#include <cstdint>
#include <stack>

namespace luna::Parse {
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

struct QueryLocation :
	pars::QueryTagBase<QueryLocation>,
	pars::CopyPasteSnapshot<QueryLocation, Location> {
	using QueryableType = Location;
};

inline constexpr QueryLocation query_location;

class LunaParserState :
	public pars::QueryableMixin<pars::QueryParserCursor>,
	public pars::QueryableMixin<QueryIndentState>,
	public pars::QueryableMixin<QueryLocation> {
public:
	explicit LunaParserState(std::u8string_view s) :
		QueryableMixin<pars::QueryParserCursor> {{s}} {}

	using QueryableMixin<pars::QueryParserCursor>::query;
	using QueryableMixin<QueryIndentState>::query;
	using QueryableMixin<QueryLocation>::query;
};

using Parser = LunaParserState;
}  // namespace luna::Parse