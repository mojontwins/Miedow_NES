// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Horizontal axis (Classic)

	// Poll pad
	
	if (pad & PAD_LEFT) {
	
#ifdef ENABLE_SLIPPERY
		if (pslips) {
			if (half_life) pvx --;
		} else
#endif
		pvx -= PLAYER_AX;
#ifdef ENABLE_WATER
		if (pwater) { if (pvx < -PLAYER_VX_MAX_SWIMMING) pvx = -PLAYER_VX_MAX_SWIMMING; } else
#endif
		if (pvx < -PLAYER_VX_MAX) pvx = -PLAYER_VX_MAX;
	
#ifdef PLAYER_GENITAL
		pfacinglast = pfacingh = CELL_FACING_LEFT;
#else
		pfacing = CELL_FACING_LEFT;
#endif
	} else if (pad & PAD_RIGHT) {
	
#ifdef ENABLE_SLIPPERY
		if (pslips) {
			if (half_life) pvx ++;
		} else
#endif
		pvx += PLAYER_AX;
#ifdef ENABLE_WATER
		if (pwater) { if (pvx > PLAYER_VX_MAX_SWIMMING) pvx = PLAYER_VX_MAX_SWIMMING; } else
#endif
		if (pvx > PLAYER_VX_MAX) pvx = PLAYER_VX_MAX;

	
#ifdef PLAYER_GENITAL		
		pfacinglast = pfacingh = CELL_FACING_RIGHT;		
#else
		pfacing = CELL_FACING_RIGHT;
#endif		
	} else {
#ifdef PLAYER_SPINS
		if (!pspin)
#endif

#ifdef ENABLE_HOLES
		if (!pholed)
#endif			
			if (pvx > 0) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx --;
			} else
#endif
				pvx -= PLAYER_RX; 
				if (pvx < 0) pvx = 0;
			} else if (pvx < 0) {
#ifdef ENABLE_SLIPPERY
			if (pslips) {
				if (half_life) pvx ++;
			} else
#endif
				pvx += PLAYER_RX; 
				if (pvx > 0) pvx = 0;
			}
#ifdef PLAYER_GENITAL
		pfacingh = 0xff;
#endif		
	}

	// Move
	px += pvx;		
	if (pgotten) px += pgtmx;
	
	// Collision
	if (px < (4<<FIX_BITS)) prx = 4;
	else if (px > (244<<FIX_BITS)) prx = 244;
	else prx = px >> FIX_BITS;
	
#ifdef PLAYER_8_PIXELS
	cy1 = (pry + 6) >> 4;
#else
	cy1 = pry >> 4;
#endif
	cy2 = (pry + 15) >> 4;
	if (pvx + pgtmx) {
		if (pvx + pgtmx < 0) {
			cx1 = cx2 = prx >> 4;
			cm_two_points ();
#ifdef PLAYER_GENITAL
			if (IS_FLOOR (at1) || IS_FLOOR (at2))
#else			
			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2))
#endif
			{
				pvx = 0;
				prx = (cx1 + 1) << 4;
				px = prx << FIX_BITS;
#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { by0 = by1 = cy1; bx0 = cx1; bx1 = cx1 - 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { by0 = by1 = cy2; bx0 = cx2; bx1 = cx2 - 1; bsignal = pad; }
#endif				
			} else {

#ifdef ENABLE_HOLES
				if (!pholed && (IS_HOLE (at1) && IS_HOLE (at2))) player_holed ();
#endif

#ifdef EVIL_TILE_MULTI
#ifdef PLAYER_SMALLER_ETCB
				cy1 = (pry + PLAYER_ETCB_UP) >> 4;
				cy2 = (pry + PLAYER_ETCB_DOWN) >> 4;
				cx1 = cx2 = (prx + PLAYER_ETCB_LEFT) >> 4;
				cm_two_points (); 
#endif
				if (IS_EVIL (at1) || IS_EVIL (at2)) {
					pvx = PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif
			}
		} else /*if (pvx + pgtmx > 0) */ {
			cx1 = cx2 = (prx + 7) >> 4; 
			cm_two_points (); 
#ifdef PLAYER_GENITAL
			if (IS_FLOOR (at1) || IS_FLOOR (at2)) 
#else
	 		if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2))
#endif
	 		{
				pvx = 0;
				prx = ((cx1 - 1) << 4) + 8;
				px = prx << FIX_BITS;
#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { by0 = by1 = cy1; bx0 = cx1; bx1 = cx1 + 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { by0 = by1 = cy2; bx0 = cx2; bx1 = cx2 + 1; bsignal = pad; }
#endif				
			} else {

#ifdef ENABLE_HOLES
				if (!pholed && (IS_HOLE (at1) && IS_HOLE (at2))) player_holed ();
#endif			

#ifdef EVIL_TILE_MULTI
#ifdef PLAYER_SMALLER_ETCB
				cy1 = (pry + PLAYER_ETCB_UP) >> 4;
				cy2 = (pry + PLAYER_ETCB_DOWN) >> 4;
				cx1 = cx2 = (prx + PLAYER_ETCB_RIGHT) >> 4;
				cm_two_points (); 
#endif
				if (IS_EVIL (at1) || IS_EVIL (at2)) {
					pvx = -PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif
			}
		}
#if defined (PLAYER_GENITAL) && defined (HOTSPOT_TYPE_KEY)
		if (IS_BOLT (at1)) { bx0 = cx1; by0 = cy1; player_push_bolt (); }
		if (IS_BOLT (at2)) { bx0 = cx2; by0 = cy2; player_push_bolt (); }
#endif		

	}

	// Solve facing
#ifdef PLAYER_GENITAL	
	if (pfacingv != 0xff) pfacing = pfacingv; else if (pfacingh != 0xff) pfacing = pfacingh;
#endif
