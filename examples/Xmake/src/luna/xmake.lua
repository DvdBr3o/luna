add_requires("glfw")
add_requires("vcpkg::stdexec")
add_requires("glad ^2.0.0", configs = {
    configs = {
        mx = false,
    }
})

target("luna")
    set_kind("static")
    add_languages("cxx20")
    if is_plat("windows") then
        add_files(
            "src/windows/Specific.hpp",
            "src/windows/DxWrapper.hpp"
        )
    elseif is_plat("linux") then
        add_files("src/linux/Specific.hpp")
    end
    add_files(
        "src/Parser.cpp"
        "src/Lexer.cpp"
        "src/Expression.cpp"
    )
    add_headerfiles("src/**.hpp")
    add_pakcages("glfw", { public = true })
    add_pakcages("stdexec", { public = true })
    add_pakcages("glad", { public = true })
