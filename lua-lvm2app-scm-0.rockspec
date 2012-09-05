#!/usr/bin/env lua

package	= 'lua-lvm2app'
version	= 'scm-0'
source	= {
	url	= 'https://github.com/morfoh/lua-lvm2app'
}
description	= {
	summary	= "Lua bindings for liblvm2app",
	detailed	= '',
	homepage	= 'https://github.com/morfoh/lua-lvm2app',
	license	= 'MIT',
	maintainer = "Christian Wiese",
}
dependencies = {
	'lua >= 5.1',
}
external_dependencies = {
	LVM2APP = {
		header = "lvm2app.h",
		library = "lvm2app",
	}
}
build	= {
	type = "builtin",
	modules = {
		lvm2app = {
			sources = { "src/pre_generated-lvm2app.nobj.c" },
			libraries = { "lvm2app" },
		}
	}
}
