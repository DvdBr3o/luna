set_group("test")

add_requires("catch2")

function luna_test(name)
    target("test." .. name)
        set_default(get_config("enable_test"))
        set_kind("binary")
        set_languages("cxx20")
        add_deps("luna")
        add_packages("catch2")
        add_files(name .. ".cpp")
        add_headerfiles("(**.hpp)")
end

luna_test("basic")
