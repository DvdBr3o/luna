/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Lua.dialect.td                                                       *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::lua {

/// summary of Lua Dialect
/// description of Lua Dialect
class LuaDialect : public ::mlir::Dialect {
  explicit LuaDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~LuaDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("lua");
  }

  /// Parse an attribute registered to this dialect.
  ::mlir::Attribute parseAttribute(::mlir::DialectAsmParser &parser,
                                   ::mlir::Type type) const override;

  /// Print an attribute registered to this dialect.
  void printAttribute(::mlir::Attribute attr,
                      ::mlir::DialectAsmPrinter &os) const override;

  /// Parse a type registered to this dialect.
  ::mlir::Type parseType(::mlir::DialectAsmParser &parser) const override;

  /// Print a type registered to this dialect.
  void printType(::mlir::Type type,
                 ::mlir::DialectAsmPrinter &os) const override;

    static void sayHello();
  };

} // namespace mlir::lua
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::LuaDialect)
