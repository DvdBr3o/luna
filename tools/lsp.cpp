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
#include <mlir/InitAllDialects.h>
#include <mlir/InitAllExtensions.h>
#include <mlir/Tools/mlir-lsp-server/MlirLspServerMain.h>

#include "luna/Lua/Lua.op.h.inc"
#include "luna/Lua/Lua.dialect.h.inc"

using namespace mlir;

int main(int argc, char** argv) {
	mlir::DialectRegistry registry;
	registerAllDialects(registry);
	registerAllExtensions(registry);
	registry.insert<mlir::lua::LuaDialect>();
	return mlir::failed(mlir::MlirLspServerMain(argc, argv, registry));
}
