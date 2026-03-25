/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::mlir::lua::ValueType,
::mlir::lua::PackType,
::mlir::lua::TableType,
::mlir::lua::NumberType,
::mlir::lua::StringType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::mlir::lua::ValueType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::lua::ValueType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::mlir::lua::PackType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::lua::PackType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::mlir::lua::TableType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::lua::TableType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::mlir::lua::NumberType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::lua::NumberType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(::mlir::lua::StringType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::mlir::lua::StringType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::mlir::lua::ValueType>([&](auto t) {
      printer << ::mlir::lua::ValueType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::mlir::lua::PackType>([&](auto t) {
      printer << ::mlir::lua::PackType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::mlir::lua::TableType>([&](auto t) {
      printer << ::mlir::lua::TableType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::mlir::lua::NumberType>([&](auto t) {
      printer << ::mlir::lua::NumberType::getMnemonic();
      return ::mlir::success();
    })
    .Case<::mlir::lua::StringType>([&](auto t) {
      printer << ::mlir::lua::StringType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace mlir::lua {


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::ValueType)
namespace mlir::lua {


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::PackType)
namespace mlir::lua {


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::TableType)
namespace mlir::lua {


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::NumberType)
namespace mlir::lua {


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::StringType)
namespace mlir::lua {


/// Parse a type registered to this dialect.
::mlir::Type LuaDialect::parseType(::mlir::DialectAsmParser &parser) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef mnemonic;
  ::mlir::Type genType;
  auto parseResult = generatedTypeParser(parser, &mnemonic, genType);
  if (parseResult.has_value())
    return genType;
  
  parser.emitError(typeLoc) << "unknown  type `"
      << mnemonic << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print a type registered to this dialect.
void LuaDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace mlir::lua

#endif // GET_TYPEDEF_CLASSES

