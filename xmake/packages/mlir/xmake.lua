-- 1. 定义 MLIR 依赖包
package("mlir")
    on_install(function (package)
        import("lib.detect.find_tool")
        local python = assert(find_tool("python3") or find_tool("python"), "python not found!")

        os.vrunv(python.program, {
            "-m", "pip", "install",
            "mlir",
            "-f", "https://github.com/makslevental/mlir-wheels/releases/expanded_assets/latest",
            "-t", package:installdir(),
            "--upgrade"
        })

        package:add("includedirs", "mlir/include")
        package:add("linkdirs", "mlir/lib")
        package:add("bindirs", "mlir/bin")

        if package:is_plat("windows") then
            package:add("syslinks", "ntdll")
        end

        local libdir = path.join(package:installdir(), "mlir", "lib")
        local links = {}
        for _, libfile in ipairs(os.files(path.join(libdir, "*.lib"))) do
            local name = path.filename(libfile)
            local stem = path.basename(libfile)
            local is_cpp_mlir = stem:startswith("MLIR") and stem ~= "MLIR-C"
            local is_cpp_llvm = stem:startswith("LLVM") and stem ~= "LLVM-C"
            local is_capi = stem:startswith("MLIRCAPI")
            if (is_cpp_mlir or is_cpp_llvm) and not is_capi then
                table.insert(links, path.basename(name))
            end
        end
        package:add("linkdirs", libdir)
        for _, link in ipairs(links) do
            package:add("links", link)
        end
    end)

    on_load(function (package)
        local libdir = path.join(package:installdir(), "mlir", "lib")
        local links = {}
        for _, libfile in ipairs(os.files(path.join(libdir, "*.lib"))) do
            local name = path.filename(libfile)
            local stem = path.basename(libfile)
            local is_cpp_mlir = stem:startswith("MLIR") and stem ~= "MLIR-C"
            local is_cpp_llvm = stem:startswith("LLVM") and stem ~= "LLVM-C"
            local is_capi = stem:startswith("MLIRCAPI")
            if (is_cpp_mlir or is_cpp_llvm) and not is_capi then
                table.insert(links, path.basename(name))
            end
        end
        package:add("linkdirs", libdir)
        for _, link in ipairs(links) do
            package:add("links", link)
        end
    end)


-- 2. 预编译规则
rule("mlir.precompiled")
    add_deps("mlir.tblgen")
    on_load(function(target)
        target:set("runtimes", "MT")
        if is_plat("windows") then
            target:add("syslinks", "ntdll")
        end
    end)

-- 3. 核心 TableGen 规则
rule("mlir.tblgen")
    set_extensions(".td")

    on_load(function(target)
        target:add("packages", "mlir")
        -- 初始化数据容器
        if not target:data("mlir.tblgen.configs") then
            target:data_set("mlir.tblgen.configs", {})
        end
    end)

    on_build_file(function(target, sourcefile, opt)
        import("lib.detect.find_program")
        import("core.project.depend")
        import("utils.progress")

        local mlir_pkg = target:pkg("mlir")
        local installdir = mlir_pkg:installdir()
        
        -- 工具查找路径（保持健壮性）
        local search_paths = {
            path.join(installdir, "bin"),
            path.join(installdir, "mlir", "bin"),
            path.join(installdir, "site-packages", "mlir", "bin") 
        }
        
        local mlir_tblgen = find_program("mlir-tblgen", {paths = search_paths})
        if not mlir_tblgen then os.raise("mlir-tblgen not found!") end

        -- 任务分发（.op.td, .dialect.td 等）
        local tasks = {}
        local filename = path.filename(sourcefile)
        if filename:find("%.op%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-op-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-op-defs"})
        elseif filename:find("%.dialect%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-dialect-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-dialect-defs"})
        elseif filename:find("%.type%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-typedef-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-typedef-defs"})
        elseif filename:find("%.attr%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-attrdef-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-attrdef-defs"})
        elseif filename:find("%.enum%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-enum-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-enum-defs"})
        elseif filename:find("%.pass%.td$") then
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-pass-decls"})
        else
            table.insert(tasks, {suffix = ".h.inc",   action = "-gen-op-decls"})
            table.insert(tasks, {suffix = ".cpp.inc", action = "-gen-op-defs"})
        end

        -- 路径准备：确保全部使用绝对路径
        local extraconf = target:extraconf("rules", "mlir.tblgen")
        local user_includes = (extraconf and extraconf.includedirs) or {}
        local include_dirs = {
            path.absolute(path.join(installdir, "include")),
            path.absolute(path.join(installdir, "mlir", "include")),
            path.absolute(path.directory(sourcefile))
        }
        for _, dir in ipairs(user_includes) do table.insert(include_dirs, path.absolute(dir)) end

        local common_args = {}
        for _, dir in ipairs(include_dirs) do
            table.insert(common_args, "-I")
            table.insert(common_args, dir)
        end

        -- 收集数据：filepath 和分号分隔的 includes
        local configs = target:data("mlir.tblgen.configs")
        table.insert(configs, {
            filepath = path.absolute(sourcefile),
            includes = table.concat(include_dirs, ";")
        })
        target:data_set("mlir.tblgen.configs", configs)

        -- 增量编译逻辑
        depend.on_changed(function ()
            local program = type(mlir_tblgen) == "table" and mlir_tblgen.program or mlir_tblgen
            for _, task in ipairs(tasks) do
                local targetfile = path.join(path.directory(path.absolute(sourcefile)), path.basename(sourcefile) .. task.suffix)
                os.vrunv(program, table.join(common_args, {task.action, sourcefile, "-o", targetfile}))
                progress.show(opt.progress, "${color.build.target} generating %s", path.filename(targetfile))
            end
        end, {files = {sourcefile}})

        target:add("includedirs", path.directory(path.absolute(sourcefile)))
    end)

-- 4. PDLL 规则
rule("mlir.pdll")
    set_extensions(".pdll")
    on_load(function(target)
        target:add("packages", "mlir")
        if not target:data("mlir.pdll.configs") then
            target:data_set("mlir.pdll.configs", {})
        end
    end)

    on_build_file(function(target, sourcefile, opt)
        import("lib.detect.find_program")
        import("core.project.depend")
        import("utils.progress")

        local mlir_pkg = target:pkg("mlir")
        local installdir = mlir_pkg:installdir()
        local mlir_pdll = find_program("mlir-pdll", {paths = {path.join(installdir, "bin"), path.join(installdir, "mlir", "bin")}})
        
        if not mlir_pdll then os.raise("mlir-pdll not found!") end

        local include_dirs = {
            path.join(installdir, "include"),
            path.join(installdir, "mlir", "include"),
            path.directory(path.absolute(sourcefile))
        }
        
        -- 记录符合 MLIR LSP 格式的信息
        local configs = target:data("mlir.pdll.configs")
        table.insert(configs, {
            filepath = path.absolute(sourcefile),
            includes = table.concat(include_dirs, ";")
        })
        target:data_set("mlir.pdll.configs", configs)

        depend.on_changed(function ()
            local targetfile = sourcefile .. ".h.inc"
            local args = {}
            for _, dir in ipairs(include_dirs) do table.insert(args, "-I") table.insert(args, dir) end
            table.insert(args, sourcefile)
            table.insert(args, "-o")
            table.insert(args, targetfile)
            
            os.vrunv(type(mlir_pdll) == "table" and mlir_pdll.program or mlir_pdll, args)
            progress.show(opt.progress, "${color.build.target} generating %s", path.filename(targetfile))
        end, {files = {sourcefile}})
    end)

-- 5. 统一持久化 Hook (修复 YAML 格式)
rule("mlir.lsp")
    after_build(function (target)
        local function write_lsp_configs(target, data_key, output_name)
            local extraconf = target:extraconf("rules", "mlir.lsp") or {}
            extraconf.outputdir = extraconf.outputdir or "build"
            output_name = path.join(extraconf.outputdir, output_name)
            local configs = target:data(data_key)
            if not configs or #configs == 0 then return end

            local content = {}
            for _, item in ipairs(configs) do
                table.insert(content, "---")
                table.insert(content, string.format("  filepath: \"%s\"", item.filepath:gsub("\\", "/")))
                table.insert(content, string.format("  includes: \"%s\"", item.includes:gsub("\\", "/")))
            end

            local output_path = path.join(os.projectdir(), output_name)
            io.writefile(output_path, table.concat(content, "\n") .. "\n")
            cprint("${color.success}[mlir]: %s updated.", output_name)
        end
    
        write_lsp_configs(target, "mlir.tblgen.configs", "tablegen_compile_commands.yml")
        
        if target:data("mlir.pdll.configs") then
            write_lsp_configs(target, "mlir.pdll.configs", "pdll_compile_commands.yml")
        end
    end)
