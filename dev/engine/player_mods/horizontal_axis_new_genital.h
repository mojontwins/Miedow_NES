// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Horizontal axis (New Genital)

// The collision box for New Genital is rather small,
// Just 8x5 pixels, centered at the bottom of the player sprite.
// The "holed" detection is 1 pixel thick.

	// Poll pad

	if (
		(pad & PAD_LEFT)
#ifdef PLAYER_TURRET 
		&& (pfixct_fire == 0)
#endif
	) {
#ifdef ENABLE_SLIPPERY
		rda = pslips ? half_life : PLAYER_AX;
		pvx -= rda;
#else
		pvx -= PLAYER_AX;
#endif
		if (pvx < -PLAYER_VX_MAX) pvx = -PLAYER_VX_MAX;
		pfacinglast = pfacingh = CELL_FACING_LEFT;
	} else if (
		(pad & PAD_RIGHT)
#ifdef PLAYER_TURRET 
		&& (pfixct_fire == 0)
#endif
	) {
#ifdef ENABLE_SLIPPERY
		rda = pslips ? half_life : PLAYER_AX;
		pvx += rda;
#else
		pvx += PLAYER_AX;
#endif
		if (pvx > PLAYER_VX_MAX) pvx = PLAYER_VX_MAX;
		pfacinglast = pfacingh = CELL_FACING_RIGHT;
	} else {
#ifdef ENABLE_HOLES
		//if (!pholed)
#endif
		{
#ifdef ENABLE_SLIPPERY
			rda = pslips ? half_life : PLAYER_RX;
			if (pvx > 0) { pvx -= rda; if (pvx < 0) pvx = 0; }
			else 
			if (pvx < 0) { pvx += rda; if (pvx > 0) pvx = 0; }
#else
			if (pvx > 0) { pvx -= PLAYER_RX; if (pvx < 0) pvx = 0; }
			else 
			if (pvx < 0) { pvx += PLAYER_RX; if (pvx > 0) pvx = 0; }
#endif
		}

		pfacingh = 0xff;
	}

	// Move & limit

	px += pvx; if (pgotten) px += pgtmx;

	if (px < (4<<FIX_BITS)) prx = 4;
	else if (px > (244<<FIX_BITS)) prx = 244;
	else prx = px >> FIX_BITS;

	// Collision

	cy1 = (pry + 11) >> 4;
	cy2 = (pry + 15) >> 4;

	if (pvx + pgtmx) {
		if (pvx + pgtmx < 0) {

			// Leftmost border of the collision box
			cx1 = cx2 = prx >> 4;
			cm_two_points ();

			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2)) {
				pgotten = pvx = 0;
				prx = (cx1 + 1) << 4;
				px = prx << FIX_BITS;

#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { by0 = by1 = cy1; bx0 = cx1; bx1 = cx1 - 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { by0 = by1 = cy2; bx0 = cx2; bx1 = cx2 - 1; bsignal = pad; }
#endif					
			}

		} else {

			// Rightmost border of the collision box
			cx1 = cx2 = (prx + 7) >> 4;
			cm_two_points ();

			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2)) {
				pgotten = pvx = 0;
				prx = (cx1 << 4) - 8;
				px = prx << FIX_BITS;

#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { by0 = by1 = cy1; bx0 = cx1; bx1 = cx1 + 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { by0 = by1 = cy2; bx0 = cx2; bx1 = cx2 + 1; bsignal = pad; }
#endif					
			}			

		}

#if defined (PLAYER_GENITAL) && defined (HOTSPOT_TYPE_KEY)
		if (IS_BOLT (at1)) { bx0 = cx1; by0 = cy1; player_push_bolt (); }
		if (IS_BOLT (at2)) { bx0 = cx2; by0 = cy2; player_push_bolt (); }

#endif
		// If still moving...
		if (pvx) {

#ifdef ENABLE_EVIL_TILE
			evil_tile_hith = (IS_EVIL (at1) || IS_EVIL (at2));
#endif

#ifdef ENABLE_SLIPPERY
			pslips = (IS_SLIPPERY (at1) || IS_SLIPPERY (at2)) && !pj;
#endif					

#ifdef ENABLE_HOLES
			cx1 = (prx - 1) >> 4; cx2 = (prx + 9) >> 4; cy1 = (pry + 12) >> 4; cm_two_points ();
			if (IS_HOLE (at1) && IS_HOLE (at2)) poverhole ++; else poverhole = 0;
			if (poverhole>1 && pholed == 0 && pj == 0) {
				player_holed ();
				pvy = 0;
			}
#endif
		}

	}

	// Solve facing
#ifdef PLAYER_GENITAL	
	if (pfacingv != 0xff) pfacing = pfacingv; else if (pfacingh != 0xff) pfacing = pfacingh;
#endif
