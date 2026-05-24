#pragma once

#if defined LUNA_USE_EMBEDDED_LLVM

#	include <llvm/IR/LLVMContext.h>
#	include <llvm/Support/TargetSelect.h>
#	include <llvm/TargetParser/Triple.h>

namespace luna {
class LLVMManager {
public:
	inline static auto get() -> LLVMManager& {
		static LLVMManager manager;
		return manager;
	}

	inline static auto init() -> void { get(); }

private:
	LLVMManager() {
		llvm::InitializeAllTargets();
		llvm::InitializeAllTargetMCs();
		llvm::InitializeAllAsmPrinters();
		llvm::InitializeAllAsmParsers();
	}
};

class LLVMTextEmitter {
public:
};

class LLVMModuleEmitter {
public:
};

}  // namespace luna

#endif