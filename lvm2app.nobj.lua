-- make generated variable nicer.
-- set_variable_format "%s%d"
set_variable_format "%s"

c_module "lvm2app" {

-- enable FFI bindings support.
luajit_ffi = false,

-- load LVM2APP shared library.
ffi_load"lvm2app",

include "lvm2app.h",

subfiles {
"src/LVM.nobj.lua",
"src/VG.nobj.lua",
"src/LV.nobj.lua",
"src/PV.nobj.lua",
},
}

