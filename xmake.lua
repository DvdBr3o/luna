add_rules("mode.debug", "mode.release")

includes("vendor")

add_requires("mlir")
add_requires("pars main")

target("luna.td")
    set_kind("object")
    add_rules("mlir.tblgen", {includedirs = {"src", "src/Lua"}})
    add_rules("mlir.lsp")
    add_packages("mlir")
    add_files("src/**.td")

target("luna")
    set_languages("cxx20")
    set_kind("static")
    add_rules("mlir.precompiled")
    add_deps("luna.td")

    add_packages("mlir", {public = true})
    add_packages("pars", {public = true})

    add_headerfiles("src/(**.hpp)", {public = true})
    add_files("src/**.cpp|!src/main.cpp")
    add_includedirs("src", {public = true})

    after_build(function (target)
        os.rm(path.join(target:targetdir(), "public"))
        os.cp("public", path.join(target:targetdir(), "public"))
    end)

target("luna.cli")
    set_languages("cxx20")
    set_kind("binary")
    add_deps("luna")
    add_rules("mlir.precompiled")
    add_packages("mlir")
    add_files("src/**.cpp")

target("luna.lsp")
    set_languages("cxx20")
    set_kind("binary")
    add_rules("mlir.precompiled")
    add_deps("luna")
    add_packages("mlir")
    -- if is_plat("windows") then
    --     add_ldflags("/FORCE:MULTIPLE")
    -- end
    add_files("tools/lsp.cpp")
    
