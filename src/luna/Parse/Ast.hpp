#pragma once

#include "pars.hpp"

namespace luna {
struct NumLit {
	uint32_t lit;
};

struct StrLit {
	std::u8string lit;
};

struct Fn {};

struct ValIdent {
	std::u8string ident;
};

struct OpIdent {
	std::u8string ident;
};

struct Ident : std::variant<ValIdent, OpIdent> {
	[[nodiscard]] auto identifer() const -> std::u8string_view {
		return *this
			 | pars::overload {[](auto&& ident) -> std::u8string_view { return ident.ident; }};
	}
};

struct AstNode :
	std::variant<
		NumLit,	 //
		StrLit,	 //
		Fn		 //
		> {
	//
};
}  // namespace luna