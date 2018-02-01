// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Vertical axis (New Genital)

// The collision box for New Genital is rather small,
// Just 8x5 pixels, centered at the bottom of the player sprite.
// The "holed" detection is 1 pixel thick.

// In this mode, "slippery", "evil tile" and "hole" are checked for
// and detected in the main collision routines.

	// First, poll pad.

	if (
		(pad & PAD_UP)
#ifdef PLAYER_TURRET 
		&& (pfixct_fire == 0)
#endif
	) {
#ifdef ENABLE_SLIPPERY
		rda = pslips ? half_life : PLAYER_AY;
		pvy -= rda;
#else
		pvy -= PLAYER_AY;
#endif
		if (pvy < -PLAYER_VY_MAX) pvy = -PLAYER_VY_MAX;
		pfacingv = CELL_FACING_UP;
	} else if (
		(pad & PAD_DOWN)
#ifdef PLAYER_TURRET 
		&& (pfixct_fire == 0)
#endif
	) {
#ifdef ENABLE_SLIPPERY
		rda = pslips ? half_life : PLAYER_AY;
		pvy += rda;
#else
		pvy += PLAYER_AY;
#endif
		if (pvy > PLAYER_VY_MAX) pvy = PLAYER_VY_MAX; 
		pfacingv = CELL_FACING_DOWN;
	} else {
#ifdef ENABLE_HOLES
		//if (!pholed)
#endif
		{
#ifdef ENABLE_SLIPPERY
			rda = pslips ? half_life : PLAYER_RY;
			if (pvy > 0) { pvy -= rda; if (pvy < 0) pvy = 0; }
			else 
			if (pvy < 0) { pvy += rda; if (pvy > 0) pvy = 0; }
#else
			if (pvy > 0) { pvy -= PLAYER_RY; if (pvy < 0) pvy = 0; }
			else 
			if (pvy < 0) { pvy += PLAYER_RY; if (pvy > 0) pvy = 0; }
#endif
		}

		pfacingv = 0xff;
	}

	// Move & limit

	py += pvy; if (pgotten) py += pgtmy;

	if (py < 0) { py = pry = 0; }
	else if (py > (192<<FIX_BITS)) pry = 192;
	else pry = py >> FIX_BITS;

	// Collision.

	cx1 = prx >> 4;
	cx2 = (prx + 7) >> 4;

	if (pvy + pgtmy) {
		if (pvy + pgtmy < 0) {

			// Top border of the collision box
			cy1 = cy2 = (pry + 11) >> 4;
			cm_two_points ();

			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2)) { 
				pgotten = pvy = 0;
				pry = (cy1 << 4) + 5;
				py = pry << FIX_BITS;

#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { bx0 = bx1 = cx1; by0 = cy1; by1 = cy1 - 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { bx0 = bx1 = cx2; by0 = cy2; by1 = cy2 - 1; bsignal = pad; }
#endif				
			} 
#ifdef ENABLE_HOLES
			else {
				//cy1 = (pry + 15) >> 4;
				//cm_two_points ();
				if (IS_HOLE (at1) && IS_HOLE (at2)) poverhole ++; else poverhole = 0;
				if (poverhole>1 && pholed == 0 && pj == 0 && ABS(pvx)<ABS(pvy)) {
					player_holed ();
					pvx = 0;
				}
			}
#endif
		} else { 

			// Bottom border of the collision box
			cy1 = cy2 = (pry + 15) >> 4;
			cm_two_points ();

			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2)) {
				pgotten = pvy = 0;
				pry = (cy1 - 1) << 4;
				py = pry << FIX_BITS;

#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { bx0 = bx1 = cx1; by0 = cy1; by1 = cy1 + 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { bx0 = bx1 = cx2; by0 = cy2; by1 = cy2 + 1; bsignal = pad; }
#endif				
			} 
#ifdef ENABLE_HOLES
			else {
				if (IS_HOLE (at1) && IS_HOLE (at2)) poverhole ++; else poverhole = 0;
				if (poverhole>1 && pholed == 0 && pj == 0 && ABS(pvx)<ABS(pvy)) {
					player_holed ();
					pvy = pvy + pvy; 
					pvx = 0;
				}
			}
#endif

		}

		// If still moving...
		if (pvy) {

#ifdef ENABLE_EVIL_TILE
			evil_tile_hitv =  (IS_EVIL (at1) || IS_EVIL (at2));
#endif

#ifdef ENABLE_SLIPPERY
			pslips = (IS_SLIPPERY (at1) || IS_SLIPPERY (at2)) && !pj;
#endif			
		}

#if defined (PLAYER_GENITAL) && defined (HOTSPOT_TYPE_KEY)
		if (IS_BOLT (at1)) { bx0 = cx1; by0 = cy1; player_push_bolt (); }
		if (IS_BOLT (at2)) { bx0 = cx2; by0 = cy2; player_push_bolt (); }
#endif

	}

	// Floor detections

	cy1 = cy2 = (pry + 14) >> 4;
	cm_two_points ();

#ifdef ENABLE_SLIPPERY
	pslips = (IS_SLIPPERY (at1) || IS_SLIPPERY (at2));
#endif

