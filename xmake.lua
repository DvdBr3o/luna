add_rules("mode.debug", "mode.release")
set_encodings("utf-8")

option("enable_test")
    set_default(false)
    set_description("whether to enable test for luna.")
    set_showmenu(true)
option_end()

includes("vendor")
includes("test")

-- add_requires("pars main")
add_requires("libllvm", {
    configs = {},
})
add_requires("fmt")
add_requires("abseil")
add_requires("dylib")
add_requires("immer")

target("luna")
    set_languages("cxx20")
    set_kind("static")

    -- add_packages("pars", {public = true})
    add_deps("pars", {public = true})
    -- add_packages("libllvm", {public = true})
    add_packages("fmt", {public = true})
    add_packages("abseil", {public = true})
    add_packages("dylib", {public = true})
    add_packages("immer", {public = true})

    add_headerfiles("src/(**.hpp)", {public = true})
    add_files("src/**.cpp|!src/main.cpp")
    add_includedirs("src", {public = true})

    if is_plat("windows") then
        add_defines("LUNA_PLAT_WINDOWS")
    elseif is_plat("macosx") then
        add_defines("LUNA_PLAT_MACOS")
    elseif is_plat("linux") then
        add_defines("LUNA_PLAT_LINUX")
    end

    after_build(function (target)
        os.rm(path.join(target:targetdir(), "public"))
        os.cp("public", path.join(target:targetdir(), "public"))
    end)

target("luna.cli")
    set_languages("cxx20")
    set_kind("binary")
    add_deps("luna")
    add_files("src/**.cpp")
