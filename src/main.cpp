#include <mlir/IR/AsmState.h>
#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/Diagnostics.h>
#include <mlir/IR/MLIRContext.h>
#include <mlir/Parser/Parser.h>
#include <mlir/Pass/PassRegistry.h>
#include <mlir/Support/FileUtilities.h>
#include <mlir/Dialect/Func/IR/FuncOps.h>
#include <mlir/Dialect/Arith/IR/Arith.h>
#include <mlir/Pass/Pass.h>
#include <mlir/Dialect/LLVMIR/LLVMDialect.h>
#include <mlir/Pass/PassManager.h>
#include <mlir/Parser/Parser.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>

#include "luna/Lua/Lua.op.h.inc"
#include "luna/Lua/Lua.dialect.h.inc"
#include "mlir/IR/OwningOpRef.h"

#include <format>

using namespace mlir;

int main() {
	mlir::DialectRegistry registry;
	registry.insert<mlir::lua::LuaDialect, mlir::func::FuncDialect, mlir::LLVM::LLVMDialect>();
	mlir::MLIRContext context { registry };
	context.loadAllAvailableDialects();
	llvm::outs() << "registered dialects:\n";
	for (const auto& name : context.getDialectRegistry().getDialectNames())
		llvm::outs() << name << '\n';

	auto source_mgr = std::make_shared<llvm::SourceMgr>();
	auto mod =
		mlir::parseSourceFile("public/hello.mlir", source_mgr, mlir::ParserConfig { &context });

	if (!mod)
		llvm::outs() << "failed to load!\n";

	mod->print(llvm::outs());

	mlir::PassManager pm { &context };

	llvm::outs() << "here\n";
}