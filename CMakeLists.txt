#
# Lua bindings for liblvm2app
#
cmake_minimum_required(VERSION 2.8)

project(lua-lvm2app C)

set(BUILD_SHARED_LIBS TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(INSTALL_CMOD share/lua/cmod CACHE PATH "Directory to install Lua binary modules (configure lua via LUA_CPATH)")

set(COMMON_CFLAGS "${CFLAGS}")
set(COMMON_LDFLAGS)
set(COMMON_LIBS)

## Lua 5.1.x
include(FindLua51)
if(NOT ${LUA51_FOUND})
    message(FATAL_ERROR "The FindLua51 module could not find lua :-(")
endif()
set(COMMON_LIBS "${COMMON_LIBS};${LUA_LIBRARIES}")

## LibLvm2app
include(FindPkgConfig)
pkg_search_module(LVM2APP REQUIRED lvm2app)
set(COMMON_CFLAGS "${COMMON_CFLAGS} ${LVM2APP_CFLAGS}")
set(COMMON_LDFLAGS "${COMMON_LDFLAGS} ${LVM2APP_LDFLAGS}")
set(COMMON_LIBS "${COMMON_LIBS};${LVM2APP_LIBRARIES}")

## LuaNativeObjects
include(LuaNativeObjects)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${LUA_INCLUDE_DIR})

## LuaLvm2app
set(LUA_LVM2APP_SRC
	lvm2app.nobj.lua
)

if(${USE_PRE_GENERATED_BINDINGS})
	set(LUA_LVM2APP_SRC src/pre_generated-lvm2app.nobj.c)
else()
	# Generate Lua bindings.
	GenLuaNativeObjects(LUA_LVM2APP_SRC)
endif()

add_library(lua-lvm2app MODULE ${LUA_LVM2APP_SRC})
target_link_libraries(lua-lvm2app ${COMMON_LIBS})
set_target_properties(lua-lvm2app PROPERTIES PREFIX "")
set_target_properties(lua-lvm2app PROPERTIES COMPILE_FLAGS "${COMMON_CFLAGS}")
set_target_properties(lua-lvm2app PROPERTIES OUTPUT_NAME lvm2app)

install(TARGETS lua-lvm2app
        DESTINATION "${INSTALL_CMOD}")

