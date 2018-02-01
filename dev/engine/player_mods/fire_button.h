// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Fire button

	// PAD B Stuff!
	// In order:
	// 1. containers
	// 2. scripting
	// 3. fire

	// If you are using "FIRE_SCRIPT_WITH_ANIMATION", well...
	// that's incompatible with PLAYER_CAN_FIRE. Unless you work it out.

	// For genital games with 1 button you *should* change PAD_B to PAD_A

#ifdef PLAYER_JUMPS
	if (pj == 0)
#endif
	{
		if (pad0 & PAD_B) {
#ifdef ENABLE_CONTAINERS
			commands_executed = containers_get = 0;
			if (!pfiring) {
				containers_do ();
#ifdef CONTAINERS_HAS_GOT_FLAG			
				flags [CONTAINERS_HAS_GOT_FLAG] = containers_get;
#endif
				if (containers_get) {
#ifdef FIRE_SCRIPT_WITH_ANIMATION
					player_reset_movement ();
					use_ct = 1;
#else
					rda = flags [PLAYER_INV_FLAG];
					flags [PLAYER_INV_FLAG] = flags [containers_get];
					flags [containers_get] = rda;
#endif
#ifdef CONTAINER_ACTION_STOPS_CHECKS
					pfiring = 1;
#endif
				}
			}
#endif

#ifdef SCRIPTING_ON
			if (!pfiring) {
#ifdef FIRE_SCRIPT_WITH_ANIMATION
				if (ppossee){
					player_reset_movement ();
					use_ct = 1;
				} 
#else
				game_run_fire_script ();
				if (commands_executed) pfiring = 1;
#endif
			}
#endif

#ifdef PLAYER_PUAS
			if (!pfiring) {
				sfx_play (SFX_SHOOT, SC_PLAYER);
				puas_create ();
			}
#endif

#ifdef PLAYER_PUSH_BOXES
			if (!pfiring) {			
				if (bsignal) {
					player_push_box ();
					pfiring = 1;
					bsignal = 0;
					pfixct_push = PUSHING_FRAMES;
				}
			}
#endif

#ifdef PLAYER_CAN_FIRE
			if (!pfiring) {
				// CUSTOM {
				if (!psleeping)
				// } END_OF_CUSTOM
				bullets_fire ();
#ifdef PLAYER_TURRET		
				pfixct_fire = FIRING_FRAMES;
#endif	
			}
#endif

#ifdef ENABLE_FABOLEES
			if (!pfiring) fabolee_new ();
#endif

			pfiring = 1;
		} else pfiring = 0;
	}
	