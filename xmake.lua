add_rules("mode.debug", "mode.release")

includes("xmake")

add_requires("mlir")

target("hello_mlir")
    set_languages("cxx20")
    add_rules("mlir.tblgen", {includedirs = {"src"}})

    set_runtimes("MT")

    add_packages("mlir")

    add_headerfiles("src/**.hpp")
    add_files("src/**.cpp")
    add_files("src/**.td")
    add_includedirs("src")

    after_build(function (target)
        os.rm(path.join(target:targetdir(), "public"))
        os.cp("public", path.join(target:targetdir(), "public"))
    end)

    if is_plat("windows") then
        add_syslinks("ntdll")
    end