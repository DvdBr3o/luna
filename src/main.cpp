#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/IR/Module.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/TargetParser/Triple.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Verifier.h>

#include "luna/Backend/Llvm.hpp"
#include "luna/Parse/Ast.hpp"

int main() {
	auto m = llvm::Module {"luna", luna::llvm_context()};

	m.setTargetTriple(llvm::Triple {"x86_64-pc-windows-gnu"});
	m.setDataLayout(llvm::DataLayout {""});

	auto builder = llvm::IRBuilder<> {luna::llvm_context()};
	auto fn		 = llvm::Function::Create(
		llvm::FunctionType::get(builder.getInt32Ty(), {}),
		llvm::GlobalValue::ExternalLinkage,
		"main",
		m
	);
	auto entry = llvm::BasicBlock::Create(luna::llvm_context(), "entry", fn);
	builder.SetInsertPoint(entry);
	auto v = llvm::ConstantInt::get(builder.getInt32Ty(), 42);
	builder.CreateRet(v);

	llvm::verifyFunction(*fn);
	llvm::verifyModule(m);

	m.print(llvm::outs(), nullptr);
}
