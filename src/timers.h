/* header file for the timers.c library written by Davenge */

extern LLIST *timer_queue;
extern LLIST *paused_timer_queue;

typedef enum
{
   TIMER_NO_OWNER = -1, TIMER_MUD, TIMER_INSTANCE, TIMER_DAMAGE, MAX_TIMER_OWNER
} TIMER_OWNER_TYPES;

typedef enum
{
   TT_UNKNOWN = -1, TT_COOLDOWN, TT_DAMAGE, MAX_TT
} TIMER_TYPES;

struct timer
{
   void *owner;
   char owner_type;
   char *key;
   sh_int duration; /* total time this damage stays alive in pulses */
   sh_int frequency; /* when ( pcounter == frequency ) do damage */
   sh_int counter; /* inc every iteration, when ( pcounter == frequnecy ) pcounter = 0 */
   char *update_message;
   char *end_message;
   char timer_type;
   bool active;
};

#define CALC_SECONDS( duration ) ( (double)( (double)duration / PULSES_PER_SECOND ) )

/* creation */
TIMER *init_timer( void );
void free_timer( TIMER *timer );

void start_timer( TIMER *timer );
void pause_timer( TIMER *timer );
void end_timer( TIMER *timer );

/* setter */
void set_melee_timer( ENTITY_INSTANCE *instance, bool message );
void own_timer( TIMER *timer );
void unown_timer( TIMER *timer );

/* getters */

/* monitor */
void timer_monitor( void );

/* inlines */
/* setters */
extern inline void set_timer_owner( TIMER *timer, void *owner, TIMER_OWNER_TYPES type );

/* getters */
extern inline TIMER *get_timer( const char *key );
extern inline TIMER *get_mud_timer( const char *key );
extern inline TIMER *get_timer_from_list_by_key( const char *key, LLIST *list );
extern inline TIMER *get_timer_from_list_by_key_and_type( const char *key, TIMER_OWNER_TYPES type, LLIST *list );
#define get_active_timer( key ) ( get_timer_from_list_by_key( (key), timer_queue ) )
#define get_inactive_timer( key ) ( get_timer_from_list_by_key( (key), paused_timer_queue ) )
#define get_timer_from_instance( instance, key ) ( get_timer_from_list_by_key( (key), ((ENTITY_INSTANCE *)(instance))->timers ) )
#define get_timer_from_damage( damage ) ( ((DAMAGE *)(damage))->timer )

/* checkers */
extern inline int check_timer( const char *key );
extern inline int check_timer_instance( ENTITY_INSTANCE *instance, const char *key );
#define MELEE_KEY "melee attack"
#define MELEE_CD_MSG "You may attack again."
#define CHECK_MELEE( instance ) ( check_timer_instance( (instance), MELEE_KEY ) )
