package("llvm")
    if not has_config("ci") then
        set_policy("package.install_locally", true)
    end
    if has_config("llvm") then
        set_sourcedir(get_config("llvm"))
    else
        if has_config("release") then
            if is_plat("windows") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x64-windows-msvc-release-lto.7z")
                add_versions("20.1.5", "499b2e1e37c6dcccbc9d538cea5a222b552d599f54bb523adea8594d7837d02b")
            elseif is_plat("linux") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-release-lto.tar.xz")
                add_versions("20.1.5", "5ff442434e9c1fbe67c9c2bd13284ef73590aa984bb74bcdfcec4404e5074b70")
            elseif is_plat("macosx") then
                add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-release-lto.tar.xz")
                add_versions("20.1.5", "f1c16076e0841b9e40cf21352d6661c7167bf6a76fa646b0fcba67e05bec2e7c")
            end
        else
            if is_plat("windows") then
                if is_mode("debug") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x64-windows-msvc-release.7z")
                    add_versions("20.1.5", "499b2e1e37c6dcccbc9d538cea5a222b552d599f54bb523adea8594d7837d02b")
                elseif is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x64-windows-msvc-release-lto.7z")
                    add_versions("20.1.5", "0548c0e3f613d1ec853d493870e68c7d424d70442d144fb35b99dc65fc682918")
                end
            elseif is_plat("linux") then
                if is_mode("debug") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-debug.tar.xz")
                    add_versions("20.1.5", "c04dddbe1d43d006f1ac52db01ab1776b8686fb8d4a1d13f2e07df37ae1ed47e")
                elseif is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/$(version)/x86_64-linux-gnu-release.tar.xz")
                    add_versions("20.1.5", "5ff442434e9c1fbe67c9c2bd13284ef73590aa984bb74bcdfcec4404e5074b70")
                end
            elseif is_plat("macosx") then
                if is_mode("debug") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-debug.tar.xz")
                    add_versions("20.1.5", "743e926a47d702a89b9dbe2f3b905cfde5a06fb2b41035bd3451e8edb5330222")
                elseif is_mode("release") then
                    add_urls("https://github.com/clice-project/llvm-binary/releases/download/20.1.5/arm64-macosx-apple-release.tar.xz")
                    add_versions("20.1.5", "16f473e069d5d8225dc5f2cd513ae4a2161127385fd384d2a4737601d83030e7")
                end
            end
        end
    end

    if is_plat("linux", "macosx") then
        if is_mode("debug") then
            add_configs("shared", {description = "Build shared library.", default = true, type = "boolean", readonly = true})
        end
    end

    if is_plat("windows", "mingw") then
        add_syslinks("version", "ntdll")
    end

    on_install(function (package)
        if not package:config("shared") then
            package:add("defines", "CLANG_BUILD_STATIC")
        end

        os.vcp("bin", package:installdir())
        os.vcp("lib", package:installdir())
        os.vcp("include", package:installdir())
    end)