#include "luna/Eval/Evaluator.hpp"
#include "luna/Parse/Ast.hpp"
#include "luna/Utils/Overload.hpp"

namespace luna::Eval {
Evaluator::Evaluator(std::span<char> buffer) :
	_arena {
		static_cast<void*>(buffer.data()),
		buffer.size(),
		std::pmr::new_delete_resource(),
	} {}

auto Evaluator::eval(const Parse::ast::Expr& expr) -> Val {
	using namespace Parse;
	expr
		| overload {
			[](const ast::NumLit& numlit) {},
			[](const ast::StrLit& strlit) {},
			[](const ast::ENV& env) {},
			[](const ast::Ident& ident) {},
			[](const ast::Lambda& fn) {},
			[](const ast::Table& table) {},
			[](const ast::FnCall& fncall) {},
			// [](const auto&) {},
		};
	return {};
}
}  // namespace luna::Eval