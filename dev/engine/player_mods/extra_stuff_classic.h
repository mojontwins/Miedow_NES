// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Extra stuff (Classic)
	
	// Hidden
#ifdef ENABLE_ESPECTROS
	cx1 = cx2 = (prx + 4) >> 4;
	cy1 = cy2 = (pry + 8) >> 4;
	cm_two_points ();
	phidden = (ABS (pvy) < PLAYER_VY_MIN) && (ABS (pvx) < PLAYER_VX_MIN) && (IS_HIDEOUT (at1));
#endif

	// Spinning

#ifdef PLAYER_SPINS
	if (!pvx && ppossee) pspin = 0;
#endif

	// Float

#ifdef PLAYER_FLOATS
	if (!ppossee && !pj && (pad0 & PAD_DOWN)) {
		if (!pfloat) pvy = 0;
		pfloat = 1;
	} else pfloat = 0;
#endif

	// Butt

#ifdef PLAYER_BUTT
	if (ppossee || phit 
#ifdef ENABLE_WATER
		|| pwater
#endif
	) pbutt = 0; else {
		if (pad & PAD_B) {
			if (!pbutt) {
				pbutt = 1; pj = 0;
				sfx_play (SFX_BUTT_FALL, SC_PLAYER);			
			}
		}
	}
#endif	

	// Hitter todo
	/*
	if ((pad & PAD_B) && !hitter_on && pstatespradder) {
		hitter_on = 1; hitter_frame = 0;
		sfx_play (SFX_SHOOT, SC_PLAYER);
	}
	*/
	