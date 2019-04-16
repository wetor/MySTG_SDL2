#pragma once
#include <lua.hpp>
#include <lua.h>  
#include <lualib.h>  


static lua_State *L; //创建一个解释器句柄= luaL_newstate();
class Script {
public:

	static void Open(const char* filename);
	static void Run();
	static void Close();
	//待Lua调用的C++注册函数。
	static int CreateEnemy(lua_State* L);
	static int CreateBoss(lua_State* L);

};