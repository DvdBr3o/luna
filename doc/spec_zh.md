# 语言规范

## 赋值

### 解构

```lua
local b, c, d = 1, 2, 3
local { e, f, g } = 4, 5, 6

local {
    :f1
    :f2
    f3_alias: f3
} = require "luna.nowhere"
```

### 重赋值

```lua
local a = 1
a = "hello"
local a -- error
```

## 字符串字面量

### 多行

```lua
local str_literal1 = "Hello, this is a string
that can be
separated into multiple lines!"
```

### 行头对齐

```lua
local str_literal2 =
    "You can also
    "align each line
    "like this."
```

### 格式化字符串

```lua
local str_literal3 = f"{a}!, maybe format support like this?" -- maybe `f` for a comptime function
```

### 函数调用 + 字符串字面量

```lua
print f"xxxxx", a -- print(f("xxxxx"), a)
print f "xxxxx", a -- print(f("xxxxx", a)) -- error
```

## Table 字面量

### List Table

```lua
local list1 =
    1, 2, 3
    4, 5, func "arg1", -- 第一行尾随逗号必要，之后不必要
        1, 1, 4,
        5, 1, 4
    "what?"
local list2 = 1, 2, -- 第一行尾随逗号必要, 之后不必要
    3, 4
```

### Dict Table

```lua
local dict1 =
    name: "DvdBr3o"
    age: 19
    gender: "male"
    [1 + 2]: "yes"
local dict2 = name: "xll", -- 第一行尾随逗号必要, 之后不必要
    age: dict1.age + 1
    gender: "female"
```

### 混合型 Table

混合型 Table 的花括号必要, 纯 List 和 纯 Dict 则不必要

```lua
local mytable = {
    1, 3, 2
    name: "somebody"
    "hello", 114.514,
    42, age: 91
}
```

### 具名重复

```lua
local a = 1
local b = "what?"
local mytable1 = {
    :a -- equivalent to `a: a`
    :b
}
local mytable2 = :a, :b
```

### 切片

```lua
local items =
    1, 2, 3, 4, 5
    6, 7, 8, 9, 10
for v in *items[nil,2] ->
    println v
```

### 元表

```lua
local foo =
    <add>: (@, right: Number) -> @value + right
    hello: () -> print "hello"

local my_metatable =
    __add: (@, right: Number) -> @value + right
local bar = <>: my_metatable
```

### 自引用

Table 字面量声明中可以用 `@` 提及自己

与 [self 函数](#self-函数)类似, 但是 `@` 的访问是在赋值时直接进行的, 而非延后到某个函数被调用

```lua
local foo =
    b: @a
    a: 1

--[[ 等效于
local foo = {
    a = 1
}
foo.b = foo.a + 1
]]
```

也可以提及前后的键, 但不能环形引用

前后键与当前作用域已有变量重名, 优先匹配已有变量

```lua
local foo =
    b: a + 1
    a: 1

--[[ 等效于
local foo = {
    a = 1
}
foo.b = foo.a + 1
]]
```

### 尾字面量返回

当函数体有且仅有形如表的键值对, 且对齐函数体的根缩进时, 所有键值对视为同一个匿名表, 并作为返回值

```lua
local foo = ->
    name: "DvdBr3o"
    age: 19
print foo!.name -- "DvdBr3o"
```

同时这也是 luna 允许直接在全局根缩进下写键值对作为[模块](#模块)的机制依据

```lua
-- foo.luna
do_foo: -> print "do_foo!"
name: "foo"

-- bar.luna
local {
    :do_foo
    :name
} = require "foo"

do_foo!
print name
```

## 函数字面量

### 无参数

```lua
local fun = -> 1
```

### 无类型参数

```lua
local fun = (a) -> a - 2
```

### 带类型参数

```lua
local fun = (a: Number) -> a - 2
```

### 多行函数

```lua
local fun = (
    lhs: String,
    rhs: String
): String ->
    local value = 1
    f"{lhs}, value, {rhs}"
```

### 字典参数函数 + 默认值

```lua
local fun = {
    c1: String = "hello",
    c2: Number,
    c3: Function
} -> c3 f"{c1}, {c2 + 1}"

fun { c3: &print, c1: "hello", c2: 42 }
fun c3: &print, c1: "hello", c2: 42

fun
    c3: &print
    c2: 42

-- TODO: Consider tuple-table conversion for function calls?
```

### 元组返回值

```lua
local fun = (s: String + Len(3, nil)) ->
    s[1], s[2], s[3] -- 是否保留 lua 下标从 1 开始的规定?
```

### self 函数

```lua
local fun = (@: String) -> @ .. "foo"
```

### 具名 self

```lua
local fun = (@s: String) -> @ .. "bar"
```

### self + 字典参数

```lua
local fun = (@s: String, {
    fore: String = "hello"
    suf: String = "bye"
}): @ ->
    print f"{fore}, {@}, {suf}"
    -- 末尾无需写 @, `(...): @ -> ...` 默认返回 @
```

### self + 链式调用

```lua
-- self 函数优先
print "hello, i'm dvdbr3o, i'm 19 years old, i'm a man, yeah!"
    \split by: ","
    \reverse!
    \transform s -> s .. "~"
    \join!
    \print! -- print 也是 self 函数
```

## 函数调用

```lua
sum = (a: Addable, b: Addable) -> a + b
```

### 无括号

```lua
sum a, b
```

### 链式调用

```lua
print sum a, b -- 默认右结合
```

### 柯里化

```lua
xmake_target = (name: String) -> (spec: Table) ->
    spec.name = name
    spec
xmake_target "hello" {
    kind: "static"
    -- ...
}
```

## 分支

### if else

```lua
if foo ~= 1
    print "what?"
elseif foo ~= 2
    print "indeed."
else
    print "unreachable"
```

### if indent

```lua
if func "a", -- 不允许直接换行缩进, 尾随逗号必要
    1, 2
        print "if with list"

if func "a", 1, 2 do print "if with list"
```

```lua
if func
    arg1: 1
    arg2: "ciallo~"
        print "if with table"
```

```lua
if func {
    1, 2, 3
    arg: "hello"
    "fuck"
    42.114514
}
    print "if with mixed table"
```

### 尾随 if

```lua
print "yep" if a == 1
```

### if local

相当于 C++ 的 `if auto` 和 Rust 的 `if let`

当且仅当返回值为以下情况判假跳出循环

- `nil`

- `false`

```lua
if local val = foo!
    print val.name
```

### and or

```lua
local readin = request.get("https://example.com") or "Haha"
local res = try_something() and "success" or "fail"
```

### switch case

```lua
local c: String = switch b
    1           -> "1!"
    2           -> "2!"
    (@: String) -> @
    _           -> @ .. " as else"
```

## 循环

### for

```lua
for k, v in pairs mytable
    println f"{k}: {v}"

mytable \foreach { k, v } -> println f"{k}, {v}"
range(9) \foreach (i) -> println i
```

### while

```lua
local i = 10
while i > 8
    print "haha!"
    i = i - 1

while i > 4 do i = i - 1

i = i - 1 while i > 0
```

## 复合表达式

### 列表型复合表达式

```lua
local evens = [i for i in range(1, 101) when i % 2 == 0]
-- equivalent to:
local evens2 = range(1, 101)
    \filter (i) -> i % 2
    \to_list!
```

### 字典型复合表达式

```lua
local no_color = {k,v for k,v in pairs thing when k != "color"}
-- equivalent to:
local no_color2 = thing
    \filter {k,v} -> k != "color"
    \to_table!
```

## 抽象

### 面向对象

```lua
local { :class, :interface, :Impl } = require "luna.class"
local { :Required, :Static, :Final } = class -- tag concepts

local Animal = interface
    name:             Final Static "Animal" -- static variable
    weight:           Required Number
    say_weight:       (@: Impl) -> print @weight
    walk:             Required Function (@, step: Number) -> Number -- `Funcion` takes a lambda as a parameter, and calc the concept from it.

local Yellable = interface
    yell:             Required Function (@, step: Number) -> Any

local Dog = class
    extends:
        Animal:
            walk:     (@, step: Number): Number ->
                @current_step  = @current_step + step
                @current_step
        Yellable:
            yell:     (@) -> print "wolf!"
    current_step: 0
    jump: (@) -> print "dog jumped!"
    weight: Number
```

### 面向约束

约束范式的抽象更像鸭子类型, 基于 `concept`, 类比 `C++20` 的 `concept`

内置的约束一般采用首位大写, 为保留风格一致, 也建议用户自定义的约束 (或者元表含 `<concept>` 的变量) 采用一样的风格

#### 约束原语

- `Unit`

- `Number`

- `String`

- `Function`

- `Enum`

- `List`

- `Table`

##### 枚举约束

```lua
MyEnumConcept1 = Enum "male" | "female"
MyEnumConcept2 = Enum range 1, 101
```

##### 列表约束

```lua
MyListConcept1 = List           -- 相当于 List Any
MyListConcept2 = List Number
MyListConcept3 = List.of Number -- 相当于 List Number
```

##### 表约束

```lua
MyTableConcept = Table
    -- 普通键约束
    myvar:  Number
    -- 函数约束
    myfun:  (@, p1: String) -> Number
    -- 可选约束
    -- `Optional` 可以是 Optional.<call>: (c: Concept): Concept -> c | Nil
    myopt: Optional (@) -> @
```

#### 约束运算

`concept` 之间可以运算

```lua
C1 = List.of Number
C2 = Table
    name:   String
    gender: Enum "male" | "female"
    age:    Number
C3 = Function (@)
```

##### 组合

```lua
C4 = C1 + C2 + C3 -- 无交集, 等价于 Unit
C5 = C1 | C2 | C3 -- 只要满足 C1, C2, C3 任意其一就满足 C5
```

##### 检验

```lua
{1, 2, 3} is C1 -- true, 编译期可知
{1, 2, 3} is C5 -- true
```

#### 约束与对象

事实上 luna 的[面向对象](#面向对象)也是用 `concept` + [元表](#元表)模拟的

```lua
interface: (@spec: Table) ->
    <concept>: Table { k, v for k, v in spec when v is Concept }

class: {
    from: Optional List.of interface
} ->
    <concept>:

```

## 错误处理

### try-catch

相当于 Yuescript 的 `try?`

```lua
try foo 1, 2, 3

local result = try foo 1, 2, 3 catch (@: Except) -> print @

try
    foo 1, 2, 3
catch e
    print e
```

### expected

### 空安全

## 编译期运算

1. luna 认为满足以下*任一*条件的变量是 **编译期变量**

   - 数字字面量

   - 字符串字面量

   - [约束 `concept`](#面向约束)

   - [函数字面量](#函数字面量)

   - 函数的编译期调用结果

2. luna 认为满足以下*所有*条件的函数调用是 **函数的编译期调用**

   - 所有参数都是编译期变量

   - 不捕获任何外部变量

3. luna 认为所有函数默认在*编译期调用*, 不满足编译期调用条件的函数调用为运行期调用

4. 函数返回结果类型约束

   - 编译期调用

     - 未指定返回类型约束时为原变量的等价约束

     - 指定返回类型约束时则为指定约束

   - 运行期调用

     - 未指定返回类型约束时为 `Any`

     - 指定返回类型约束时则为指定约束

## 反射

- [ ] TODO:

## 宏

- [ ] TODO:

## 互操作

### luna as hosted

详见 libluna 规范

### luna as host

- [ ] TODO:

#### dll

```lua
local dll = require "luna.interop.dll"
```

#### ffi

```lua
local ffi = require "luna.interop.ffi"
```

#### com

```lua
local com = require "luna.interop.com"
```

#### lua

```lua
local lua = require "luna.lua"
```

## 异步

luna 的异步与并发完全由 host 定制. 当 luna self-host 时则用默认的 scheduler.

- [ ] TODO:

## 模块

## 包管理

用项目根目录下的 `package.luna` 描述包

该脚本返回一个符合 `luna.package.Package` 约束的 table 用于描述

```lua
local { :Package, :v } = require "luna.package"

Package "my_module_name.sub1.sub2"
    deps: {
        "lunum"
        "opengl"
        boost: -- ?
            version: (@) -> v"1.2.6" <= @ <= v"1.2.11"
            options:
                spirit: true
                python: true
    }
    options:
        op1:
            type:        Bool
            description: "just an op1"
        op2:
            type:        String
            description: "just an op2"
    scripts:
        dev: "echo dev"
        config: (...args) -> f"xmake config {f"{arg} " for arg in args}"
```

包管理器本地只保留包的 `package.luna` 文件,

模块 `luna.package` 可以大概实现如下

```lua
Version: Table
    major: Number
    minor: Number
    patch: Number

v: (version: String): Version ->
    local v = version\split by: "."
    return
        major: v[1]
        minor: v[2]
        patch: v[3]

Url:
    <concept>: Table
        source: String
        url: String

FIND_DIR:
    -- intrisics

Option:
    <concept>: Table
        name: String
        type: Concept

Dependency: Table
    name:     String
    info:
        version:  Optional Version
        configs:  Optional List.of Table.of String, Any
        required: Bool or true -- Concept.<or>: (@, defaultv: @) -> ConceptWithDefault @, defaultv

    <from>: (k: Number | String, dep: Table): Dependency ->
        switch k
            (@: Number) -> name: @
            (@: String) ->
                name: @
                info: dep



Package:
    <concept>:
        name: String
        deps: List.of Dependency
    <call>: {
        name: String
        deps: Table
    }: Package ->
        :name
        deps: Dependency.from dep for dep in pairs deps
```
