#pragma once

#include "luna/Eval/Env.hpp"
#include "luna/Parse/Ast.hpp"
#include "luna/Utils/Hash.hpp"
#include "luna/Utils/Arena.hpp"

#include <absl/container/flat_hash_map.h>

#include <bit>
#include <cstddef>
#include <format>
#include <functional>
#include <string>
#include <variant>
#include <vector>

namespace luna::Eval {
/// @brief Byte
struct Byt {
	std::byte byt;

	//
	inline friend auto to_string(const Byt& byt) -> std::string {
		return std::format("Byt({:02x})", std::to_integer<int>(byt.byt));
	}

	template<typename H>
	inline friend auto AbslHashValue(H h, Byt b) {
		return H::combine(std::move(h), b.byt);
	}

	inline friend auto operator==(const Byt& l, const Byt& r) { return l.byt == r.byt; }
};

/// @brief Constant Number
struct CstNum {
	std::variant<int64_t, double> num;

	//
	inline friend auto to_string(const CstNum& cstnum) -> std::string {
		return cstnum.num
			 | overload {
				 [](auto num) { return std::format("CstNum({})", num); },
			 };
	}

	template<typename H>
	inline friend auto AbslHashValue(H h, CstNum cstnum) {
		return absl_hash_variant(std::move(h), cstnum.num);
	}

	inline friend auto operator==(const CstNum& l, const CstNum& r) { return l.num == r.num; }
};

/// @brief Constant String
struct CstStr {
	std::vector<char8_t> str;

	inline friend auto	 to_string(const CstStr& cststr) -> std::string {
		return std::format(
			"CstStr({})",
			std::bit_cast<std::string_view>(std::u8string_view {cststr.str.data()})
		);
	}

	inline static auto from(std::u8string_view sv) -> CstStr {
		return {
			std::vector<char8_t> {sv.begin(), sv.end()}
		};
	}

	template<typename H>
	inline friend auto AbslHashValue(H h, const CstStr& cststr) {
		return H::combine(std::move(h), cststr.str);
	}
};

/// @brief Closure based on ast expression
struct ExpClo {
	using Env = absl::flat_hash_map<std::u8string, Arena<struct Val>>;
	Env						env;
	const Parse::ast::Expr& exp;

	template<typename H>
	inline friend auto AbslHashValue(H h, const ExpClo& expclo) {
		std::size_t env_mixed = 0;
		for (const auto& [name, val] : expclo.env)
			env_mixed ^= absl::HashOf(name, val);
		return H::combine(std::move(h), expclo.env.size(), env_mixed, expclo.exp);
	}
};

/// @brief Opaque closure based on binary
struct OpqClo {
	std::function<struct Val(const struct Val&)> clo;

	template<typename H>
	inline friend auto AbslHashValue(H h, const OpqClo& opqclo) {
		return H::combine(std::move(h), opqclo.clo.target_type().hash_code());
	}
};

struct Clo : std::variant<ExpClo, OpqClo> {
	using Base = std::variant<ExpClo, OpqClo>;
	using Base::Base;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Clo& clo) {
		return absl_hash_variant(std::move(h), static_cast<const Base&>(clo));
	}
};

/// @brief Byte List
struct BytLst : std::vector<std::byte> {
	using std::vector<std::byte>::vector;
};

struct ValLst : std::vector<Arena<struct Val>> {
	using std::vector<Arena<struct Val>>::vector;
};

/// @brief Hash Table
struct Tbl {
	std::variant<BytLst, ValLst>							  lst;
	absl::flat_hash_map<Arena<struct Val>, Arena<struct Val>> tbl;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Tbl& tbl) {
		const auto lst_hash = absl::HashOf(tbl.lst);
		std::size_t tbl_mixed = 0;
		for (const auto& [k, v] : tbl.tbl)
			tbl_mixed ^= absl::HashOf(k, v);
		return H::combine(std::move(h), lst_hash, tbl.tbl.size(), tbl_mixed);
	}
};

/// @brief Value
struct Val : std::variant<CstNum, CstStr, Clo, Tbl> {
	using Base = std::variant<CstNum, CstStr, Clo, Tbl>;
	using Base::Base;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Val& val) {
		return absl_hash_variant(std::move(h), static_cast<const Base&>(val));
	}
};

struct RefVal {
	const Val& ref;

	template<typename H>
	inline friend auto AbslHashValue(H h, RefVal ref) {
		return H::combine(std::move(h), ref.ref);
	}
};
}  // namespace luna::Eval
