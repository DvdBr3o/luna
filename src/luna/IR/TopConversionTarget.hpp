#pragma once

#include "luna/MlirContext.hpp"
#include "luna/Lua/Lua.hpp"

#include <mlir/Conversion/Passes.h>
#include <mlir/IR/Dialect.h>
#include <mlir/Transforms/DialectConversion.h>
#include <mlir/IR/MLIRContext.h>

namespace luna {
class TopConversionTarget : public mlir::ConversionTarget {
public:
	TopConversionTarget(mlir::MLIRContext& context = MlirContext::global()) :
		mlir::ConversionTarget { context } {
		addLegalDialect<mlir::lua::LuaDialect>();
	}
};

}  // namespace luna