#ifndef LUA_TYPE_TD
#define LUA_TYPE_TD

include "mlir/IR/AttrTypeBase.td"
include "luna/Lua/Lua.dialect.td"

class LuaType<string name, string typeMnemonic, list<Trait> traits = []>
    : TypeDef<LuaDialect, name, traits> {
  let mnemonic = typeMnemonic;
}

def Lua_Value : LuaType<"Value", "value"> {
  let summary = "A dynamically typed Lua runtime value";
  let description = [{
    Represents any first-class Lua value, including nil, boolean, number,
    string, table, function, userdata, thread, and boxed runtime objects.
  }];
}

def Lua_Pack : LuaType<"Pack", "pack"> {
  let summary = "A Lua multi-value pack";
  let description = [{
    Represents Lua's multiple return values or varargs as a first-class IR value.
  }];
}

def Lua_Table : LuaType<"Table", "table"> {
  let summary = "A specialized Lua table type";
}

def Lua_Number : LuaType<"Number", "number"> {
  let summary = "A specialized Lua number type";
}

def Lua_String : LuaType<"String", "string"> {
  let summary = "A specialized Lua string type";
}

#endif
