#include <lua.h>
#include <lauxlib.h>

#include <lstate.h>
#include <lobject.h>
#include <lfunc.h>

static int
lproto(lua_State *L) {
	const LClosure *c;
	if (lua_islightuserdata(L,1)) {
		c = lua_touserdata(L,1);
	} else {
		if (!lua_isfunction(L, 1) || lua_iscfunction(L,1))
			return 0;
		c = lua_topointer(L,1);
	}
	lua_pushlightuserdata(L, (void *)(c->p));
	lua_pushinteger(L, c->p->sizep);
	lua_pushinteger(L, c->p->sizek);
	return 3;
}

static int
lconstant(lua_State *L) {
	Proto *p;
	if (lua_islightuserdata(L,1)) {
		p = lua_touserdata(L,1);
	} else {
		if (!lua_isfunction(L, 1) || lua_iscfunction(L,1))
			return luaL_error(L, "Need lua function");
		const LClosure *c = lua_topointer(L,1);
		p = c->p;
	}
	int n = luaL_optinteger(L, 2, 0);
	if (n < 0 || n > p->sizek)
		return 0;
	luaL_checkstack(L, 1, NULL);
	lua_lock(L);
	setobj(L, L->top++, &p->k[n]);
	lua_unlock(L);
	return 1;
}

LUAMOD_API int
luaopen_proto(lua_State *L) {
	luaL_checkversion(L);
	luaL_Reg l[] = {
		{ "proto", lproto },
		{ "constant", lconstant },
		{ NULL, NULL },
	};
	luaL_newlib(L, l);
	return 1;
}
