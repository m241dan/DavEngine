/* header file for lua_instance.c written by Davenge */

int luaopen_EntityInstanceLib( lua_State *L );
int EntityInstanceGC( lua_State *L );

/* lib functions */

int getInstance( lua_State *L );
int luaNewInstance( lua_State *L );

/* meta methods */

/* getters */
int getName( lua_State *L );
int getShort( lua_State *L );
int getLong( lua_State *L );
int getDesc( lua_State *L );
int getID( lua_State *L );
int getLevel( lua_State *L);
int getItemFromInventory( lua_State *L );
int getSpec( lua_State *L );
int getInstanceFramework( lua_State *L );
int getContainer( lua_State *L );
int getVar( lua_State *L );
int getStatMod( lua_State *L );
int getStatPerm( lua_State *L );
int getStat( lua_State *L );
int getStatEffectiveValue( lua_State *L );
/* setters */
int setStatMod( lua_State *L );
int setStatPerm( lua_State *L );
int addStatMod( lua_State *L );
int addStatPerm( lua_State *L );
int setVar( lua_State *L );
int addSpec( lua_State *L );

/* bools */
int isLoaded( lua_State *L );
int isLive( lua_State *L );
int isBuilder( lua_State *L );
int isSameRoom( lua_State  *L );
int hasItemInInventoryFramework( lua_State *L );

/* actions */
int luaCallBack( lua_State *L );
int luaEntityInstanceInterp( lua_State *L );
int luaEntityInstanceTeleport( lua_State *L );
int luaEcho( lua_State *L );
int luaEchoAt( lua_State *L );
int luaEchoAround( lua_State *L );

/* iterators */
int luaEachInventory( lua_State *L );
int inv_iter( lua_State *L ); /* belongs to luaEachInventory */


/* later */
int getStat( lua_State *L );
