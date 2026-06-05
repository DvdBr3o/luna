package("pars")
    set_description("Vivid and powerful PEG parser in C++20.")
    set_license("MIT")

    add_deps(
        "range-v3",
        "tl_expected",
        "utfcpp",
        "fmt"
    )
    
    add_urls("https://github.com/DvdBr3o/pars.git")

    on_install(function (package)
        import("package.tools.xmake").install(package)
    end)
package_end()

add_requires("range-v3")
add_requires("tl_expected")
add_requires("utfcpp")
add_requires("fmt")

target("pars")
    set_languages("cxxlatest")
    set_kind("static")

    add_packages("range-v3", {public = true})
    add_packages("tl_expected", {public = true})
    add_packages("utfcpp", {public = true})
    add_packages("fmt", {public = true})

    add_headerfiles("src/(**.hpp)", {public = true})
    add_files("src/**.cpp", {public = true})
    add_includedirs("src", {public = true})
target_end()