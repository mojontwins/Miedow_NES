// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Evil tile reaction

#ifdef ENABLE_EVIL_TILE

	if (evil_tile_hit) {
#ifdef PLAYER_SPINS
		pspin = 0;
#endif
#ifdef PLAYER_JUMPS
		pjustjumped = 0;
#endif

#ifdef EVIL_TILE_ON_FLOOR
		pvy = -PLAYER_V_REBOUND; 
#endif
#ifdef EVIL_TILE_MULTI
		px = pcx; py = pcy;
#endif
#if defined (EVIL_TILE_CENTER) && !defined (PLAYER_DIE_AND_RESPAWN)
		px = pcx; py = pcy;
#ifdef PLAYER_GENITAL
		if (phit) {
			pvx = pvy = 0;
		} else {
			pvy = ADD_SIGN (-pvy, PLAYER_V_REBOUND_MULTI);
			pvx = ADD_SIGN (-pvx, PLAYER_V_REBOUND_MULTI);
		}
#else		
		pvy = -PLAYER_V_REBOUND_MULTI;
#endif
#endif

		if (
#ifdef PLAYER_FLICKERS
		!pflickering
#else				
		!phit
#endif
		)
		pwashit = 1; 
	}
#endif	
	