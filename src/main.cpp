#include "luna/Eval/Val.hpp"
#include "luna/Parse/Ast.hpp"

#include <immer/map.hpp>
#include <immer/map_transient.hpp>
#include <fmt/core.h>
#include <fmt/color.h>

int main() {
	using namespace luna::Parse::ast;

	auto mytable = Table {};
	mytable.emplace(Expr::box<StrLit>(u8"name"), Expr::box<StrLit>(u8"dvdbr3o"));
	mytable.emplace(Expr::box<StrLit>(u8"age"), Expr::box<NumLit>(19u));
	fmt::println("{}", to_string(mytable));

	auto mylam = Lambda {
		.body = Expr::box<FnCall>(FnCall {
			.caller = Expr::box<Ident>(OpIdent {u8"+"}),
			.callee = Expr::box<Ident>(ValIdent {u8"hello"}),
		}),
	};
	fmt::println("{}", to_string(mylam));

	fmt::println("{}", to_string(luna::Eval::Atm {&mylam}));
	fmt::println("{}", to_string(luna::Eval::Atm {&mytable}));
}
