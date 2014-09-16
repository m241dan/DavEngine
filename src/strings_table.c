#include "mud.h"

const char *const data_types[MAX_MEMORY_TYPE+1] = {
   "int", "char", "D_SOCKET",
   '\0' /* gandalf */
};

const char *const tag_table_strings[MAX_ID_HANDLER+1] = {
   "accounts", "workspaces", "entity_frameworks", "entity_instances", "projects",
   '\0'
};

const char *const tag_table_whereID[MAX_ID_HANDLER+1] = {
   "accountID", "workspaceID", "entityFrameworkID", "entityInstanceID", "projectID",
   '\0'
};

const char const tag_table_characters[MAX_ID_HANDLER+1] = {
   'a', 'w', 'f', 'i', 'p',
   '\0'
};

/* match from from given table */
int match_string_table( const char *string, const char *const string_table[] )
{
   int x;

   for( x = 0; string_table[x] != '\0'; x++ )
      if( !strcmp( string, string_table[x] ) )
         return x;

   return -1;
}

int match_string_table_no_case( const char *string, const char *const string_table[] )
{
   int x;

   for( x = 0; string_table[x] != '\0'; x++ )
      if( !strcasecmp( string, string_table[x] ) )
         return x;

   return -1;
}

const char *print_string_table( const char *const string_table[] )
{
   static char buf[MAX_BUFFER];
   int x = 0;

   if( !string_table[x] || string_table[x] == '\0' )
      return "empty table";

   mud_printf( buf, string_table[x] );

   for( x = 1; string_table[x] != '\0'; x++ )
   {
      strcat( buf, ", " );
      strcat( buf, string_table[x] );
   }

   return buf;

}
