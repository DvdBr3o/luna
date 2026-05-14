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