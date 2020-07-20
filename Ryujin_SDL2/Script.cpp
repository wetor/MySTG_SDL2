#include "pch.h"
#include "Script.h"
#include "struct.h"
#include "Manager.h"

void Script::Open(const char* filename) {
	L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "enemy", CreateEnemy);
	lua_register(L, "load_img", LoadImage);
	lua_register(L, "boss", CreateBoss);
	luaL_loadfile(L, filename); /*调入Lua脚本文件*/
}
void Script::Run() {
	lua_pcall(L, 0, 0, 0); /*执行Lua脚本*/
}
void Script::Close() {
	lua_close(L);       /*关闭句柄*/
}
//待Lua调用的C注册函数。
int Script::CreateEnemy(lua_State* L)
{
	//检查栈中的参数是否合法，1表示Lua调用时的第一个参数(从左到右)，依此类推。
	//如果Lua代码在调用时传递的参数不为number，该函数将报错并终止程序的执行。
	enemy_order_t temp;
	temp.cnt = (int)luaL_checknumber(L, 1);
	temp.pattern = (int)luaL_checknumber(L, 2);
	temp.knd = (int)luaL_checknumber(L, 3);
	temp.x = (float)luaL_checknumber(L, 4);
	temp.y = (float)luaL_checknumber(L, 5);
	temp.sp = (float)luaL_checknumber(L, 6);
	temp.bltime = (int)luaL_checknumber(L, 7);
	temp.blknd = (int)luaL_checknumber(L, 8);
	temp.col = (int)luaL_checknumber(L, 9);
	temp.hp = (int)luaL_checknumber(L, 10);
	temp.blknd2 = (int)luaL_checknumber(L, 11);
	temp.wait = (int)luaL_checknumber(L, 12);
	temp.item_n[0] = (int)luaL_checknumber(L, 13);
	temp.item_n[1] = (int)luaL_checknumber(L, 14);
	temp.item_n[2] = (int)luaL_checknumber(L, 15);
	temp.item_n[3] = (int)luaL_checknumber(L, 16);
	temp.item_n[4] = (int)luaL_checknumber(L, 17);
	temp.item_n[5] = (int)luaL_checknumber(L, 18);

	//Enemy::enemy_order.push_back(temp);
	enemy_order.push_back(temp);
	//将函数的结果压入栈中。如果有多个返回值，可以在这里多次压入栈中。
	lua_pushnumber(L, 1);
	//返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
	return 1;
}
int Script::CreateBoss(lua_State* L) {
	return 1;
}
int Script::LoadImage(lua_State* L)
{
	//检查栈中的参数是否合法，1表示Lua调用时的第一个参数(从左到右)，依此类推。
	//如果Lua代码在调用时传递的参数不为number，该函数将报错并终止程序的执行。
	image_t temp;
	string name = luaL_checklstring(L, 1, NULL);
	temp.width = (int)luaL_checknumber(L, 2);
	temp.height = (int)luaL_checknumber(L, 3);
	temp.surface = IMG_Load(luaL_checklstring(L, 4, NULL));
	temp.texture = NULL;
	image_map[name] = temp;
	//将函数的结果压入栈中。如果有多个返回值，可以在这里多次压入栈中。
	lua_pushnumber(L, 1);
	//返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
	return 1;
}
/*
int main() {
	Script::Open("../dat/script/load.lua");
	Script::Run();
	Script::Close();

	return 0;
}*/