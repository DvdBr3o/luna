/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Lua.op.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::lua::TableSetOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_Lua2Eop1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((true))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be any type, but got " << type;
  }
  return ::mlir::success();
}
namespace mlir::lua {


//===----------------------------------------------------------------------===//
// ::mlir::lua::TableSetOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

TableSetOpGenericAdaptorBase::TableSetOpGenericAdaptorBase(TableSetOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
TableSetOpAdaptor::TableSetOpAdaptor(TableSetOp op) : TableSetOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult TableSetOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult TableSetOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute TableSetOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code TableSetOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> TableSetOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void TableSetOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void TableSetOp::populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs) {
}

::llvm::LogicalResult TableSetOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void TableSetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  odsState.addOperands(table);
  odsState.addOperands(key);
  odsState.addOperands(value);
}

TableSetOp TableSetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, table, key, value);
  auto __res__ = ::llvm::dyn_cast<TableSetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TableSetOp TableSetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  return create(builder, builder.getLoc(), table, key, value);
}

void TableSetOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  odsState.addOperands(table);
  odsState.addOperands(key);
  odsState.addOperands(value);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

TableSetOp TableSetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, resultTypes, table, key, value);
  auto __res__ = ::llvm::dyn_cast<TableSetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TableSetOp TableSetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value) {
  return create(builder, builder.getLoc(), resultTypes, table, key, value);
}

void TableSetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TableSetOp TableSetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, resultTypes, operands, attributes);
  auto __res__ = ::llvm::dyn_cast<TableSetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TableSetOp TableSetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), resultTypes, operands, attributes);
}

void TableSetOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

TableSetOp TableSetOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, resultTypes, operands, properties, discardableAttributes);
  auto __res__ = ::llvm::dyn_cast<TableSetOp>(builder.create(__state__));
  assert(__res__ && "builder didn't return the right type");
  return __res__;
}

TableSetOp TableSetOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), resultTypes, operands, properties, discardableAttributes);
}

::llvm::LogicalResult TableSetOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Lua2Eop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Lua2Eop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_Lua2Eop1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult TableSetOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::mlir::ParseResult TableSetOp::parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result) {
  ::mlir::OpAsmParser::UnresolvedOperand tableRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> tableOperands(&tableRawOperand, 1);  ::llvm::SMLoc tableOperandsLoc;
  (void)tableOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand keyRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> keyOperands(&keyRawOperand, 1);  ::llvm::SMLoc keyOperandsLoc;
  (void)keyOperandsLoc;
  ::mlir::OpAsmParser::UnresolvedOperand valueRawOperand{};
  ::llvm::ArrayRef<::mlir::OpAsmParser::UnresolvedOperand> valueOperands(&valueRawOperand, 1);  ::llvm::SMLoc valueOperandsLoc;
  (void)valueOperandsLoc;
  ::mlir::Type tableRawType{};
  ::llvm::ArrayRef<::mlir::Type> tableTypes(&tableRawType, 1);
  ::mlir::Type keyRawType{};
  ::llvm::ArrayRef<::mlir::Type> keyTypes(&keyRawType, 1);
  ::mlir::Type valueRawType{};
  ::llvm::ArrayRef<::mlir::Type> valueTypes(&valueRawType, 1);

  tableOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(tableRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  keyOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(keyRawOperand))
    return ::mlir::failure();
  if (parser.parseComma())
    return ::mlir::failure();

  valueOperandsLoc = parser.getCurrentLocation();
  if (parser.parseOperand(valueRawOperand))
    return ::mlir::failure();
  {
    auto loc = parser.getCurrentLocation();(void)loc;
    if (parser.parseOptionalAttrDict(result.attributes))
      return ::mlir::failure();
    if (failed(verifyInherentAttrs(result.name, result.attributes, [&]() {
        return parser.emitError(loc) << "'" << result.name.getStringRef() << "' op ";
      })))
      return ::mlir::failure();
  }
  if (parser.parseColon())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    tableRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    keyRawType = type;
  }
  if (parser.parseComma())
    return ::mlir::failure();

  {
    ::mlir::Type type;
    if (parser.parseCustomTypeWithFallback(type))
      return ::mlir::failure();
    valueRawType = type;
  }
  if (parser.resolveOperands(tableOperands, tableTypes, tableOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(keyOperands, keyTypes, keyOperandsLoc, result.operands))
    return ::mlir::failure();
  if (parser.resolveOperands(valueOperands, valueTypes, valueOperandsLoc, result.operands))
    return ::mlir::failure();
  return ::mlir::success();
}

void TableSetOp::print(::mlir::OpAsmPrinter &_odsPrinter) {
  _odsPrinter << ' ';
  _odsPrinter << getTable();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getKey();
  _odsPrinter << ",";
  _odsPrinter << ' ';
  _odsPrinter << getValue();
  ::llvm::SmallVector<::llvm::StringRef, 2> elidedAttrs;
  _odsPrinter.printOptionalAttrDict((*this)->getAttrs(), elidedAttrs);
  _odsPrinter << ' ' << ":";
  _odsPrinter << ' ';
  {
    auto type = getTable().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getKey().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
  _odsPrinter << ",";
  _odsPrinter << ' ';
  {
    auto type = getValue().getType();
    if (auto validType = ::llvm::dyn_cast<::mlir::Type>(type))
      _odsPrinter.printStrippedAttrOrType(validType);
   else
     _odsPrinter << type;
  }
}


} // namespace mlir::lua
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::lua::TableSetOp)


#endif // GET_OP_CLASSES

