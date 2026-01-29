include "mlir/IR/OpBase.td"
include "./ToyDialect.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

// mnemonic 指名字
class ToyOp<string mnemonic, list<Trait> traits = []> :
  Op<ToyDialect, mnemonic, traits>;

// Pure 是 Trait，表示没有 SideEffect 的纯函数
def AddOp : ToyOp<"add", [Pure]> {
  let summary = "add operation";
  let arguments = (ins AnyInteger:$lhs, AnyInteger:$rhs);
  let results = (outs AnyInteger:$result);
}