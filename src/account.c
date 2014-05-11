/* account.c: methods pertaining to accounts written by Davenge */

#include "mud.h"

/* creation */

ACCOUNT_DATA *init_account( void )
{
   ACCOUNT_DATA *account;

   CREATE( account, ACCOUNT_DATA, 1 );
   if( clear_account( account ) != RET_SUCCESS )
   {
      free_account( account );
      return NULL;
   }
   account->characters = AllocList();
   account->command_tables = AllocList();
   account->commands = AllocList();
   return account;
}

int clear_account( ACCOUNT_DATA *account )
{
   int ret = RET_SUCCESS;

   account->name = strdup( "new_account" );
   account->password = strdup( "new_password" );
   account->level = 1;
   account->pagewidth = DEFAULT_PAGEWIDTH;
   account->last_command = strdup( "none" );
   account->executing_command = NULL;

   return ret;
}

/* deletion */
int free_account( ACCOUNT_DATA *account )
{
   int ret = RET_SUCCESS;

   account->socket = NULL;
   FreeList( account->characters );
   account->characters = NULL;
   FreeList( account->command_tables );
   account->command_tables = NULL;
   FreeList( account->commands );
   account->commands = NULL;
   FREE( account->name );
   FREE( account->password );
   FREE( account->command_tables );
   FREE( account->commands );
   FREE( account->last_command );

   return ret;
}

/* i/o */
int load_account( ACCOUNT_DATA *account, const char *name )
{
   MYSQL_RES *result;
   MYSQL_ROW row;
   int num_row;
   char query[MAX_BUFFER];

   if( !check_sql() )
      return RET_NO_SQL;

   mud_printf( query, "SELECT * FROM accounts WHERE name='%s';", name );

   if( mysql_query( sql_handle, query ) )
   {
      report_sql_error( sql_handle );
      return RET_NO_SQL;
   }

   if( ( result = mysql_store_result( sql_handle ) ) == NULL )
   {
      report_sql_error( sql_handle );
      return RET_NO_SQL;
   }

   num_row = mysql_num_rows( result );
   if( num_row > 1 )
   {
      bug( "%s: Query for account %s turned up more than one entry...", __FUNCTION__, name );
      mysql_free_result( result );
      return RET_FAILED_OTHER;
   }
   else if( num_row == 0 )
   {
      mysql_free_result( result );
      return RET_DB_NO_ENTRY;
   }

   row = mysql_fetch_row( result );
   account->accountID = atoi( row[0] );
   account->name = strdup( row[1] );
   account->password = strdup( row[2] );
   account->level = atoi( row[3] );
   account->pagewidth = atoi( row[4] );


   mysql_free_result( result );
   return RET_SUCCESS;
}

int new_account( ACCOUNT_DATA *account )
{
   char query[MAX_BUFFER];
   int ret = RET_SUCCESS;

   if( !account )
   {
      BAD_POINTER( "account" );
      return ret;
   }

   mud_printf( query, "INSERT INTO accounts VALUES( %d, '%s', '%s', %d, %d );",
              account->accountID, account->name, account->password, account->level,
              account->pagewidth );

   if( mysql_query( sql_handle, query ) )
   {
      report_sql_error( sql_handle );
      return RET_FAILED_OTHER;
   }

   return ret;
}

int save_account( ACCOUNT_DATA *account )
{
   int ret = RET_SUCCESS;

   if( !account )
   {
      BAD_POINTER( "account" );
      return ret;
   }
   return ret;
}
int account_prompt( D_SOCKET *dsock )
{
   BUFFER *buf = buffer_new(MAX_BUFFER);
   int width = dsock->account->pagewidth;

   bprintf( buf, "/%s\\\r\n", print_header( "Account Menu", "-", width - 2 ) );
   print_commands( dsock->account->commands, buf, 0, dsock->account->pagewidth );
   bprintf( buf, "\\%s/\r\n", print_header( "End Menu", "-", width -2 ) );
   bprintf( buf, "What is your choice?: " );

   text_to_buffer( dsock, buf->data );
   buffer_free( buf );
   return RET_SUCCESS; 
}

ACCOUNT_DATA *check_account_reconnect(const char *act_name)
{
  ACCOUNT_DATA *account;
  ITERATOR Iter;

  AttachIterator(&Iter, account_list);
  while ((account = (ACCOUNT_DATA *) NextInList(&Iter)) != NULL)
  {
    if (!strcasecmp(account->name, act_name))
    {
      if (account->socket)
        close_socket(account->socket, TRUE);

      break;
    }
  }
  DetachIterator(&Iter);

  return account;
}

int text_to_account( ACCOUNT_DATA *account, const char *fmt, ... )
{
   va_list va;
   int res;
   char dest[MAX_BUFFER];

   va_start( va, fmt );
   res = vsnprintf( dest, MAX_BUFFER, fmt, va );
   va_end( va );

   if( res >= MAX_BUFFER -1 )
   {
      dest[0] = '\0';
      bug( "Overflow when attempting to format string for message." );
   }

   text_to_buffer( account->socket, dest );
   return res;
}


void account_quit( void *passed, char *arg )
{

}

void account_settings( void *passed, char *arg )
{
   ACCOUNT_DATA *account = (ACCOUNT_DATA *)passed;
   COMMAND *settings_command;

   if( ( settings_command = account->executing_command ) == NULL )
      return;

   if( settings_command->sub_commands )
   {
      free_command_list( settings_command->sub_commands );
      FreeList( settings_command->sub_commands );
      settings_command->sub_commands = NULL;
   }
   else
   {
      settings_command->sub_commands = AllocList();
      load_commands( settings_command->sub_commands, settings_sub_commands, account->level );
   }
   text_to_account( account, "Settings Opened.\r\n" );
   return;
}

void set_pagewidth( void *passed, char *arg )
{

}
