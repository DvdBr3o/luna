set_group("tests")

add_requires("catch2")

function luna_test(name)
    target("tests." .. name)
        set_default(get_config("enable_test"))
        set_kind("binary")
        set_languages("cxxlatest")
        add_deps("luna")
        add_packages("catch2")
        add_files(name .. ".cpp")
        add_headerfiles("(**.hpp)")
end

luna_test("basic")
luna_test("parse")
