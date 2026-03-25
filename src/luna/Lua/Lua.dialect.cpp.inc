/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Lua.dialect.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::LuaDialect)
namespace mlir::lua {


LuaDialect::LuaDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<LuaDialect>())
    
     {
  getContext()->loadDialect<::mlir::tensor::TensorDialect>();
  initialize();
}

} // namespace mlir::lua
