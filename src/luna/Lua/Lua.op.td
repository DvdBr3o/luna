include "Lua.dialect.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

// 基础 Op 类，减少重复代码
class Lua_Op<string mnemonic, list<Trait> traits = []> :
    Op<LuaDialect, mnemonic, traits>;

def TableSetOp : Lua_Op<"table_set"> {
  let summary = "Set a value in a Lua table.";
  let arguments = (ins 
    AnyType:$table,   // 这里的 AnyType 后面可以优化为 LuaTableType
    AnyType:$key, 
    AnyType:$value
  );
  // Lua 的 table 设置通常有副作用（修改内存）
  let results = (outs); 

  let assemblyFormat = "$table `,` $key `,` $value attr-dict `:` type($table) `,` type($key) `,` type($value)";
}
