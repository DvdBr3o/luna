#pragma once

#include "luna/Eval/Env.hpp"
#include "luna/Parse/Ast.hpp"

#include <absl/container/flat_hash_map.h>

#include <string>
#include <variant>

namespace luna::Eval {
/// @brief Atom
struct Atm {
	void*			   atm;

	inline friend auto to_string(const Atm& atm) -> std::string {
		return std::format("Atm({})", atm.atm);
	}
};

/// @brief Constant Number
struct CstNum {
	std::uint32_t	   num;

	inline friend auto to_string(const CstNum& cstnum) -> std::string {
		return std::format("CstNum({})", cstnum.num);
	}
};

/// @brief Constant String
struct CstStr {
	std::u8string	   str;

	inline friend auto to_string(const CstStr& cststr) -> std::string {
		return std::format("CstStr({})", reinterpret_cast<const std::string&>(cststr.str));
	}

	inline static auto from(std::u8string_view sv) -> CstStr { return {std::u8string {sv}}; }
};

/// @brief Closure
struct Clo {
	Env				   env;
	Parse::ast::Expr   expr;

	inline friend auto to_string(const Clo& clo) -> std::string {
		return std::format("Clo({})", to_string(clo.expr));
	}
};

/// @brief Table
struct Tbl {
	absl::flat_hash_map<std::unique_ptr<struct Val>, std::unique_ptr<struct Val>> tbl;
};

/// @brief Value
struct Val : std::variant<Atm, CstNum, CstStr, Clo, Tbl> {
	template<typename F>
	auto visit(F&& f) -> decltype(auto) {
		return std::visit(std::forward<F>(f), *this);
	}

	template<typename F>
	auto visit(F&& f) const -> decltype(auto) {
		return std::visit(std::forward<F>(f), *this);
	}
};
}  // namespace luna::Eval
