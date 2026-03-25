#include <mlir/IR/Dialect.h>
#include <mlir/IR/DialectImplementation.h>
#include <mlir/Dialect/Tensor/IR/Tensor.h>
#include <llvm/ADT/TypeSwitch.h>

#include "luna/Lua/Lua.hpp"

#include "luna/Lua/Lua.dialect.cpp.inc"
#define GET_TYPEDEF_CLASSES
#include "luna/Lua/Lua.type.cpp.inc"
#define GET_OP_CLASSES
#include "luna/Lua/Lua.op.cpp.inc"

#include <iostream>

namespace mlir::lua {
void LuaDialect::initialize() {
	llvm::outs() << "initializing " << getDialectNamespace() << "\n";
	addTypes<
#define GET_TYPEDEF_LIST
#include "luna/Lua/Lua.type.cpp.inc"
		>();
	addOperations<
#define GET_OP_LIST
#include "luna/Lua/Lua.op.cpp.inc"
		>();
}

LuaDialect::~LuaDialect() {
	llvm::outs() << "destroying " << getDialectNamespace() << "\n";
}

auto LuaDialect::sayHello() -> void {
	std::cout << "hello!\n";
}

mlir::Attribute LuaDialect::parseAttribute(mlir::DialectAsmParser& parser, mlir::Type type) const {
	parser.emitError(parser.getNameLoc(), "lua dialect does not define custom attributes");
	return {};
}

void LuaDialect::printAttribute(mlir::Attribute attr, mlir::DialectAsmPrinter& os) const {
	llvm_unreachable("lua dialect does not define custom attributes");
}

// mlir::Type LuaDialect::parseType(mlir::DialectAsmParser &parser) const {
// 	llvm::StringRef mnemonic;
// 	mlir::Type type;

// 	auto result = generatedTypeParser(parser, &mnemonic, type);
// 	if (result.has_value()) {
// 		if (mlir::failed(*result)) {
// 			return {};
// 		}
// 		return type;
// 	}

// 	parser.emitError(parser.getNameLoc()) << "unknown lua type: " << mnemonic;
// 	return {};
// }

// void LuaDialect::printType(mlir::Type type, mlir::DialectAsmPrinter& os) const {
// 	if (mlir::succeeded(generatedTypePrinter(type, os)))
// 		return;

// 	llvm_unreachable("unexpected lua type kind");
// }
}  // namespace mlir::lua
