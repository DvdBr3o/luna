/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: Lua.op.td                                                            *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::lua {

/// Set a value in a Lua table.
class TableSetOp;

} // namespace mlir::lua
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::lua {


//===----------------------------------------------------------------------===//
// ::mlir::lua::TableSetOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class TableSetOpGenericAdaptorBase {
public:
  using Properties = ::mlir::EmptyProperties;
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  TableSetOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("lua.table_set", odsAttrs.getContext());
  }

  TableSetOpGenericAdaptorBase(TableSetOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

};

} // namespace detail
template <typename RangeT>
class TableSetOpGenericAdaptor : public detail::TableSetOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::TableSetOpGenericAdaptorBase;
  static constexpr int odsIndex_table = 0;
  static constexpr int odsIndex_key = 1;
  static constexpr int odsIndex_value = 2;
public:
  TableSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  TableSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::OpaqueProperties properties, ::mlir::RegionRange regions = {}) : TableSetOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  TableSetOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : TableSetOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  TableSetOpGenericAdaptor(RangeT values, const TableSetOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = TableSetOp, typename = std::enable_if_t<std::is_same_v<LateInst, TableSetOp>>>
  TableSetOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getTable() {
    return (*getODSOperands(0).begin());
  }

  ValueT getKey() {
    return (*getODSOperands(1).begin());
  }

  ValueT getValue() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class TableSetOpAdaptor : public TableSetOpGenericAdaptor<::mlir::ValueRange> {
public:
  using TableSetOpGenericAdaptor::TableSetOpGenericAdaptor;
  TableSetOpAdaptor(TableSetOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class TableSetOp : public ::mlir::Op<TableSetOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = TableSetOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = TableSetOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_table = 0;
  static constexpr int odsIndex_key = 1;
  static constexpr int odsIndex_value = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    return {};
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("lua.table_set");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::Type> getTable() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getKey() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::Type> getValue() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::Type>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getTableMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getKeyMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getValueMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void populateInherentAttrs(::mlir::MLIRContext *ctx, const Properties &prop, ::mlir::NamedAttrList &attrs);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static TableSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static TableSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static TableSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static TableSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value table, ::mlir::Value key, ::mlir::Value value);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TableSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static TableSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TableSetOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static TableSetOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  static ::mlir::ParseResult parse(::mlir::OpAsmParser &parser, ::mlir::OperationState &result);
  void print(::mlir::OpAsmPrinter &_odsPrinter);
public:
};

} // namespace mlir::lua
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::lua::TableSetOp)


#endif // GET_OP_CLASSES

