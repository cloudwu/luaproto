LUA_INC ?= -I/d/project/lua/src
LUA_LIB ?= -L/usr/local/bin -llua53 # -L/d/project/lua/src -llua

proto.dll : luaproto.c
	gcc -g -o $@ --shared $^ $(LUA_INC) $(LUA_LIB)

clean :
	rm proto.dll
