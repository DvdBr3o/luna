#pragma once

#include <mlir/IR/MLIRContext.h>

namespace luna {
class MlirContext : public mlir::MLIRContext {
public:
	using mlir::MLIRContext::MLIRContext;

	template<typename... Args>
	inline static auto& global(Args&&... args) {
		static MlirContext ctx {std::forward<Args>(args)...};
		return ctx;
	}

	class Ignorable {
	public:
		Ignorable() : _ref(MlirContext::global()) {}

		Ignorable(MlirContext& ref) : _ref(ref) {}

	private:
		MlirContext& _ref;
	};
};

}  // namespace luna