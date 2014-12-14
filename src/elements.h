/* header file for the elements library writte by Davenge */

#define COMP_OWNER_NONE     0
#define COMP_OWNER_ELEMENT  1
#define COMP_OWNER_FRAME    2
#define COMP_OWNER_INSTANCE 3

extern LLIST *element_frameworks;

struct element_framework
{
   char *name;
   LLIST *strong_against;
   LLIST *weak_against;
   LLIST *composition;
};

struct composition
{
   void *owner;
   int ownertype;
   ELEMENT_FRAMEWORK *frame;
   int amount;
};

struct element_info
{
   ENTITY_INSTANCE *owner;
   ELEMENT_FRAMEWORK *frame;
   int pen;
   int res;
   int potency;
};

/* creation | deletion */
ELEMENT_FRAMEWORK *init_element_frame( void );
void free_element_frame( ELEMENT_FRAMEWORK *element );

ELEMENT_INFO *init_element_info( void );
void free_element_info( ELEMENT_INFO *element );

COMPOSITION *init_composition( void );
void free_composition( COMPOSITION *comp );

/* utility */
void load_elements_table( void );
bool base_load_lua_element( ELEMENT_FRAMEWORK *eleframe, lua_State *L );
void load_elements_list( void );
void load_element( ELEMENT_FRAMEWORK *eleframe, lua_State *L );
void load_element_strengths( ELEMENT_FRAMEWORK *eleframe, lua_State *L );
void load_element_weaknesses( ELEMENT_FRAMEWORK *eleframe, lua_State *L );
void load_element_composition( ELEMENT_FRAMEWORK *eleframe, lua_State *L );
void reload_elements_table( void );

/* getter */
ELEMENT_FRAMEWORK *get_element_framework( const char *name );
bool get_element_from_lua_table( const char *name, lua_State *L );

/* setter */

/* action */
extern inline void add_composition_to_element( COMPOSITION *comp, ELEMENT_FRAMEWORK *eleframe );
void print_element_list( LLIST *list );
