func.func @create_table() -> !lua.table {
    %0 = lua.create_table : !lua.table
    return %0 : !lua.table
}

%1 = lua.add %arg0, %arg1 : !lua.number