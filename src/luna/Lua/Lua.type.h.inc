/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace mlir::lua {

/// A dynamically typed Lua runtime value
/// Represents any first-class Lua value, including nil, boolean, number,
///     string, table, function, userdata, thread, and boxed runtime objects.
class ValueType;
/// A Lua multi-value pack
/// Represents Lua's multiple return values or varargs as a first-class IR value.
class PackType;
/// A specialized Lua table type
class TableType;
/// A specialized Lua number type
class NumberType;
/// A specialized Lua string type
class StringType;
class ValueType : public ::mlir::Type::TypeBase<ValueType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "lua.value";
  static constexpr ::llvm::StringLiteral dialectName = "lua";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"value"};
  }

};
class PackType : public ::mlir::Type::TypeBase<PackType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "lua.pack";
  static constexpr ::llvm::StringLiteral dialectName = "lua";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"pack"};
  }

};
class TableType : public ::mlir::Type::TypeBase<TableType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "lua.table";
  static constexpr ::llvm::StringLiteral dialectName = "lua";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"table"};
  }

};
class NumberType : public ::mlir::Type::TypeBase<NumberType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "lua.number";
  static constexpr ::llvm::StringLiteral dialectName = "lua";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"number"};
  }

};
class StringType : public ::mlir::Type::TypeBase<StringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "lua.string";
  static constexpr ::llvm::StringLiteral dialectName = "lua";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"string"};
  }

};

} // namespace mlir::lua
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::ValueType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::PackType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::TableType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::NumberType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::StringType)

#endif // GET_TYPEDEF_CLASSES

