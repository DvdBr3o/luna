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
    end)
    
rule("mlir.tblgen")
    set_extensions(".td")

    on_build_file(function(target, sourcefile, opt)
        import("lib.detect.find_program")
        import("lib.detect.find_package")
        import("core.project.depend")
        import("utils.progress")

        local mlir_bindirs = {
            path.join(target:pkg("mlir"):installdir(), "bin"),
            path.join(target:pkg("mlir"):installdir(), "mlir", "bin"),
        }
    
        local mlir_tblgen = assert(find_program("mlir-tblgen", {paths = mlir_bindirs}), "mlir-tblgen not found!")

        local targetfile = path.join(path.directory(path.absolute(sourcefile)), path.basename(sourcefile) .. ".h.inc")

        local includedirs = target:extraconf("rules", "mlir.tblgen", "includedirs") or { "src" }

        print("targetfile:  %s", targetfile)

        local configs = {
            "-gen-op-decls",
            "-I", path.join(target:pkg("mlir"):installdir(), "include"),
            "-I", path.join(target:pkg("mlir"):installdir(), "mlir", "include"),
        }
        for _, dir in ipairs(includedirs) do
            table.insert(configs, "-I")
            table.insert(configs, includedirs)
        end
        table.insert(configs, sourcefile)
        table.insert(configs, "-o")
        table.insert(configs, targetfile)

        depend.on_changed(function ()
            os.vrunv(mlir_tblgen, {
                "-gen-op-decls",
                "-I", path.join(target:pkg("mlir"):installdir(), "include"),
                "-I", path.join(target:pkg("mlir"):installdir(), "mlir", "include"),
                "-I", includedirs,
                sourcefile, 
                "-o", targetfile,
            })
            progress.show(opt.progress, "${color.build.target} generating %s", targetfile)
        end, {files = {sourcefile}})

        target:add("headerfiles", targetfile)
        target:add("includedirs", path.directory(path.absolute(targetfile)))
    end)