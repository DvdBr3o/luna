set_group("examples")

function luna_example(name)
    target("examples." .. name)
        set_default(get_config("enable_examples"))
        set_kind("binary")
        set_languages("cxxlatest")
        add_deps("luna")
        add_files("src/**.cpp")
        add_headerfiles("src/(**.hpp)")
end

includes("basic")
includes("external_module")