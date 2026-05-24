#pragma once

#include "luna/Utils/Overload.hpp"

#include <absl/container/node_hash_map.h>
#include <absl/hash/hash.h>

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <variant>

namespace luna::Parse::ast {
struct Expr;

struct NumLit {
	uint32_t		   lit;

	inline friend auto to_string(const NumLit& numlit) -> std::string {
		return std::format("NumLit({})", numlit.lit);
	}

	inline friend auto operator==(const NumLit&, const NumLit&) -> bool = default;

	template<typename H>
	inline friend auto AbslHashValue(H h, const NumLit& numlit) -> H {
		return H::combine(std::move(h), numlit.lit);
	}
};

struct StrLit {
	std::u8string	   lit;

	inline friend auto to_string(const StrLit& strlit) -> std::string {
		return std::format("StrLit({})", reinterpret_cast<const std::string&>(strlit.lit));
	}

	inline friend auto operator==(const StrLit&, const StrLit&) -> bool = default;

	template<typename H>
	inline friend auto AbslHashValue(H h, const StrLit& strlit) -> H {
		return H::combine(std::move(h), strlit.lit);
	}
};

struct Lambda {
	std::unique_ptr<Expr> body;

	inline friend auto	  to_string(const Lambda& lambda) -> std::string;
	inline friend auto	  operator==(const Lambda& lhs, const Lambda& rhs) -> bool;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Lambda& lambda) -> H;
};

struct ENV {
	inline friend constexpr auto operator==(const ENV&, const ENV&) { return true; }

	template<typename H>
	inline friend auto AbslHashValue(H h, const ENV& env) -> H {
		return H::combine(std::move(h), 0u);
	}

	inline friend auto to_string(const ENV& env) -> std::string { return "ENV()"; }
};

struct ValIdent {
	std::u8string	   ident;

	inline friend auto to_string(const ValIdent& ident) -> std::string {
		return std::format("ValIdent({})", reinterpret_cast<const std::string&>(ident.ident));
	}

	inline friend auto operator==(const ValIdent&, const ValIdent&) -> bool = default;

	template<typename H>
	inline friend auto AbslHashValue(H h, const ValIdent& ident) -> H {
		return H::combine(std::move(h), ident.ident);
	}
};

struct OpIdent {
	std::u8string	   ident;

	inline friend auto to_string(const OpIdent& ident) -> std::string {
		return std::format("OpIdent({})", reinterpret_cast<const std::string&>(ident.ident));
	}

	inline friend auto operator==(const OpIdent&, const OpIdent&) -> bool = default;

	template<typename H>
	inline friend auto AbslHashValue(H h, const OpIdent& ident) -> H {
		return H::combine(std::move(h), ident.ident);
	}
};

struct Ident : std::variant<ValIdent, OpIdent> {
	[[nodiscard]] auto identifer() const -> std::u8string_view {
		return *this | overload {[](auto&& ident) -> std::u8string_view { return ident.ident; }};
	}

	inline friend auto to_string(const Ident& ident) -> std::string {
		return std::format(
			"Ident({})",
			std::string_view(reinterpret_cast<const char*>(ident.identifer().data()))
		);
	}

	inline friend auto operator==(const Ident&, const Ident&) -> bool = default;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Ident& ident) -> H {
		return ident
			 | overload {
				 [&h](const ValIdent& value) mutable {
					 return H::combine(std::move(h), 0u, value);
				 },
				 [&h](const OpIdent& value) mutable {  //
					 return H::combine(std::move(h), 1u, value);
				 },
			 };
	}
};

struct FnCall {
	std::unique_ptr<Expr> caller;
	std::unique_ptr<Expr> callee;

	inline friend auto	  to_string(const FnCall& fncall) -> std::string;
	inline friend auto	  operator==(const FnCall& lhs, const FnCall& rhs) -> bool;

	template<typename H>
	inline friend auto AbslHashValue(H h, const FnCall& fncall) -> H;
};

struct ExprPtrHash {
	auto operator()(const std::unique_ptr<Expr>& expr) const -> size_t;
};

struct ExprPtrEq {
	auto operator()(const std::unique_ptr<Expr>& lhs, const std::unique_ptr<Expr>& rhs) const
		-> bool;
};

// TODO(pars): use arena instead of unique_ptr
using TableMapBase =
	absl::node_hash_map<std::unique_ptr<Expr>, std::unique_ptr<Expr>, ExprPtrHash, ExprPtrEq>;

struct Table : TableMapBase {
	using TableMapBase::TableMapBase;

	inline friend auto to_string(const Table& table) -> std::string;
	inline friend auto operator==(const Table& lhs, const Table& rhs) -> bool;

	template<typename H>
	inline friend auto AbslHashValue(H h, const Table& table) -> H;
};

struct Expr : std::variant<NumLit, StrLit, ENV, Ident, Lambda, Table, FnCall> {
	using std::variant<NumLit, StrLit, ENV, Ident, Lambda, Table, FnCall>::variant;

	inline friend auto operator==(const Expr& lhs, const Expr& rhs) -> bool {
		return std::visit(
			overload {
				[](const NumLit& lhs, const NumLit& rhs) { return lhs == rhs; },
				[](const StrLit& lhs, const StrLit& rhs) { return lhs == rhs; },
				[](const Ident& lhs, const Ident& rhs) { return lhs == rhs; },
				[](const Lambda& lhs, const Lambda& rhs) { return lhs == rhs; },
				[](const Table& lhs, const Table& rhs) { return lhs == rhs; },
				[](const FnCall& lhs, const FnCall& rhs) { return lhs == rhs; },
				[](const auto&, const auto&) { return false; },
			},
			lhs,
			rhs
		);
	}

	inline friend auto to_string(const Expr& expr) -> std::string {
		return expr | overload {[](const auto& value) { return to_string(value); }};
	}

	template<typename H>
	inline friend auto AbslHashValue(H h, const Expr& expr) -> H {
		return expr
			 | overload {
				 [&h](const NumLit& value) mutable { return H::combine(std::move(h), 0u, value); },
				 [&h](const StrLit& value) mutable { return H::combine(std::move(h), 1u, value); },
				 [&h](const ENV& value) mutable { return H::combine(std::move(h), 2u, value); },
				 [&h](const Ident& value) mutable { return H::combine(std::move(h), 3u, value); },
				 [&h](const Lambda& value) mutable { return H::combine(std::move(h), 4u, value); },
				 [&h](const Table& value) mutable { return H::combine(std::move(h), 5u, value); },
				 [&h](const FnCall& value) mutable { return H::combine(std::move(h), 6u, value); },
			 };
	}

	template<typename T, typename... Args>
		requires(std::is_constructible_v<Expr, T> && std::is_constructible_v<T, Args && ...>)
	inline static auto box(Args&&... args) -> std::unique_ptr<Expr> {
		return std::make_unique<Expr>(T {std::forward<Args>(args)...});
	}
};

template<typename T>
concept ExprC = std::is_constructible_v<Expr, T>;

}  // namespace luna::Parse::ast

namespace luna::Parse::ast {
inline auto to_string(const Lambda& lambda) -> std::string {
	return std::format("Lambda({})", to_string(*lambda.body));
}

inline auto operator==(const Lambda& lhs, const Lambda& rhs) -> bool {
	return *lhs.body == *rhs.body;
}

template<typename H>
inline auto AbslHashValue(H h, const Lambda& lambda) -> H {
	return H::combine(std::move(h), *lambda.body);
}

inline auto to_string(const FnCall& fncall) -> std::string {
	return std::format("FnCall({}, {})", to_string(*fncall.caller), to_string(*fncall.callee));
}

inline auto operator==(const FnCall& lhs, const FnCall& rhs) -> bool {
	return *lhs.caller == *rhs.caller && *lhs.callee == *rhs.callee;
}

template<typename H>
inline auto AbslHashValue(H h, const FnCall& fncall) -> H {
	return H::combine(std::move(h), *fncall.caller, *fncall.callee);
}

inline auto ExprPtrHash::operator()(const std::unique_ptr<Expr>& expr) const -> size_t {
	return absl::HashOf(*expr);
}

inline auto ExprPtrEq::operator()(
	const std::unique_ptr<Expr>& lhs, const std::unique_ptr<Expr>& rhs
) const -> bool {
	return *lhs == *rhs;
}

inline auto to_string(const Table& table) -> std::string {
	std::string res = "Table(";
	for (const auto& [k, v] : table)
		res += std::format("Pair({}:{}),", to_string(*k), to_string(*v));
	res += ')';
	return res;
}

inline auto operator==(const Table& lhs, const Table& rhs) -> bool {
	if (lhs.size() != rhs.size())
		return false;

	for (const auto& [k, v] : lhs) {
		const auto it = rhs.find(k);
		if (it == rhs.end() || *it->second != *v)
			return false;
	}
	return true;
}

template<typename H>
inline auto AbslHashValue(H h, const Table& table) -> H {
	std::size_t mixed = 0;
	for (const auto& [k, v] : table) mixed ^= absl::HashOf(*k, *v);
	return H::combine(std::move(h), table.size(), mixed);
}
}  // namespace luna::Parse::ast
