/* specifications.c methods pertaining to specifications written by Davenge */

#include "mud.h"

const char *const spec_table[] = {
   "IsRoom",
   '\0' /* gandalf */
};


SPECIFICATION *init_specification( void )
{
   SPECIFICATION *spec;

   CREATE( spec, SPECIFICATION, 1 );
   if( clear_specification( spec ) != RET_SUCCESS )
   {
      bug( "%s: could not clear specification.", __FUNCTION__ );
      return NULL;
   }
   return spec;
}

int clear_specification( SPECIFICATION *spec )
{
   int ret = RET_SUCCESS;

   spec->type = -1;
   spec->value = -1;
   spec->owner = strdup( "null" );

   return ret;
}

int free_specification( SPECIFICATION *spec )
{
   int ret = RET_SUCCESS;

   FREE( spec->owner );
   FREE( spec);

   return ret;
}

int new_specification( SPECIFICATION *spec )
{
   int ret = RET_SUCCESS;

   if( spec->type <= -1 || !strcmp( spec->owner, "null" ) )
   {
      bug( "%s: trying to add invalid spec to database.", __FUNCTION__ );
      return RET_FAILED_OTHER;
   }

   if( !quick_query( "INSERT INTO live_specs VALUES( %d, %d, '%s' );", spec->type, spec->value, spec->owner ) )
      return RET_FAILED_OTHER;

   return ret;
}

int add_spec_to_framework( SPECIFICATION *spec, ENTITY_FRAMEWORK *frame )
{
   AttachToList( spec, frame->specifications );
   return RET_SUCCESS;
}

int load_specifications_to_list( LLIST *spec_list, const char *owner )
{
   SPECIFICATION *spec;
   MYSQL_RES *result;
   MYSQL_ROW row;

   int ret = RET_SUCCESS;

   if( !spec_list )
   {
      BAD_POINTER( "spec_list" );
      return ret;
   }
   if( !owner || owner[0] == '\0' )
   {
      BAD_POINTER( "spec_list" );
      return ret;
   }

   if( !quick_query( "SELECT * FROM live_specs WHERE owner='%s';", owner ) )
      return RET_FAILED_OTHER;

   if( ( result = mysql_store_result( sql_handle ) ) == NULL )
      return RET_FAILED_OTHER;
   if( mysql_num_rows( result ) == 0 )
      return RET_DB_NO_ENTRY;

   while( ( row = mysql_fetch_row( result ) ) != NULL )
   {
      spec = init_specification();
      if ( db_load_spec( spec, &row ) != RET_SUCCESS )
      {
         free_specification( spec );
         continue;
      }
      AttachToList( spec, spec_list );
   }
   mysql_free_result( result );
   return RET_SUCCESS;
}

int db_load_spec( SPECIFICATION *spec, MYSQL_ROW *row )
{
   spec->type = atoi( (*row)[0] );
   spec->value = atoi( (*row)[1] );
   spec->owner = strdup( (*row)[2] );
   return RET_SUCCESS;
}

SPECIFICATION *spec_list_has_by_type( LLIST *spec_list, int type )
{
   SPECIFICATION *spec;
   ITERATOR Iter;

   AttachIterator( &Iter, spec_list );
   while( ( spec = (SPECIFICATION *)NextInList( &Iter ) ) != NULL )
      if( spec->type == type )
         break;
   DetachIterator( &Iter );

   if( spec )
      return spec;
   return NULL;
}
