set_project("luna")
set_version("0.1.0")
set_description("A graceful script language.") -- TODO: amplify description

-- set_policy("compatibility.version", "3.0")
add_rules("mode.debug", "mode.release")

add_requires("spdlog")
add_requires("matchit")
add_requires("tl_expected")
-- add_requires("llvm 20.1.5", { system = false })
-- add_requires("llvm", {configs = {
--     mlir = true,
-- }})
add_requires("lua")
add_requires("mapbox_eternal")
add_requires("utfcpp")
add_requires("spdlog")

includes("xmake")

if is_plat("windows") then
    set_runtimes("MD")
end
    
target("luna")
    -- if not has_config("kind") then
    --     set_kind("phony")
    -- end 
    set_languages("cxx20")
    set_kind("binary")

    -- add_packages("boost_spirit", {public = true})
    add_packages("spdlog", {public = true})
    add_packages("matchit", {public = true})
    add_packages("tl_expected", {public = true})
    add_packages("lua", {public = true})
    add_packages("utfcpp", {public = true})
    add_packages("spdlog", {public = true})
    -- if is_mode("debug") then 
    --     add_packages("llvm", {
    --         public = true, 
    --         links = {
    --             "LLVMSupport",
    --             "LLVMFrontendOpenMP",
    --             "LLVMOption",
    --             "LLVMOrcJIT",
    --             "clangAST",
    --             "clangASTMatchers",
    --             "clangBasic",
    --             "clangDependencyScanning",
    --             "clangDriver",
    --             "clangFormat",
    --             "clangFrontend",
    --             "clangIndex",
    --             "clangLex",
    --             "clangSema",
    --             "clangSerialization",
    --             "clangTooling",
    --             "clangToolingCore",
    --             "clangToolingInclusions",
    --             "clangToolingInclusionsStdlib",
    --             "clangToolingSyntax",
    --     }})
    -- elseif is_mode("release") then 
    --     add_packages("llvm", {public = true})
    --     add_ldflags("-Wl,--gc-sections")
    -- end 
    -- add_packages("llvm", {public = true})
    add_packages("mapbox_eternal", {public = true})

    add_includedirs("src", {public = true})
    add_headerfiles("src/**.hpp")
    -- if is_kind("binary") then
        add_files("src/main.cpp")
    -- end

    add_defines("NOMINMAX", {public = true})
    -- add_ldflags("/NODEFAULTLIB:library", {force = true})
    -- add_ldflags("-nodefaultlib", {force = true})
    -- add_shflags("/NODEFAULTLIB:library", {force = true})
    -- add_shflags("-nodefaultlib", {force = true})
    