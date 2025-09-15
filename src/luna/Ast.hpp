#pragma once

#include "luna/Lexer.hpp"

#include <tl/expected.hpp>

#include <cstdint>
#include <variant>

namespace luna::ast {
	enum class ParseErrorCode : std::uint32_t {
		NotMatched = 0,

	};

	namespace ParseErrors {
		/**
		 * @brief Not even matched. Never throw grammar errors.
		 */
		struct NotMatched {};

		struct ParseError :
			public std::variant<  //
				NotMatched		  //
				> {
			using variant::variant;
			ParseErrorCode error_code = ParseErrorCode::NotMatched;
		};
	}  // namespace ParseErrors

	using ParseErrors::ParseError;

	struct Variable {};

	struct Literal {};

	using Expression = std::variant<
		Variable,  //
		Literal	   //
		>;

	struct ScopeBase {
		std::uint32_t depth;
	};

	struct LambdaParamList {};

	struct LambdaBody {};

	struct LambdaScope : public ScopeBase {
		LambdaParamList param_list;
		LambdaBody		body;
	};

	struct TableScope : public ScopeBase {};

	using Scope = std::variant<LambdaScope, TableScope>;

	struct DestructureBase {};

	struct TupleDestructure : public DestructureBase {};

	struct TableDestructure : public DestructureBase {};

	using Destructure = std::variant<TupleDestructure, TableDestructure>;

	/**
	 * @brief
	 *
	 * ```luna
	 * local a = 1
	 * ```
	 */
	struct LocalAssignStatement {
		using Assigned = std::variant<Variable, Destructure>;
		Assigned   assigned;
		Expression assignment;
	};

	struct TrailingIfStatement;

	using Statement = std::variant<
		LocalAssignStatement,				  //
		std::unique_ptr<TrailingIfStatement>  //
		// TrailingIfStatement	 //
		>;

	struct TrailingIfStatement {
		Statement  statement;
		Expression if_decision;
	};

}  // namespace luna::ast

namespace luna::ast {
	inline static auto parse(const lex::TokenStream& ts) -> LambdaBody {
		return {};
	}
}  // namespace luna::ast