#pragma once

#include "luna/Eval/Val.hpp"
#include "luna/Eval/Env.hpp"
#include "luna/Eval/FnApply.hpp"
#include "luna/Parse/Ast.hpp"

namespace luna::Eval::legacy {
inline constexpr auto eval(const Env& env, const Parse::ast::NumLit& numlit) -> Val {
	return {CstNum {numlit.lit}};
}

inline constexpr auto eval(const Env& env, const Parse::ast::StrLit& strlit) -> Val {
	return {CstStr {strlit.lit}};
}

inline constexpr auto eval(const Env& env, const Parse::ast::FnCall& fncall) -> Val {
	using namespace Parse::ast;
	return std::visit(
		overload {
			[&env]<typename CallerT, typename CalleeT>
				requires FnApplyable<CallerT, CalleeT>
			(const CallerT& caller, const CalleeT& callee) -> Val {
				return fn_apply(env, caller, callee);
			},
			[](const auto& caller, const auto& callee) -> Val { throw; },
			},
			*fncall.caller,
			*fncall.callee
	);
}

inline auto eval(const Env& env, const Parse::ast::Lambda& lambda) -> Val {
	using namespace Parse::ast;
	return {
		Clo {
			 env, *lambda.body
				| overload {
					[](const auto& expr) -> Parse::ast::Expr { return {}; },
				}
		}
	};
}

}  // namespace luna::Eval::legacy

namespace luna::Eval {
inline auto eval(const Env& env, const Parse::ast::Lambda& lambda) -> Val {
	namespace ast = Parse::ast;
	return {
		Clo {
			 .env = env,
			 //  .expr = *lambda.body,
		}
	};
}
}  // namespace luna::Eval