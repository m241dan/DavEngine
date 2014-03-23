/* header file for nanny.c written by Davenge */

struct nanny_data
{
   D_SOCKET *socket;
   void *content;
   const struct nanny_lib_entry *info;
   int state;
};

struct nanny_lib_entry
{
   const char *name;
   const char *const *nanny_messages;
   nanny_fun *const *nanny_code;
};

/* LIBRARY */
extern const struct nanny_lib_entry nanny_lib[];

/* NANNY LOGIN */
extern const char *const nanny_login_messages[];
extern nanny_fun *const nanny_login_code[];

nanny_fun nanny_login;
nanny_fun nanny_password;

/* NANNY NEW ACCOUNT */
extern const char *const nanny_new_account_messages[];
extern nanny_fun *nanny_new_account_code[];

nanny_fun nanny_new_password;
nanny_fun nanny_confirm_new_password;

/* NANNY SPECIFIC CODE */
/* creation */
NANNY_DATA *init_nanny( void );
int clear_nanny( NANNY_DATA *nanny );

/* deletion */
int free_nanny( NANNY_DATA *nanny );

/* input handling */
int handle_nanny_input( D_SOCKET *dsock, char *arg );

/* state handling */
int change_nanny_state( NANNY_DATA *nanny, int state, bool message );
int nanny_state_next( NANNY_DATA *nanny, bool message );
int nanny_state_prev( NANNY_DATA *nanny, bool message );

/* controlling */
int control_nanny( D_SOCKET *dsock, NANNY_DATA *nanny );
int uncontrol_nanny( D_SOCKET *dsock );

/* communication */
int text_to_nanny( NANNY_DATA *nanny, const char *fmt, ... );

/* retrieval */
const struct nanny_lib_entry *get_nanny_lib_from_name( const char *name );

