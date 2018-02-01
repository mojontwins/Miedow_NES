// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Initial checks.

	// Player state
	if (phit) phit --;
	if (pflickering) pflickering --;

#ifdef PLAYER_PUSH_BOXES
	if (bsignal != pad) bsignal = 0;
#endif	

#ifdef FIRE_SCRIPT_WITH_ANIMATION
	// Refine this with use_ct, guay_ct, etc.
	pad = 0;

	if (use_ct) {
		psprid = CELL_USE_BASE + use_ct;
		if (fr_ct) fr_ct --; else {
			use_ct ++;
			if (use_ct == 7) {
				if (containers_get) {
					sfx_play (SFX_GET_ITEM, SC_LEVEL);
					if (flags [PLAYER_INV_FLAG] != flags [containers_get]) {
						rda = flags [PLAYER_INV_FLAG];
						flags [PLAYER_INV_FLAG] = flags [containers_get];
						flags [containers_get] = rda;
						commands_executed = 1;
					}
#ifdef CONTAINER_ACTION_STOPS_CHECKS
				} else {
#else
				}
				if (0 == commands_executed) {
#endif
					game_run_fire_script ();
				}
			}
			if (use_ct == 13 && !commands_executed) {
				use_ct = 0;
				pfacing = CELL_FACING_RIGHT;
				no_ct = ticks;
			}
			if (use_ct == 18) use_ct = 0;
			fr_ct = 6;
		}
	} else if (guay_ct) {
		guay_ct --;
		if (guay_ct == 0) pflickering = ticks;
	} else
#endif 

#ifdef PLAYER_PUSH_BOXES
	if (pfixct_push) { 
		pfixct_push --;
		pad = 0;
	} else 
#endif
	pad = pad0;

#ifdef PLAYER_TURRET
	if (pfixct_fire) pfixct_fire --;
	/*
	if ((pad0 & 0xf0) != prevpad) pfixct_fire = 0;
	prevpad = (pad0 & 0xf0);	
	*/
#endif

#ifdef ENABLE_HOLES
	if (pholed) {
		pad = 0;
		pholed --;
		if (pholed == 1) pwashit = 1;
	}
#endif	

#if defined (ENGINE_TYPE_CLASSIC)
	evil_tile_hit = 0;
#elif defined (ENGINE_TYPE_NEW_GENITAL)
	evil_tile_hitv = evil_tile_hith = 0;
#endif

#if defined (EVIL_TILE_MULTI) || defined (EVIL_TILE_CENTER)
	pcx = px; pcy = py;
#endif

