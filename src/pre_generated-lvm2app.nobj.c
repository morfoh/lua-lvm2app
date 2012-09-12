/***********************************************************************************************
************************************************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!! Warning this file was generated from a set of *.nobj.lua definition files !!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
************************************************************************************************
***********************************************************************************************/

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define REG_PACKAGE_IS_CONSTRUCTOR 0
#define REG_MODULES_AS_GLOBALS 0
#define REG_OBJECTS_AS_GLOBALS 0
#define OBJ_DATA_HIDDEN_METATABLE 1
#define USE_FIELD_GET_SET_METHODS 0
#define LUAJIT_FFI 0


#include "lvm2app.h"



#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#ifdef _MSC_VER
#define __WINDOWS__
#else
#if defined(_WIN32)
#define __WINDOWS__
#endif
#endif

#ifdef __WINDOWS__

/* for MinGW32 compiler need to include <stdint.h> */
#ifdef __GNUC__
#include <stdint.h>
#include <stdbool.h>
#else

/* define some standard types missing on Windows. */
#ifndef __INT32_MAX__
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#endif
#ifndef __INT64_MAX__
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
typedef int bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif

/* wrap strerror_s(). */
#ifdef __GNUC__
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) do { \
	strncpy((buf), strerror(errno), (buflen)-1); \
	(buf)[(buflen)-1] = '\0'; \
} while(0)
#endif
#else
#ifndef strerror_r
#define strerror_r(errno, buf, buflen) strerror_s((buf), (buflen), (errno))
#endif
#endif

#define FUNC_UNUSED

#define LUA_NOBJ_API __declspec(dllexport)

#else

#define LUA_NOBJ_API LUALIB_API

#include <stdint.h>
#include <stdbool.h>

#define FUNC_UNUSED __attribute__((unused))

#endif

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define assert_obj_type(type, obj) \
	assert(__builtin_types_compatible_p(typeof(obj), type *))
#else
#define assert_obj_type(type, obj)
#endif

void *nobj_realloc(void *ptr, size_t osize, size_t nsize);

void *nobj_realloc(void *ptr, size_t osize, size_t nsize) {
	(void)osize;
	if(0 == nsize) {
		free(ptr);
		return NULL;
	}
	return realloc(ptr, nsize);
}

#define obj_type_free(type, obj) do { \
	assert_obj_type(type, obj); \
	nobj_realloc((obj), sizeof(type), 0); \
} while(0)

#define obj_type_new(type, obj) do { \
	assert_obj_type(type, obj); \
	(obj) = nobj_realloc(NULL, 0, sizeof(type)); \
} while(0)

typedef struct obj_type obj_type;

typedef void (*base_caster_t)(void **obj);

typedef void (*dyn_caster_t)(void **obj, obj_type **type);

#define OBJ_TYPE_FLAG_WEAK_REF (1<<0)
#define OBJ_TYPE_SIMPLE (1<<1)
struct obj_type {
	dyn_caster_t    dcaster;  /**< caster to support casting to sub-objects. */
	int32_t         id;       /**< type's id. */
	uint32_t        flags;    /**< type's flags (weak refs) */
	const char      *name;    /**< type's object name. */
};

typedef struct obj_base {
	int32_t        id;
	base_caster_t  bcaster;
} obj_base;

typedef enum obj_const_type {
	CONST_UNKOWN    = 0,
	CONST_BOOLEAN   = 1,
	CONST_NUMBER    = 2,
	CONST_STRING    = 3
} obj_const_type;

typedef struct obj_const {
	const char      *name;    /**< constant's name. */
	const char      *str;
	double          num;
	obj_const_type  type;
} obj_const;

typedef enum obj_field_type {
	TYPE_UNKOWN    = 0,
	TYPE_UINT8     = 1,
	TYPE_UINT16    = 2,
	TYPE_UINT32    = 3,
	TYPE_UINT64    = 4,
	TYPE_INT8      = 5,
	TYPE_INT16     = 6,
	TYPE_INT32     = 7,
	TYPE_INT64     = 8,
	TYPE_DOUBLE    = 9,
	TYPE_FLOAT     = 10,
	TYPE_STRING    = 11
} obj_field_type;

typedef struct obj_field {
	const char      *name;  /**< field's name. */
	uint32_t        offset; /**< offset to field's data. */
	obj_field_type  type;   /**< field's data type. */
	uint32_t        flags;  /**< is_writable:1bit */
} obj_field;

typedef enum {
	REG_OBJECT,
	REG_PACKAGE,
	REG_META,
} module_reg_type;

typedef struct reg_impl {
	const char *if_name;
	const void *impl;
} reg_impl;

typedef struct reg_sub_module {
	obj_type        *type;
	module_reg_type req_type;
	const luaL_reg  *pub_funcs;
	const luaL_reg  *methods;
	const luaL_reg  *metas;
	const obj_base  *bases;
	const obj_field *fields;
	const obj_const *constants;
	const reg_impl  *implements;
	int             bidirectional_consts;
} reg_sub_module;

#define OBJ_UDATA_FLAG_OWN (1<<0)
#define OBJ_UDATA_FLAG_LOOKUP (1<<1)
#define OBJ_UDATA_LAST_FLAG (OBJ_UDATA_FLAG_LOOKUP)
typedef struct obj_udata {
	void     *obj;
	uint32_t flags;  /**< lua_own:1bit */
} obj_udata;

/* use static pointer as key to weak userdata table. */
static char obj_udata_weak_ref_key[] = "obj_udata_weak_ref_key";

/* use static pointer as key to module's private table. */
static char obj_udata_private_key[] = "obj_udata_private_key";

#if LUAJIT_FFI
typedef int (*ffi_export_func_t)(void);
typedef struct ffi_export_symbol {
	const char *name;
	union {
	void               *data;
	ffi_export_func_t  func;
	} sym;
} ffi_export_symbol;
#endif





static obj_type obj_types[] = {
#define obj_type_id_LVM 0
#define obj_type_LVM (obj_types[obj_type_id_LVM])
  { NULL, 0, OBJ_TYPE_SIMPLE, "LVM" },
#define obj_type_id_VG 1
#define obj_type_VG (obj_types[obj_type_id_VG])
  { NULL, 1, OBJ_TYPE_SIMPLE, "VG" },
#define obj_type_id_LV 2
#define obj_type_LV (obj_types[obj_type_id_LV])
  { NULL, 2, OBJ_TYPE_SIMPLE, "LV" },
#define obj_type_id_PV 3
#define obj_type_PV (obj_types[obj_type_id_PV])
  { NULL, 3, OBJ_TYPE_SIMPLE, "PV" },
  {NULL, -1, 0, NULL},
};


#if LUAJIT_FFI

/* nobj_ffi_support_enabled_hint should be set to 1 when FFI support is enabled in at-least one
 * instance of a LuaJIT state.  It should never be set back to 0. */
static int nobj_ffi_support_enabled_hint = 0;
static const char nobj_ffi_support_key[] = "LuaNativeObject_FFI_SUPPORT";
static const char nobj_check_ffi_support_code[] =
"local stat, ffi=pcall(require,\"ffi\")\n" /* try loading LuaJIT`s FFI module. */
"if not stat then return false end\n"
"return true\n";

static int nobj_check_ffi_support(lua_State *L) {
	int rc;
	int err;

	/* check if ffi test has already been done. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_rawget(L, LUA_REGISTRYINDEX);
	if(!lua_isnil(L, -1)) {
		rc = lua_toboolean(L, -1);
		lua_pop(L, 1);
		/* use results of previous check. */
		goto finished;
	}
	lua_pop(L, 1); /* pop nil. */

	err = luaL_loadbuffer(L, nobj_check_ffi_support_code,
		sizeof(nobj_check_ffi_support_code) - 1, nobj_ffi_support_key);
	if(0 == err) {
		err = lua_pcall(L, 0, 1, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Error when checking for FFI-support: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
		return 0;
	}
	/* check results of test. */
	rc = lua_toboolean(L, -1);
	lua_pop(L, 1); /* pop results. */
		/* cache results. */
	lua_pushstring(L, nobj_ffi_support_key);
	lua_pushboolean(L, rc);
	lua_rawset(L, LUA_REGISTRYINDEX);

finished:
	/* turn-on hint that there is FFI code enabled. */
	if(rc) {
		nobj_ffi_support_enabled_hint = 1;
	}

	return rc;
}

typedef struct {
	const char **ffi_init_code;
	int offset;
} nobj_reader_state;

static const char *nobj_lua_Reader(lua_State *L, void *data, size_t *size) {
	nobj_reader_state *state = (nobj_reader_state *)data;
	const char *ptr;

	(void)L;
	ptr = state->ffi_init_code[state->offset];
	if(ptr != NULL) {
		*size = strlen(ptr);
		state->offset++;
	} else {
		*size = 0;
	}
	return ptr;
}

static int nobj_try_loading_ffi(lua_State *L, const char *ffi_mod_name,
		const char *ffi_init_code[], const ffi_export_symbol *ffi_exports, int priv_table)
{
	nobj_reader_state state = { ffi_init_code, 0 };
	int err;

	/* export symbols to priv_table. */
	while(ffi_exports->name != NULL) {
		lua_pushstring(L, ffi_exports->name);
		lua_pushlightuserdata(L, ffi_exports->sym.data);
		lua_settable(L, priv_table);
		ffi_exports++;
	}
	err = lua_load(L, nobj_lua_Reader, &state, ffi_mod_name);
	if(0 == err) {
		lua_pushvalue(L, -2); /* dup C module's table. */
		lua_pushvalue(L, priv_table); /* move priv_table to top of stack. */
		lua_remove(L, priv_table);
		lua_pushvalue(L, LUA_REGISTRYINDEX);
		err = lua_pcall(L, 3, 0, 0);
	}
	if(err) {
		const char *msg = "<err not a string>";
		if(lua_isstring(L, -1)) {
			msg = lua_tostring(L, -1);
		}
		printf("Failed to install FFI-based bindings: %s\n", msg);
		lua_pop(L, 1); /* pop error message. */
	}
	return err;
}
#endif


typedef struct {
	void *impl;
	void *obj;
} obj_implement;

static FUNC_UNUSED void *obj_implement_luaoptional(lua_State *L, int _index, void **impl, char *if_name) {
	void *ud;
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	/* get the implements table for this interface. */
	lua_pushlightuserdata(L, if_name);
	lua_rawget(L, LUA_REGISTRYINDEX);

	/* get pointer to userdata value & check if it is a userdata value. */
	ud = (obj_implement *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* get the userdata's metatable */
		if(lua_getmetatable(L, _index)) {
			/* lookup metatable in interface table for this object's implementation of the interface. */
			lua_gettable(L, -2);
		} else {
			/* no metatable. */
			goto no_interface;
		}
#if LUAJIT_FFI
	} else if(nobj_ffi_support_enabled_hint) { /* handle cdata. */
		/* get cdata interface check function from interface table. */
		lua_getfield(L, -1, "cdata");
		if(lua_isfunction(L, -1)) {
			/* pass cdata to function, return value should be an implmentation. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			/* get pointer to cdata. */
			ud = (void *)lua_topointer(L, _index);
		} else {
			lua_pop(L, 1); /* pop non-function. */
			goto no_interface;
		}
#endif
	} else {
		goto no_interface;
	}

	if(!lua_isnil(L, -1)) {
		*impl = lua_touserdata(L, -1);
		lua_pop(L, 2); /* pop interface table & implementation. */
		/* object implements interface. */
		return ud;
	} else {
		lua_pop(L, 1); /* pop nil. */
	}
no_interface:
	lua_pop(L, 1); /* pop interface table. */
	return NULL;
}

static FUNC_UNUSED void *obj_implement_luacheck(lua_State *L, int _index, void **impl, char *type) {
	void *ud = obj_implement_luaoptional(L, _index, impl, type);
	if(ud == NULL) {
#define ERROR_BUFFER_SIZE 256
		char buf[ERROR_BUFFER_SIZE];
		snprintf(buf, ERROR_BUFFER_SIZE-1,"Expected object with %s interface", type);
		/* value doesn't implement this interface. */
		luaL_argerror(L, _index, buf);
	}
	return ud;
}

/* use static pointer as key to interfaces table. (version 1.0) */
static char obj_interfaces_table_key[] = "obj_interfaces<1.0>_table_key";

static void obj_get_global_interfaces_table(lua_State *L) {
	/* get global interfaces table. */
	lua_getfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	if(lua_isnil(L, -1)) {
		/* Need to create global interfaces table. */
		lua_pop(L, 1); /* pop nil */
		lua_createtable(L, 0, 4); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		/* store interfaces table in Lua registery. */
		lua_setfield(L, LUA_REGISTRYINDEX, obj_interfaces_table_key);
	}
}

static void obj_get_interface(lua_State *L, const char *name, int global_if_tab) {
	/* get a interface's implementation table */
	lua_getfield(L, global_if_tab, name);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil */
		/* new interface. (i.e. no object implement it yet.)
		 *
		 * create an empty table for this interface that will be used when an
		 * implementation is registered for this interface.
		 */
		lua_createtable(L, 0, 2); /* 0 size array part, small hash part. */
		lua_pushvalue(L, -1); /* dup table. */
		lua_setfield(L, global_if_tab, name); /* store interface in global interfaces table. */
	}
}

static int obj_get_userdata_interface(lua_State *L) {
	/* get the userdata's metatable */
	if(lua_getmetatable(L, 2)) {
		/* lookup metatable in interface table for the userdata's implementation of the interface. */
		lua_gettable(L, 1);
		if(!lua_isnil(L, -1)) {
			/* return the implementation. */
			return 1;
		}
	}
	/* no metatable or no implementation. */
	return 0;
}

static void obj_interface_register(lua_State *L, char *name, int global_if_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, name, global_if_tab);

	/* check for 'userdata' function. */
	lua_getfield(L, -1, "userdata");
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		/* add C function for getting a userdata's implementation. */
		lua_pushcfunction(L, obj_get_userdata_interface);
		lua_setfield(L, -2, "userdata");
	} else {
		/* already have function. */
		lua_pop(L, 1); /* pop C function. */
	}
	/* we are going to use a lightuserdata pointer for fast lookup of the interface's impl. table. */
	lua_pushlightuserdata(L, name);
	lua_insert(L, -2);
	lua_settable(L, LUA_REGISTRYINDEX);
}

static void obj_register_interfaces(lua_State *L, char *interfaces[]) {
	int i;
	int if_tab;
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(i = 0; interfaces[i] != NULL ; i++) {
		obj_interface_register(L, interfaces[i], if_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

static void obj_type_register_implement(lua_State *L, const reg_impl *impl, int global_if_tab, int mt_tab) {
	/* get the table of implementations for this interface. */
	obj_get_interface(L, impl->if_name, global_if_tab);

	/* register object's implement in the interface table. */
	lua_pushvalue(L, mt_tab);
	lua_pushlightuserdata(L, (void *)impl->impl);
	lua_settable(L, -3);

	lua_pop(L, 1); /* pop inteface table. */
}

static void obj_type_register_implements(lua_State *L, const reg_impl *impls) {
	int if_tab;
	int mt_tab;
	/* get absolute position of object's metatable. */
	mt_tab = lua_gettop(L);
	/* get global interfaces table. */
	obj_get_global_interfaces_table(L);
	if_tab = lua_gettop(L);

	for(; impls->if_name != NULL ; impls++) {
		obj_type_register_implement(L, impls, if_tab, mt_tab);
	}
	lua_pop(L, 1); /* pop global interfaces table. */
}

#ifndef REG_PACKAGE_IS_CONSTRUCTOR
#define REG_PACKAGE_IS_CONSTRUCTOR 1
#endif

#ifndef REG_MODULES_AS_GLOBALS
#define REG_MODULES_AS_GLOBALS 0
#endif

#ifndef REG_OBJECTS_AS_GLOBALS
#define REG_OBJECTS_AS_GLOBALS 0
#endif

#ifndef OBJ_DATA_HIDDEN_METATABLE
#define OBJ_DATA_HIDDEN_METATABLE 1
#endif

static FUNC_UNUSED obj_udata *obj_udata_toobj(lua_State *L, int _index) {
	obj_udata *ud;
	size_t len;

	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	/* verify userdata size. */
	len = lua_objlen(L, _index);
	if(len != sizeof(obj_udata)) {
		/* This shouldn't be possible */
		luaL_error(L, "invalid userdata size: size=%d, expected=%d", len, sizeof(obj_udata));
	}
	return ud;
}

static FUNC_UNUSED int obj_udata_is_compatible(lua_State *L, obj_udata *ud, void **obj, base_caster_t *caster, obj_type *type) {
	obj_base *base;
	obj_type *ud_type;
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(lua_rawequal(L, -1, -2)) {
		*obj = ud->obj;
		/* same type no casting needed. */
		return 1;
	} else {
		/* Different types see if we can cast to the required type. */
		lua_rawgeti(L, -2, type->id);
		base = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop obj_base or nil */
		if(base != NULL) {
			*caster = base->bcaster;
			/* get the obj_type for this userdata. */
			lua_pushliteral(L, ".type");
			lua_rawget(L, -3); /* type's metatable. */
			ud_type = lua_touserdata(L, -1);
			lua_pop(L, 1); /* pop obj_type or nil */
			if(base == NULL) {
				luaL_error(L, "bad userdata, missing type info.");
				return 0;
			}
			/* check if userdata is a simple object. */
			if(ud_type->flags & OBJ_TYPE_SIMPLE) {
				*obj = ud;
			} else {
				*obj = ud->obj;
			}
			return 1;
		}
	}
	return 0;
}

static FUNC_UNUSED obj_udata *obj_udata_luacheck_internal(lua_State *L, int _index, void **obj, obj_type *type, int not_delete) {
	obj_udata *ud;
	base_caster_t caster = NULL;
	/* make sure it's a userdata value. */
	ud = (obj_udata *)lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			if(obj_udata_is_compatible(L, ud, obj, &(caster), type)) {
				lua_pop(L, 2); /* pop both metatables. */
				/* apply caster function if needed. */
				if(caster != NULL && *obj != NULL) {
					caster(obj);
				}
				/* check object pointer. */
				if(*obj == NULL) {
					if(not_delete) {
						luaL_error(L, "null %s", type->name); /* object was garbage collected? */
					}
					return NULL;
				}
				return ud;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				*obj = *(void **)lua_topointer(L, _index);
				return ud;
			}
			lua_pop(L, 2);
		} else {
			lua_pop(L, 1);
		}
	}
	if(not_delete) {
		luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	}
	return NULL;
}

static FUNC_UNUSED void *obj_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	void *obj = NULL;
	if(lua_isnoneornil(L, _index)) {
		return obj;
	}
	obj_udata_luacheck_internal(L, _index, &(obj), type, 1);
	return obj;
}

static FUNC_UNUSED void *obj_udata_luadelete(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;
	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);
}

static FUNC_UNUSED void *obj_udata_luadelete_weak(lua_State *L, int _index, obj_type *type, int *flags) {
	void *obj;
	obj_udata *ud = obj_udata_luacheck_internal(L, _index, &(obj), type, 0);
	if(ud == NULL) return NULL;
	*flags = ud->flags;
	/* null userdata. */
	ud->obj = NULL;
	ud->flags = 0;
	/* clear the metatable in invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* remove object from weak table. */
	lua_pushlightuserdata(L, obj);
	lua_pushnil(L);
	lua_rawset(L, -3);
	return obj;
}

static FUNC_UNUSED void obj_udata_luapush_weak(lua_State *L, void *obj, obj_type *type, int flags) {
	obj_udata *ud;

	/* convert NULL's into Lua nil's. */
	if(obj == NULL) {
		lua_pushnil(L);
		return;
	}
	/* check for type caster. */
	if(type->dcaster) {
		(type->dcaster)(&obj, &type);
	}
	/* get objects weak table. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key);
	lua_rawget(L, LUA_REGISTRYINDEX); /* weak ref table. */
	/* lookup userdata instance from pointer. */
	lua_pushlightuserdata(L, obj);
	lua_rawget(L, -2);
	if(!lua_isnil(L, -1)) {
		lua_remove(L, -2);     /* remove objects table. */
		return;
	}
	lua_pop(L, 1);  /* pop nil. */

#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		lua_remove(L, -2);
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_pushinteger(L, flags);
		lua_call(L, 2, 1);
		return;
	}
#endif
	/* create new userdata. */
	ud = (obj_udata *)lua_newuserdata(L, sizeof(obj_udata));

	/* init. obj_udata. */
	ud->obj = obj;
	ud->flags = flags;
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	/* add weak reference to object. */
	lua_pushlightuserdata(L, obj); /* push object pointer as the 'key' */
	lua_pushvalue(L, -2);          /* push object's udata */
	lua_rawset(L, -4);             /* add weak reference to object. */
	lua_remove(L, -2);     /* remove objects table. */
}

/* default object equal method. */
static FUNC_UNUSED int obj_udata_default_equal(lua_State *L) {
	obj_udata *ud1 = obj_udata_toobj(L, 1);
	obj_udata *ud2 = obj_udata_toobj(L, 2);

	lua_pushboolean(L, (ud1->obj == ud2->obj));
	return 1;
}

/* default object tostring method. */
static FUNC_UNUSED int obj_udata_default_tostring(lua_State *L) {
	obj_udata *ud = obj_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p, flags=%d", ud->obj, ud->flags);
	lua_concat(L, 2);

	return 1;
}

/*
 * Simple userdata objects.
 */
static FUNC_UNUSED void *obj_simple_udata_toobj(lua_State *L, int _index) {
	void *ud;

	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud == NULL) {
		luaL_typerror(L, _index, "userdata"); /* is not a userdata value. */
	}
	return ud;
}

static FUNC_UNUSED void * obj_simple_udata_luacheck(lua_State *L, int _index, obj_type *type) {
	void *ud;
	/* make sure it's a userdata value. */
	ud = lua_touserdata(L, _index);
	if(ud != NULL) {
		/* check object type by comparing metatables. */
		if(lua_getmetatable(L, _index)) {
			lua_pushlightuserdata(L, type);
			lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
			if(lua_rawequal(L, -1, -2)) {
				lua_pop(L, 2); /* pop both metatables. */
				return ud;
			}
		}
	} else if(!lua_isnoneornil(L, _index)) {
		/* handle cdata. */
		/* get private table. */
		lua_pushlightuserdata(L, obj_udata_private_key);
		lua_rawget(L, LUA_REGISTRYINDEX); /* private table. */
		/* get cdata type check function from private table. */
		lua_pushlightuserdata(L, type);
		lua_rawget(L, -2);

		/* check for function. */
		if(!lua_isnil(L, -1)) {
			/* pass cdata value to type checking function. */
			lua_pushvalue(L, _index);
			lua_call(L, 1, 1);
			if(!lua_isnil(L, -1)) {
				/* valid type get pointer from cdata. */
				lua_pop(L, 2);
				return (void *)lua_topointer(L, _index);
			}
		}
	}
	luaL_typerror(L, _index, type->name); /* is not a userdata value. */
	return NULL;
}

static FUNC_UNUSED void * obj_simple_udata_luaoptional(lua_State *L, int _index, obj_type *type) {
	if(lua_isnoneornil(L, _index)) {
		return NULL;
	}
	return obj_simple_udata_luacheck(L, _index, type);
}

static FUNC_UNUSED void * obj_simple_udata_luadelete(lua_State *L, int _index, obj_type *type) {
	void *obj;
	obj = obj_simple_udata_luacheck(L, _index, type);
	/* clear the metatable to invalidate userdata. */
	lua_pushnil(L);
	lua_setmetatable(L, _index);
	return obj;
}

static FUNC_UNUSED void *obj_simple_udata_luapush(lua_State *L, void *obj, int size, obj_type *type)
{
	void *ud;
#if LUAJIT_FFI
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
	if(nobj_ffi_support_enabled_hint && lua_isfunction(L, -1)) {
		/* call special FFI "void *" to FFI object convertion function. */
		lua_pushlightuserdata(L, obj);
		lua_call(L, 1, 1);
		return obj;
	}
#endif
	/* create new userdata. */
	ud = lua_newuserdata(L, size);
	memcpy(ud, obj, size);
	/* get obj_type metatable. */
#if LUAJIT_FFI
	lua_insert(L, -2); /* move userdata below metatable. */
#else
	lua_pushlightuserdata(L, type);
	lua_rawget(L, LUA_REGISTRYINDEX); /* type's metatable. */
#endif
	lua_setmetatable(L, -2);

	return ud;
}

/* default simple object equal method. */
static FUNC_UNUSED int obj_simple_udata_default_equal(lua_State *L) {
	void *ud1 = obj_simple_udata_toobj(L, 1);
	size_t len1 = lua_objlen(L, 1);
	void *ud2 = obj_simple_udata_toobj(L, 2);
	size_t len2 = lua_objlen(L, 2);

	if(len1 == len2) {
		lua_pushboolean(L, (memcmp(ud1, ud2, len1) == 0));
	} else {
		lua_pushboolean(L, 0);
	}
	return 1;
}

/* default simple object tostring method. */
static FUNC_UNUSED int obj_simple_udata_default_tostring(lua_State *L) {
	void *ud = obj_simple_udata_toobj(L, 1);

	/* get object's metatable. */
	lua_getmetatable(L, 1);
	lua_remove(L, 1); /* remove userdata. */
	/* get the object's name from the metatable */
	lua_getfield(L, 1, ".name");
	lua_remove(L, 1); /* remove metatable */
	/* push object's pointer */
	lua_pushfstring(L, ": %p", ud);
	lua_concat(L, 2);

	return 1;
}

static int obj_constructor_call_wrapper(lua_State *L) {
	/* replace '__call' table with constructor function. */
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_replace(L, 1);

	/* call constructor function with all parameters after the '__call' table. */
	lua_call(L, lua_gettop(L) - 1, LUA_MULTRET);
	/* return all results from constructor. */
	return lua_gettop(L);
}

static void obj_type_register_constants(lua_State *L, const obj_const *constants, int tab_idx,
		int bidirectional) {
	/* register constants. */
	while(constants->name != NULL) {
		lua_pushstring(L, constants->name);
		switch(constants->type) {
		case CONST_BOOLEAN:
			lua_pushboolean(L, constants->num != 0.0);
			break;
		case CONST_NUMBER:
			lua_pushnumber(L, constants->num);
			break;
		case CONST_STRING:
			lua_pushstring(L, constants->str);
			break;
		default:
			lua_pushnil(L);
			break;
		}
		/* map values back to keys. */
		if(bidirectional) {
			/* check if value already exists. */
			lua_pushvalue(L, -1);
			lua_rawget(L, tab_idx - 3);
			if(lua_isnil(L, -1)) {
				lua_pop(L, 1);
				/* add value->key mapping. */
				lua_pushvalue(L, -1);
				lua_pushvalue(L, -3);
				lua_rawset(L, tab_idx - 4);
			} else {
				/* value already exists. */
				lua_pop(L, 1);
			}
		}
		lua_rawset(L, tab_idx - 2);
		constants++;
	}
}

static void obj_type_register_package(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list = type_reg->pub_funcs;

	/* create public functions table. */
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	lua_pop(L, 1);  /* drop package table */
}

static void obj_type_register_meta(lua_State *L, const reg_sub_module *type_reg) {
	const luaL_reg *reg_list;

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register functions */
		luaL_register(L, NULL, reg_list);
	}

	obj_type_register_constants(L, type_reg->constants, -1, type_reg->bidirectional_consts);

	/* register methods. */
	luaL_register(L, NULL, type_reg->methods);

	/* create metatable table. */
	lua_newtable(L);
	luaL_register(L, NULL, type_reg->metas); /* fill metatable */
	/* setmetatable on meta-object. */
	lua_setmetatable(L, -2);

	lua_pop(L, 1);  /* drop meta-object */
}

static void obj_type_register(lua_State *L, const reg_sub_module *type_reg, int priv_table) {
	const luaL_reg *reg_list;
	obj_type *type = type_reg->type;
	const obj_base *base = type_reg->bases;

	if(type_reg->req_type == REG_PACKAGE) {
		obj_type_register_package(L, type_reg);
		return;
	}
	if(type_reg->req_type == REG_META) {
		obj_type_register_meta(L, type_reg);
		return;
	}

	/* create public functions table. */
	reg_list = type_reg->pub_funcs;
	if(reg_list != NULL && reg_list[0].name != NULL) {
		/* register "constructors" as to object's public API */
		luaL_register(L, NULL, reg_list); /* fill public API table. */

		/* make public API table callable as the default constructor. */
		lua_newtable(L); /* create metatable */
		lua_pushliteral(L, "__call");
		lua_pushcfunction(L, reg_list[0].func); /* push first constructor function. */
		lua_pushcclosure(L, obj_constructor_call_wrapper, 1); /* make __call wrapper. */
		lua_rawset(L, -3);         /* metatable.__call = <default constructor> */

#if OBJ_DATA_HIDDEN_METATABLE
		lua_pushliteral(L, "__metatable");
		lua_pushboolean(L, 0);
		lua_rawset(L, -3);         /* metatable.__metatable = false */
#endif

		/* setmetatable on public API table. */
		lua_setmetatable(L, -2);

		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
	} else {
		/* register all methods as public functions. */
#if OBJ_DATA_HIDDEN_METATABLE
		lua_pop(L, 1); /* pop public API table, don't need it any more. */
		/* create methods table. */
		lua_newtable(L);
#endif
	}

	luaL_register(L, NULL, type_reg->methods); /* fill methods table. */

	luaL_newmetatable(L, type->name); /* create metatable */
	lua_pushliteral(L, ".name");
	lua_pushstring(L, type->name);
	lua_rawset(L, -3);    /* metatable['.name'] = "<object_name>" */
	lua_pushliteral(L, ".type");
	lua_pushlightuserdata(L, type);
	lua_rawset(L, -3);    /* metatable['.type'] = lightuserdata -> obj_type */
	lua_pushlightuserdata(L, type);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, LUA_REGISTRYINDEX);    /* REGISTRY[type] = metatable */

	/* add metatable to 'priv_table' */
	lua_pushstring(L, type->name);
	lua_pushvalue(L, -2); /* dup metatable. */
	lua_rawset(L, priv_table);    /* priv_table["<object_name>"] = metatable */

	luaL_register(L, NULL, type_reg->metas); /* fill metatable */

	/* add obj_bases to metatable. */
	while(base->id >= 0) {
		lua_pushlightuserdata(L, (void *)base);
		lua_rawseti(L, -2, base->id);
		base++;
	}

	obj_type_register_constants(L, type_reg->constants, -2, type_reg->bidirectional_consts);

	obj_type_register_implements(L, type_reg->implements);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3);               /* dup methods table */
	lua_rawset(L, -3);                  /* metatable.__index = methods */
#if OBJ_DATA_HIDDEN_METATABLE
	lua_pushliteral(L, "__metatable");
	lua_pushboolean(L, 0);
	lua_rawset(L, -3);                  /* hide metatable:
	                                       metatable.__metatable = false */
#endif
	lua_pop(L, 2);                      /* drop metatable & methods */
}

static FUNC_UNUSED int lua_checktype_ref(lua_State *L, int _index, int _type) {
	luaL_checktype(L,_index,_type);
	lua_pushvalue(L,_index);
	return luaL_ref(L, LUA_REGISTRYINDEX);
}

/* use static pointer as key to weak callback_state table. */
static char obj_callback_state_weak_ref_key[] = "obj_callback_state_weak_ref_key";

static FUNC_UNUSED void *nobj_get_callback_state(lua_State *L, int owner_idx, int size) {
	void *cb_state;

	lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		/* create weak table for callback_state */
		lua_newtable(L);               /* weak table. */
		lua_newtable(L);               /* metatable for weak table. */
		lua_pushliteral(L, "__mode");
		lua_pushliteral(L, "k");
		lua_rawset(L, -3);             /* metatable.__mode = 'k'  weak keys. */
		lua_setmetatable(L, -2);       /* add metatable to weak table. */
		lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
		lua_pushvalue(L, -2);          /* dup weak table. */
		lua_rawset(L, LUA_REGISTRYINDEX);  /* add weak table to registry. */
	}

	/* check weak table for callback_state. */
	lua_pushvalue(L, owner_idx); /* dup. owner as lookup key. */
	lua_rawget(L, -2);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil. */
		lua_pushvalue(L, owner_idx); /* dup. owner as lookup key. */
		/* create new callback state. */
		cb_state = lua_newuserdata(L, size);
		lua_rawset(L, -3);
		lua_pop(L, 1); /* pop <weak table> */
	} else {
		/* got existing callback state. */
		cb_state = lua_touserdata(L, -1);
		lua_pop(L, 2); /* pop <weak table>, <callback_state> */
	}

	return cb_state;
}

static FUNC_UNUSED void *nobj_delete_callback_state(lua_State *L, int owner_idx) {
	void *cb_state = NULL;

	lua_pushlightuserdata(L, obj_callback_state_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop nil.  no weak table, so there is no callback state. */
		return NULL;
	}
	/* get callback state. */
	lua_pushvalue(L, owner_idx); /* dup. owner */
	lua_rawget(L, -2);
	if(lua_isnil(L, -1)) {
		lua_pop(L, 2); /* pop <weak table>, nil.  No callback state for the owner. */
	} else {
		cb_state = lua_touserdata(L, -1);
		lua_pop(L, 1); /* pop <state> */
		/* remove callback state. */
		lua_pushvalue(L, owner_idx); /* dup. owner */
		lua_pushnil(L);
		lua_rawset(L, -3);
		lua_pop(L, 1); /* pop <weak table> */
	}

	return cb_state;
}



static char *obj_interfaces[] = {
  NULL,
};



#define obj_type_LVM_check(L, _index) \
	*((LVM *)obj_simple_udata_luacheck(L, _index, &(obj_type_LVM)))
#define obj_type_LVM_optional(L, _index) \
	*((LVM *)obj_simple_udata_luaoptional(L, _index, &(obj_type_LVM)))
#define obj_type_LVM_delete(L, _index) \
	*((LVM *)obj_simple_udata_luadelete(L, _index, &(obj_type_LVM)))
#define obj_type_LVM_push(L, obj) \
	obj_simple_udata_luapush(L, &(obj), sizeof(LVM), &(obj_type_LVM))

#define obj_type_VG_check(L, _index) \
	*((VG *)obj_simple_udata_luacheck(L, _index, &(obj_type_VG)))
#define obj_type_VG_optional(L, _index) \
	*((VG *)obj_simple_udata_luaoptional(L, _index, &(obj_type_VG)))
#define obj_type_VG_delete(L, _index) \
	*((VG *)obj_simple_udata_luadelete(L, _index, &(obj_type_VG)))
#define obj_type_VG_push(L, obj) \
	obj_simple_udata_luapush(L, &(obj), sizeof(VG), &(obj_type_VG))

#define obj_type_LV_check(L, _index) \
	*((LV *)obj_simple_udata_luacheck(L, _index, &(obj_type_LV)))
#define obj_type_LV_optional(L, _index) \
	*((LV *)obj_simple_udata_luaoptional(L, _index, &(obj_type_LV)))
#define obj_type_LV_delete(L, _index) \
	*((LV *)obj_simple_udata_luadelete(L, _index, &(obj_type_LV)))
#define obj_type_LV_push(L, obj) \
	obj_simple_udata_luapush(L, &(obj), sizeof(LV), &(obj_type_LV))

#define obj_type_PV_check(L, _index) \
	*((PV *)obj_simple_udata_luacheck(L, _index, &(obj_type_PV)))
#define obj_type_PV_optional(L, _index) \
	*((PV *)obj_simple_udata_luaoptional(L, _index, &(obj_type_PV)))
#define obj_type_PV_delete(L, _index) \
	*((PV *)obj_simple_udata_luadelete(L, _index, &(obj_type_PV)))
#define obj_type_PV_push(L, obj) \
	obj_simple_udata_luapush(L, &(obj), sizeof(PV), &(obj_type_PV))



typedef lvm_t LVM;

typedef vg_t VG;

typedef lv_t LV;

typedef pv_t PV;



/* method: init */
static int LVM__init__meth(lua_State *L) {
  size_t system_dir_len;
  const char * system_dir;
  LVM this;
  system_dir = luaL_optlstring(L,1,NULL,&(system_dir_len));
  this = lvm_init(system_dir);
  obj_type_LVM_push(L, this);
  return 1;
}

/* method: quit */
static int LVM__quit__meth(lua_State *L) {
  LVM this;
  this = obj_type_LVM_delete(L,1);
  lvm_quit(this);
  return 0;
}

/* method: config_reload */
static int LVM__config_reload__meth(lua_State *L) {
  LVM this;
  int rc_lvm_config_reload = 0;
  this = obj_type_LVM_check(L,1);
  rc_lvm_config_reload = lvm_config_reload(this);
  lua_pushinteger(L, rc_lvm_config_reload);
  return 1;
}

/* method: config_override */
static int LVM__config_override__meth(lua_State *L) {
  LVM this;
  size_t config_string_len;
  const char * config_string;
  int rc_lvm_config_override = 0;
  this = obj_type_LVM_check(L,1);
  config_string = luaL_checklstring(L,2,&(config_string_len));
  rc_lvm_config_override = lvm_config_override(this, config_string);
  lua_pushinteger(L, rc_lvm_config_override);
  return 1;
}

/* method: errno */
static int LVM__errno__meth(lua_State *L) {
  LVM this;
  int rc_lvm_errno = 0;
  this = obj_type_LVM_check(L,1);
  rc_lvm_errno = lvm_errno(this);
  lua_pushinteger(L, rc_lvm_errno);
  return 1;
}

/* method: errmsg */
static int LVM__errmsg__meth(lua_State *L) {
  LVM this;
  const char * rc_lvm_errmsg = NULL;
  this = obj_type_LVM_check(L,1);
  rc_lvm_errmsg = lvm_errmsg(this);
  lua_pushstring(L, rc_lvm_errmsg);
  return 1;
}

/* method: scan */
static int LVM__scan__meth(lua_State *L) {
  LVM this;
  int rc_lvm_scan = 0;
  this = obj_type_LVM_check(L,1);
  rc_lvm_scan = lvm_scan(this);
  lua_pushinteger(L, rc_lvm_scan);
  return 1;
}

/* method: vgname_from_pvid */
static int LVM__vgname_from_pvid__meth(lua_State *L) {
  LVM this;
  size_t pvid_len;
  const char * pvid;
  const char * rc_lvm_vgname_from_pvid = NULL;
  this = obj_type_LVM_check(L,1);
  pvid = luaL_checklstring(L,2,&(pvid_len));
  rc_lvm_vgname_from_pvid = lvm_vgname_from_pvid(this, pvid);
  lua_pushstring(L, rc_lvm_vgname_from_pvid);
  return 1;
}

/* method: vgname_from_device */
static int LVM__vgname_from_device__meth(lua_State *L) {
  LVM this;
  size_t device_len;
  const char * device;
  const char * rc_lvm_vgname_from_device = NULL;
  this = obj_type_LVM_check(L,1);
  device = luaL_checklstring(L,2,&(device_len));
  rc_lvm_vgname_from_device = lvm_vgname_from_device(this, device);
  lua_pushstring(L, rc_lvm_vgname_from_device);
  return 1;
}

/* method: open */
static int VG__open__meth(lua_State *L) {
  LVM lvm_handle;
  size_t vgname_len;
  const char * vgname;
  size_t mode_len;
  const char * mode;
  uint32_t flags;
  VG this;
  lvm_handle = obj_type_LVM_check(L,1);
  vgname = luaL_checklstring(L,2,&(vgname_len));
  mode = luaL_checklstring(L,3,&(mode_len));
  flags = luaL_checkinteger(L,4);
  this = lvm_vg_open(lvm_handle, vgname, mode, flags);
  obj_type_VG_push(L, this);
  return 1;
}

/* method: create */
static int VG__create__meth(lua_State *L) {
  LVM lvm_handle;
  size_t vgname_len;
  const char * vgname;
  VG this;
  lvm_handle = obj_type_LVM_check(L,1);
  vgname = luaL_checklstring(L,2,&(vgname_len));
  this = lvm_vg_create(lvm_handle, vgname);
  obj_type_VG_push(L, this);
  return 1;
}

/* method: close */
static int VG__close__meth(lua_State *L) {
  VG this;
  int rc_lvm_vg_close = 0;
  this = obj_type_VG_delete(L,1);
  rc_lvm_vg_close = lvm_vg_close(this);
  lua_pushinteger(L, rc_lvm_vg_close);
  return 1;
}

/* method: write */
static int VG__write__meth(lua_State *L) {
  VG this;
  int rc_lvm_vg_write = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_write = lvm_vg_write(this);
  lua_pushinteger(L, rc_lvm_vg_write);
  return 1;
}

/* method: remove */
static int VG__remove__meth(lua_State *L) {
  VG this;
  int rc_lvm_vg_remove = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_remove = lvm_vg_remove(this);
  lua_pushinteger(L, rc_lvm_vg_remove);
  return 1;
}

/* method: extend */
static int VG__extend__meth(lua_State *L) {
  VG this;
  size_t device_len;
  const char * device;
  int rc_lvm_vg_extend = 0;
  this = obj_type_VG_check(L,1);
  device = luaL_checklstring(L,2,&(device_len));
  rc_lvm_vg_extend = lvm_vg_extend(this, device);
  lua_pushinteger(L, rc_lvm_vg_extend);
  return 1;
}

/* method: reduce */
static int VG__reduce__meth(lua_State *L) {
  VG this;
  size_t device_len;
  const char * device;
  int rc_lvm_vg_reduce = 0;
  this = obj_type_VG_check(L,1);
  device = luaL_checklstring(L,2,&(device_len));
  rc_lvm_vg_reduce = lvm_vg_reduce(this, device);
  lua_pushinteger(L, rc_lvm_vg_reduce);
  return 1;
}

/* method: add_tag */
static int VG__add_tag__meth(lua_State *L) {
  VG this;
  size_t tag_len;
  const char * tag;
  int rc_lvm_vg_add_tag = 0;
  this = obj_type_VG_check(L,1);
  tag = luaL_checklstring(L,2,&(tag_len));
  rc_lvm_vg_add_tag = lvm_vg_add_tag(this, tag);
  lua_pushinteger(L, rc_lvm_vg_add_tag);
  return 1;
}

/* method: remove_tag */
static int VG__remove_tag__meth(lua_State *L) {
  VG this;
  size_t tag_len;
  const char * tag;
  int rc_lvm_vg_remove_tag = 0;
  this = obj_type_VG_check(L,1);
  tag = luaL_checklstring(L,2,&(tag_len));
  rc_lvm_vg_remove_tag = lvm_vg_remove_tag(this, tag);
  lua_pushinteger(L, rc_lvm_vg_remove_tag);
  return 1;
}

/* method: set_extent_size */
static int VG__set_extent_size__meth(lua_State *L) {
  VG this;
  uint32_t new_size;
  int rc_lvm_vg_set_extent_size = 0;
  this = obj_type_VG_check(L,1);
  new_size = luaL_checkinteger(L,2);
  rc_lvm_vg_set_extent_size = lvm_vg_set_extent_size(this, new_size);
  lua_pushinteger(L, rc_lvm_vg_set_extent_size);
  return 1;
}

/* method: is_clustered */
static int VG__is_clustered__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_is_clustered = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_is_clustered = lvm_vg_is_clustered(this);
  lua_pushinteger(L, rc_lvm_vg_is_clustered);
  return 1;
}

/* method: is_exported */
static int VG__is_exported__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_is_exported = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_is_exported = lvm_vg_is_exported(this);
  lua_pushinteger(L, rc_lvm_vg_is_exported);
  return 1;
}

/* method: is_partial */
static int VG__is_partial__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_is_partial = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_is_partial = lvm_vg_is_partial(this);
  lua_pushinteger(L, rc_lvm_vg_is_partial);
  return 1;
}

/* method: get_seqno */
static int VG__get_seqno__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_seqno = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_seqno = lvm_vg_get_seqno(this);
  lua_pushinteger(L, rc_lvm_vg_get_seqno);
  return 1;
}

/* method: get_uuid */
static int VG__get_uuid__meth(lua_State *L) {
  VG this;
  const char * rc_lvm_vg_get_uuid = NULL;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_uuid = lvm_vg_get_uuid(this);
  lua_pushstring(L, rc_lvm_vg_get_uuid);
  return 1;
}

/* method: get_name */
static int VG__get_name__meth(lua_State *L) {
  VG this;
  const char * rc_lvm_vg_get_name = NULL;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_name = lvm_vg_get_name(this);
  lua_pushstring(L, rc_lvm_vg_get_name);
  return 1;
}

/* method: get_size */
static int VG__get_size__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_size = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_size = lvm_vg_get_size(this);
  lua_pushinteger(L, rc_lvm_vg_get_size);
  return 1;
}

/* method: get_free_size */
static int VG__get_free_size__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_free_size = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_free_size = lvm_vg_get_free_size(this);
  lua_pushinteger(L, rc_lvm_vg_get_free_size);
  return 1;
}

/* method: get_extent_size */
static int VG__get_extent_size__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_extent_size = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_extent_size = lvm_vg_get_extent_size(this);
  lua_pushinteger(L, rc_lvm_vg_get_extent_size);
  return 1;
}

/* method: get_extent_count */
static int VG__get_extent_count__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_extent_count = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_extent_count = lvm_vg_get_extent_count(this);
  lua_pushinteger(L, rc_lvm_vg_get_extent_count);
  return 1;
}

/* method: get_free_extent_count */
static int VG__get_free_extent_count__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_free_extent_count = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_free_extent_count = lvm_vg_get_free_extent_count(this);
  lua_pushinteger(L, rc_lvm_vg_get_free_extent_count);
  return 1;
}

/* method: get_pv_count */
static int VG__get_pv_count__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_pv_count = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_pv_count = lvm_vg_get_pv_count(this);
  lua_pushinteger(L, rc_lvm_vg_get_pv_count);
  return 1;
}

/* method: get_max_pv */
static int VG__get_max_pv__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_max_pv = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_max_pv = lvm_vg_get_max_pv(this);
  lua_pushinteger(L, rc_lvm_vg_get_max_pv);
  return 1;
}

/* method: get_max_lv */
static int VG__get_max_lv__meth(lua_State *L) {
  VG this;
  uint64_t rc_lvm_vg_get_max_lv = 0;
  this = obj_type_VG_check(L,1);
  rc_lvm_vg_get_max_lv = lvm_vg_get_max_lv(this);
  lua_pushinteger(L, rc_lvm_vg_get_max_lv);
  return 1;
}

/* method: create_linear */
static int LV__create_linear__meth(lua_State *L) {
  VG vg;
  size_t name_len;
  const char * name;
  uint64_t size;
  LV this;
  vg = obj_type_VG_check(L,1);
  name = luaL_checklstring(L,2,&(name_len));
  size = luaL_checkinteger(L,3);
  this = lvm_vg_create_lv_linear(vg, name, size);
  obj_type_LV_push(L, this);
  return 1;
}

/* method: from_name */
static int LV__from_name__meth(lua_State *L) {
  VG vg;
  size_t name_len;
  const char * name;
  LV this;
  vg = obj_type_VG_check(L,1);
  name = luaL_checklstring(L,2,&(name_len));
  this = lvm_lv_from_name(vg, name);
  obj_type_LV_push(L, this);
  return 1;
}

/* method: from_uuid */
static int LV__from_uuid__meth(lua_State *L) {
  VG vg;
  size_t uuid_len;
  const char * uuid;
  LV this;
  vg = obj_type_VG_check(L,1);
  uuid = luaL_checklstring(L,2,&(uuid_len));
  this = lvm_lv_from_uuid(vg, uuid);
  obj_type_LV_push(L, this);
  return 1;
}

/* method: activate */
static int LV__activate__meth(lua_State *L) {
  LV this;
  int rc_lvm_lv_activate = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_activate = lvm_lv_activate(this);
  lua_pushinteger(L, rc_lvm_lv_activate);
  return 1;
}

/* method: deactivate */
static int LV__deactivate__meth(lua_State *L) {
  LV this;
  int rc_lvm_lv_deactivate = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_deactivate = lvm_lv_deactivate(this);
  lua_pushinteger(L, rc_lvm_lv_deactivate);
  return 1;
}

/* method: remove */
static int LV__remove__meth(lua_State *L) {
  LV this;
  int rc_lvm_vg_remove_lv = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_vg_remove_lv = lvm_vg_remove_lv(this);
  lua_pushinteger(L, rc_lvm_vg_remove_lv);
  return 1;
}

/* method: get_uuid */
static int LV__get_uuid__meth(lua_State *L) {
  LV this;
  const char * rc_lvm_lv_get_uuid = NULL;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_get_uuid = lvm_lv_get_uuid(this);
  lua_pushstring(L, rc_lvm_lv_get_uuid);
  return 1;
}

/* method: get_name */
static int LV__get_name__meth(lua_State *L) {
  LV this;
  const char * rc_lvm_lv_get_name = NULL;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_get_name = lvm_lv_get_name(this);
  lua_pushstring(L, rc_lvm_lv_get_name);
  return 1;
}

/* method: get_size */
static int LV__get_size__meth(lua_State *L) {
  LV this;
  uint64_t rc_lvm_lv_get_size = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_get_size = lvm_lv_get_size(this);
  lua_pushinteger(L, rc_lvm_lv_get_size);
  return 1;
}

/* method: is_active */
static int LV__is_active__meth(lua_State *L) {
  LV this;
  uint64_t rc_lvm_lv_is_active = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_is_active = lvm_lv_is_active(this);
  lua_pushinteger(L, rc_lvm_lv_is_active);
  return 1;
}

/* method: is_suspended */
static int LV__is_suspended__meth(lua_State *L) {
  LV this;
  uint64_t rc_lvm_lv_is_suspended = 0;
  this = obj_type_LV_check(L,1);
  rc_lvm_lv_is_suspended = lvm_lv_is_suspended(this);
  lua_pushinteger(L, rc_lvm_lv_is_suspended);
  return 1;
}

/* method: add_tag */
static int LV__add_tag__meth(lua_State *L) {
  LV this;
  size_t tag_len;
  const char * tag;
  int rc_lvm_lv_add_tag = 0;
  this = obj_type_LV_check(L,1);
  tag = luaL_checklstring(L,2,&(tag_len));
  rc_lvm_lv_add_tag = lvm_lv_add_tag(this, tag);
  lua_pushinteger(L, rc_lvm_lv_add_tag);
  return 1;
}

/* method: remove_tag */
static int LV__remove_tag__meth(lua_State *L) {
  LV this;
  size_t tag_len;
  const char * tag;
  int rc_lvm_lv_remove_tag = 0;
  this = obj_type_LV_check(L,1);
  tag = luaL_checklstring(L,2,&(tag_len));
  rc_lvm_lv_remove_tag = lvm_lv_remove_tag(this, tag);
  lua_pushinteger(L, rc_lvm_lv_remove_tag);
  return 1;
}

/* method: resize */
static int LV__resize__meth(lua_State *L) {
  LV this;
  uint64_t size;
  int rc_lvm_lv_resize = 0;
  this = obj_type_LV_check(L,1);
  size = luaL_checkinteger(L,2);
  rc_lvm_lv_resize = lvm_lv_resize(this, size);
  lua_pushinteger(L, rc_lvm_lv_resize);
  return 1;
}

/* method: from_name */
static int PV__from_name__meth(lua_State *L) {
  VG vg;
  size_t name_len;
  const char * name;
  PV this;
  vg = obj_type_VG_check(L,1);
  name = luaL_checklstring(L,2,&(name_len));
  this = lvm_pv_from_name(vg, name);
  obj_type_PV_push(L, this);
  return 1;
}

/* method: from_uuid */
static int PV__from_uuid__meth(lua_State *L) {
  VG vg;
  size_t uuid_len;
  const char * uuid;
  PV this;
  vg = obj_type_VG_check(L,1);
  uuid = luaL_checklstring(L,2,&(uuid_len));
  this = lvm_pv_from_uuid(vg, uuid);
  obj_type_PV_push(L, this);
  return 1;
}

/* method: get_uuid */
static int PV__get_uuid__meth(lua_State *L) {
  PV this;
  const char * rc_lvm_pv_get_uuid = NULL;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_uuid = lvm_pv_get_uuid(this);
  lua_pushstring(L, rc_lvm_pv_get_uuid);
  return 1;
}

/* method: get_name */
static int PV__get_name__meth(lua_State *L) {
  PV this;
  const char * rc_lvm_pv_get_name = NULL;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_name = lvm_pv_get_name(this);
  lua_pushstring(L, rc_lvm_pv_get_name);
  return 1;
}

/* method: get_mda_count */
static int PV__get_mda_count__meth(lua_State *L) {
  PV this;
  uint64_t rc_lvm_pv_get_mda_count = 0;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_mda_count = lvm_pv_get_mda_count(this);
  lua_pushinteger(L, rc_lvm_pv_get_mda_count);
  return 1;
}

/* method: get_dev_size */
static int PV__get_dev_size__meth(lua_State *L) {
  PV this;
  uint64_t rc_lvm_pv_get_dev_size = 0;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_dev_size = lvm_pv_get_dev_size(this);
  lua_pushinteger(L, rc_lvm_pv_get_dev_size);
  return 1;
}

/* method: get_size */
static int PV__get_size__meth(lua_State *L) {
  PV this;
  uint64_t rc_lvm_pv_get_size = 0;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_size = lvm_pv_get_size(this);
  lua_pushinteger(L, rc_lvm_pv_get_size);
  return 1;
}

/* method: get_free */
static int PV__get_free__meth(lua_State *L) {
  PV this;
  uint64_t rc_lvm_pv_get_free = 0;
  this = obj_type_PV_check(L,1);
  rc_lvm_pv_get_free = lvm_pv_get_free(this);
  lua_pushinteger(L, rc_lvm_pv_get_free);
  return 1;
}



static const luaL_reg obj_LVM_pub_funcs[] = {
  {"init", LVM__init__meth},
  {NULL, NULL}
};

static const luaL_reg obj_LVM_methods[] = {
  {"quit", LVM__quit__meth},
  {"config_reload", LVM__config_reload__meth},
  {"config_override", LVM__config_override__meth},
  {"errno", LVM__errno__meth},
  {"errmsg", LVM__errmsg__meth},
  {"scan", LVM__scan__meth},
  {"vgname_from_pvid", LVM__vgname_from_pvid__meth},
  {"vgname_from_device", LVM__vgname_from_device__meth},
  {NULL, NULL}
};

static const luaL_reg obj_LVM_metas[] = {
  {"__gc", LVM__quit__meth},
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_LVM_bases[] = {
  {-1, NULL}
};

static const obj_field obj_LVM_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_LVM_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_LVM_implements[] = {
  {NULL, NULL}
};

static const luaL_reg obj_VG_pub_funcs[] = {
  {"open", VG__open__meth},
  {"create", VG__create__meth},
  {NULL, NULL}
};

static const luaL_reg obj_VG_methods[] = {
  {"close", VG__close__meth},
  {"write", VG__write__meth},
  {"remove", VG__remove__meth},
  {"extend", VG__extend__meth},
  {"reduce", VG__reduce__meth},
  {"add_tag", VG__add_tag__meth},
  {"remove_tag", VG__remove_tag__meth},
  {"set_extent_size", VG__set_extent_size__meth},
  {"is_clustered", VG__is_clustered__meth},
  {"is_exported", VG__is_exported__meth},
  {"is_partial", VG__is_partial__meth},
  {"get_seqno", VG__get_seqno__meth},
  {"get_uuid", VG__get_uuid__meth},
  {"get_name", VG__get_name__meth},
  {"get_size", VG__get_size__meth},
  {"get_free_size", VG__get_free_size__meth},
  {"get_extent_size", VG__get_extent_size__meth},
  {"get_extent_count", VG__get_extent_count__meth},
  {"get_free_extent_count", VG__get_free_extent_count__meth},
  {"get_pv_count", VG__get_pv_count__meth},
  {"get_max_pv", VG__get_max_pv__meth},
  {"get_max_lv", VG__get_max_lv__meth},
  {NULL, NULL}
};

static const luaL_reg obj_VG_metas[] = {
  {"__gc", VG__close__meth},
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_VG_bases[] = {
  {-1, NULL}
};

static const obj_field obj_VG_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_VG_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_VG_implements[] = {
  {NULL, NULL}
};

static const luaL_reg obj_LV_pub_funcs[] = {
  {"create_linear", LV__create_linear__meth},
  {"from_name", LV__from_name__meth},
  {"from_uuid", LV__from_uuid__meth},
  {NULL, NULL}
};

static const luaL_reg obj_LV_methods[] = {
  {"activate", LV__activate__meth},
  {"deactivate", LV__deactivate__meth},
  {"remove", LV__remove__meth},
  {"get_uuid", LV__get_uuid__meth},
  {"get_name", LV__get_name__meth},
  {"get_size", LV__get_size__meth},
  {"is_active", LV__is_active__meth},
  {"is_suspended", LV__is_suspended__meth},
  {"add_tag", LV__add_tag__meth},
  {"remove_tag", LV__remove_tag__meth},
  {"resize", LV__resize__meth},
  {NULL, NULL}
};

static const luaL_reg obj_LV_metas[] = {
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_LV_bases[] = {
  {-1, NULL}
};

static const obj_field obj_LV_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_LV_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_LV_implements[] = {
  {NULL, NULL}
};

static const luaL_reg obj_PV_pub_funcs[] = {
  {"from_name", PV__from_name__meth},
  {"from_uuid", PV__from_uuid__meth},
  {NULL, NULL}
};

static const luaL_reg obj_PV_methods[] = {
  {"get_uuid", PV__get_uuid__meth},
  {"get_name", PV__get_name__meth},
  {"get_mda_count", PV__get_mda_count__meth},
  {"get_dev_size", PV__get_dev_size__meth},
  {"get_size", PV__get_size__meth},
  {"get_free", PV__get_free__meth},
  {NULL, NULL}
};

static const luaL_reg obj_PV_metas[] = {
  {"__tostring", obj_simple_udata_default_tostring},
  {"__eq", obj_simple_udata_default_equal},
  {NULL, NULL}
};

static const obj_base obj_PV_bases[] = {
  {-1, NULL}
};

static const obj_field obj_PV_fields[] = {
  {NULL, 0, 0, 0}
};

static const obj_const obj_PV_constants[] = {
  {NULL, NULL, 0.0 , 0}
};

static const reg_impl obj_PV_implements[] = {
  {NULL, NULL}
};

static const luaL_reg lvm2app_function[] = {
  {NULL, NULL}
};

static const obj_const lvm2app_constants[] = {
  {NULL, NULL, 0.0 , 0}
};



static const reg_sub_module reg_sub_modules[] = {
  { &(obj_type_LVM), REG_OBJECT, obj_LVM_pub_funcs, obj_LVM_methods, obj_LVM_metas, obj_LVM_bases, obj_LVM_fields, obj_LVM_constants, obj_LVM_implements, 0},
  { &(obj_type_VG), REG_OBJECT, obj_VG_pub_funcs, obj_VG_methods, obj_VG_metas, obj_VG_bases, obj_VG_fields, obj_VG_constants, obj_VG_implements, 0},
  { &(obj_type_LV), REG_OBJECT, obj_LV_pub_funcs, obj_LV_methods, obj_LV_metas, obj_LV_bases, obj_LV_fields, obj_LV_constants, obj_LV_implements, 0},
  { &(obj_type_PV), REG_OBJECT, obj_PV_pub_funcs, obj_PV_methods, obj_PV_metas, obj_PV_bases, obj_PV_fields, obj_PV_constants, obj_PV_implements, 0},
  {NULL, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0}
};





#if LUAJIT_FFI
static const ffi_export_symbol lvm2app_ffi_export[] = {
  {NULL, { NULL } }
};
#endif




static const luaL_Reg submodule_libs[] = {
  {NULL, NULL}
};



static void create_object_instance_cache(lua_State *L) {
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_rawget(L, LUA_REGISTRYINDEX);  /* check if weak table exists already. */
	if(!lua_isnil(L, -1)) {
		lua_pop(L, 1); /* pop weak table. */
		return;
	}
	lua_pop(L, 1); /* pop nil. */
	/* create weak table for object instance references. */
	lua_pushlightuserdata(L, obj_udata_weak_ref_key); /* key for weak table. */
	lua_newtable(L);               /* weak table. */
	lua_newtable(L);               /* metatable for weak table. */
	lua_pushliteral(L, "__mode");
	lua_pushliteral(L, "v");
	lua_rawset(L, -3);             /* metatable.__mode = 'v'  weak values. */
	lua_setmetatable(L, -2);       /* add metatable to weak table. */
	lua_rawset(L, LUA_REGISTRYINDEX);  /* create reference to weak table. */
}

LUA_NOBJ_API int luaopen_lvm2app(lua_State *L) {
	const reg_sub_module *reg = reg_sub_modules;
	const luaL_Reg *submodules = submodule_libs;
	int priv_table = -1;

	/* register interfaces */
	obj_register_interfaces(L, obj_interfaces);

	/* private table to hold reference to object metatables. */
	lua_newtable(L);
	priv_table = lua_gettop(L);
	lua_pushlightuserdata(L, obj_udata_private_key);
	lua_pushvalue(L, priv_table);
	lua_rawset(L, LUA_REGISTRYINDEX);  /* store private table in registry. */

	/* create object cache. */
	create_object_instance_cache(L);

	/* module table. */
#if REG_MODULES_AS_GLOBALS
	luaL_register(L, "lvm2app", lvm2app_function);
#else
	lua_newtable(L);
	luaL_register(L, NULL, lvm2app_function);
#endif

	/* register module constants. */
	obj_type_register_constants(L, lvm2app_constants, -1, 0);

	for(; submodules->func != NULL ; submodules++) {
		lua_pushcfunction(L, submodules->func);
		lua_pushstring(L, submodules->name);
		lua_call(L, 1, 0);
	}

	/* register objects */
	for(; reg->type != NULL ; reg++) {
		lua_newtable(L); /* create public API table for object. */
		lua_pushvalue(L, -1); /* dup. object's public API table. */
		lua_setfield(L, -3, reg->type->name); /* module["<object_name>"] = <object public API> */
#if REG_OBJECTS_AS_GLOBALS
		lua_pushvalue(L, -1);                 /* dup value. */
		lua_setglobal(L, reg->type->name);    /* global: <object_name> = <object public API> */
#endif
		obj_type_register(L, reg, priv_table);
	}

#if LUAJIT_FFI
	if(nobj_check_ffi_support(L)) {
		nobj_try_loading_ffi(L, "lvm2app.nobj.ffi.lua", lvm2app_ffi_lua_code,
			lvm2app_ffi_export, priv_table);
	}
#endif



	return 1;
}


