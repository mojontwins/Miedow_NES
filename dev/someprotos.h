// This is ugly. Some code reorganization is due
// But not now.

void player_reset_movement (void);
void player_register_safe_spot (void);
void player_restore_safe_spot (void);
void containers_add (void);
void containers_draw (void);
void game_run_fire_script (void);
void enems_drain (void);

#ifdef ENABLE_PROPELLERS
void propellers_add (void);
#endif

#ifdef ENABLE_SPRINGS
void springs_add (void);
#endif

#ifdef ENABLE_ESTRUJATORS
void estrujators_add (void);
#endif

#ifdef ENABLE_CATARACTS
void cataracts_add (void);
#endif

#if defined (HOTSPOT_TYPE_KEY) || defined (ENABLE_TOUCHPLATES) || defined (ENABLE_LIGHTABLE)
void bolts_decrease_life (void);
#endif
