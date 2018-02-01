// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Evil tile reaction

	if (phit || pflickering) evil_tile_hith = evil_tile_hitv = 0;

	if (evil_tile_hith) {
		px = pcx;
		pvx = ADD_SIGN (-pvx, PLAYER_V_REBOUND_MULTI);
	}

	if (evil_tile_hitv) {
		py = pcy;
		pvy = ADD_SIGN (-pvy, PLAYER_V_REBOUND_MULTI);
	}

	if (evil_tile_hitv || evil_tile_hith) pwashit = 1; 
