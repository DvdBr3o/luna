#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/TargetSelect.h>

namespace luna {
class LlvmContextManger {
public:
	inline static auto get() -> LlvmContextManger& {
		static LlvmContextManger manager;
		return manager;
	}

	inline static auto context() -> llvm::LLVMContext& { return get()._context; }

private:
	LlvmContextManger() {
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
	}

private:
	llvm::LLVMContext _context;
};

inline auto llvm_context() -> llvm::LLVMContext& {
	return LlvmContextManger::context();
}
}  // namespace luna