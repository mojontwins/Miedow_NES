// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Vertical axis (Classic)

#ifdef PLAYER_GRAVITY
#ifdef ENABLE_WATER
	if (pwater) {
		pvy += PLAYER_G_WATER;
		if (pvy > PLAYER_VY_MAX_SINK_WATER) pvy = PLAYER_VY_MAX_SINK_WATER;
	} else
#endif
	// Gravity
	if (!pgotten
#ifdef PLAYER_JETPAC
		&& !pthrust
#endif
	) {
		if (!pj) {
#ifdef PLAYER_FLOATS
			if (pfloat) {
				if (half_life) { if (pvy < 16) pvy ++; else pvy = 16; }
			} else
#endif			
			pvy += PLAYER_G; 
		} else pvy += PLAYER_G_JUMPING;
		if (pvy > PLAYER_VY_FALLING_MAX) pvy = PLAYER_VY_FALLING_MAX;
	}
#endif

#ifdef PLAYER_GENITAL
	// Poll pad
	if (pad & PAD_UP) {
		if (pvy > -PLAYER_VY_MAX) {
			pvy -= PLAYER_AY;			
		}
		pfacingv = CELL_FACING_UP;
	} else if (pad & PAD_DOWN) {
		if (pvy < PLAYER_VY_MAX) {
			pvy += PLAYER_AY;
		}
		pfacingv = CELL_FACING_DOWN;		
	} else {
#ifdef ENABLE_HOLES
		if (!pholed)
#endif
			if (pvy > 0) {
				pvy -= PLAYER_RY; if (pvy < 0) pvy = 0; 
			} else if (pvy < 0) {
				pvy += PLAYER_RY; if (pvy > 0) pvy = 0;
			}

		pfacingv = 0xff;
	}
#endif

	// Move
	py += pvy;

	// Collision
	//prx = px >> FIX_BITS;
	if (py < 0) { py = pry = 0; }
	else if (py > (192<<FIX_BITS)) pry = 192;
	else pry = py >> FIX_BITS;

	cx1 = prx >> 4;
	cx2 = (prx + 7) >> 4;
	if (pvy + pgtmy) {
		if (pvy + pgtmy < 0) {
#ifdef PLAYER_8_PIXELS
			cy1 = cy2 = (pry + 6) >> 4;
#else
			cy1 = cy2 = pry >> 4;
#endif
			cm_two_points ();
#ifdef PLAYER_GENITAL
			if (IS_FLOOR (at1) || IS_FLOOR (at2))
#else
			if (IS_OBSTACLE (at1) || IS_OBSTACLE (at2))
#endif
			{
				pgotten = pvy = 0;
#ifdef PLAYER_8_PIXELS
				pry = ((cy1 + 1) << 4) - 6;
#else
				pry = (cy1 + 1) << 4;
#endif
				py = pry << FIX_BITS;

#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { bx0 = bx1 = cx1; by0 = cy1; by1 = cy1 - 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { bx0 = bx1 = cx2; by0 = cy2; by1 = cy2 - 1; bsignal = pad; }
#endif					
			} else {

#ifdef EVIL_TILE_MULTI
				if (IS_EVIL (at1) || IS_EVIL (at2)) {
					pvy = PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif	

#ifdef ENABLE_HOLES
				if (!pholed) {
					cy1 = cy2 = (pry + 14) >> 4;
					cm_two_points ();
					if (IS_HOLE (at1) && IS_HOLE (at2)) player_holed ();
				} 
#endif

#ifdef ENABLE_QUICKSANDS
				if (IS_QUICKSANDS (at1) || IS_QUICKSANDS (at2)) {
					//if (pctj > 2) pj = pvy = 0;
					if (pvy < -PLAYER_VY_EXIT_QUICKSANDS) pvy = -PLAYER_VY_EXIT_QUICKSANDS;
				}
#endif
			}
		} else /* if (pvy + pgtmy > 0) */ {
			cy1 = cy2 = (pry + 15) >> 4; 
			cm_two_points (); 
#ifdef PLAYER_GENITAL
			if (IS_FLOOR (at1) || IS_FLOOR (at2))
#else			
	 		if (((pry - 1) & 15) < 4 && (IS_FLOOR (at1) || IS_FLOOR (at2))) 
#endif
	 		{
				pgotten = pvy = 0;
				pry = (cy1 - 1) << 4;
				py = pry << FIX_BITS;
#ifdef PLAYER_PUSH_BOXES
				// Check if the collision was with a pushable box and raise a flag!
				if (IS_PUSH_BOX (at1)) { bx0 = bx1 = cx1; by0 = cy1; by1 = cy1 + 1; bsignal = pad; }
				if (IS_PUSH_BOX (at2)) { bx0 = bx1 = cx2; by0 = cy2; by1 = cy2 + 1; bsignal = pad; }
#endif				
			} else {
#ifdef ENABLE_HOLES
				if (!pholed && (IS_HOLE (at1) && IS_HOLE (at2))) player_holed ();
#endif			

#ifdef EVIL_TILE_MULTI
				if (IS_EVIL (at1) || IS_EVIL (at2)) {
					pvy = -PLAYER_V_REBOUND_MULTI; evil_tile_hit = 1;
				}
#endif		

#ifdef ENABLE_QUICKSANDS
				if (IS_QUICKSANDS (at1) || IS_QUICKSANDS (at2)) pvy = PLAYER_VY_SINKING;
#endif	
			}
		}

#if defined (PLAYER_GENITAL) && defined (HOTSPOT_TYPE_KEY)
		if (IS_BOLT (at1)) { bx0 = cx1; by0 = cy1; player_push_bolt (); }
		if (IS_BOLT (at2)) { bx0 = cx2; by0 = cy2; player_push_bolt (); }
#endif
	}

#ifdef PLAYER_GRAVITY
	// Floor detections: possee

	cy1 = cy2 = (pry + 16) >> 4;
	cm_two_points ();
	ppossee = (IS_FLOOR (at1) || IS_FLOOR (at2)) && pvy >= 0 && ((pry & 0xf) == 0);
#ifdef PLAYER_JUMPS	
	if (ppossee || pgotten) {
		pjustjumped = 0;
#ifdef PLAYER_DOUBLE_JUMP
		njumps = 0;
#endif		
	}
#endif	
#endif	

	// Floor detections: Conveyors
	
#ifdef ENABLE_CONVEYORS
	if (ppossee) {
		if (IS_CONVEYOR (at1)) { if CONVEYOR_PUSHES_RIGHT (at1) pgtmx = CONVEYOR_SPEED; else pgtmx = -CONVEYOR_SPEED; pgotten = 1; }
		if (IS_CONVEYOR (at2)) { if CONVEYOR_PUSHES_RIGHT (at2) pgtmx = CONVEYOR_SPEED; else pgtmx = -CONVEYOR_SPEED; pgotten = 1; }
	}
#endif	

	// Floor detections: Propellers
#ifdef ENABLE_PROPELLERS
	if (IS_PROPELLER (at1) || IS_PROPELLER (at2)) {
		pvy -= PLAYER_G + PLAYER_AY_PROPELLER;
		if (pvy < -PLAYER_VY_PROPELLER_MAX) pvy = -PLAYER_VY_PROPELLER_MAX;
	}
#endif

	// Floor detections: Evil tile

#ifdef ENABLE_EVIL_TILE
#ifdef EVIL_TILE_ON_FLOOR
	cy1 = cy2 = (pry + 12) >> 4;	// Let it bleed a bit
	cm_two_points ();
	if (at1 == 1 || at2 == 1) evil_tile_hit = 1;
#endif	
#endif

	// Floor detections: Slippery
#ifdef ENABLE_SLIPPERY
	pslips = ppossee && (IS_SLIPPERY (at1) || IS_SLIPPERY (at2));
#endif

	// Jump!

#ifdef PLAYER_JUMPS
	if (pad & PAD_A) {
		if (!pjb) {
			pjb = 1;
#ifdef ENABLE_WATER
			if (pwater) {
				if (ppossee) player_register_safe_spot ();
				pvy -= PLAYER_AY_SWIM;
				if (pvy < -PLAYER_VY_SWIM_MAX) pvy = -PLAYER_VY_SWIM_MAX;
				pwaterthrustct ++;
				if (rand8 () & 0xf) hearts_create ();
			} else
#endif			
			if (!pj) {
				if (
					(pgotten || ppossee || phit)
#ifdef PLAYER_DOUBLE_JUMP
					|| (njumps < 2)
#endif
				) {
#ifdef PLAYER_DOUBLE_JUMP					
					if (njumps) {
						fumettos_add ();
						pctj = 2;
					} else
#endif					
					pctj = 0; 
#ifdef PLAYER_DOUBLE_JUMP
					njumps ++;
#endif					
					pj = 1; pjustjumped = 1;
					pvy = -PLAYER_VY_JUMP_INITIAL;
					sfx_play (SFX_JUMP, SC_PLAYER);

#ifdef PLAYER_DIE_AND_RESPAWN
					if (ppossee) {
						player_register_safe_spot ();
					}
#endif					
				}
			} 
		}
		if (pj) {
			pctj ++; if (pctj == PLAYER_VY_JUMP_A_STEPS) pj = 0;
		}
	} else {
		pjb = 0;
		if (pj) {
			if (pvy < -PLAYER_VY_JUMP_RELEASE) pvy = -PLAYER_VY_JUMP_RELEASE;
			pj = 0;
		}
	}
#endif

	// Monono!

#ifdef PLAYER_MONONO
	if (!(pad & PAD_A)) { pj = 0; pvylast = -PLAYER_VY_JUMP_INITIAL; } else {
		if (ppossee || pgotten) {
			pvy = SATURATE_N (pvylast - PLAYER_AY_JUMP, -PLAYER_VY_JUMP_MAX);
			pvylast = pvy;
			pj = 1;
			sfx_play (SFX_JUMP, SC_PLAYER);
		}
	}
#endif	

#ifdef PLAYER_JETPAC
	if (pad & PAD_A) {
		pvy = SATURATE_N (pvy - PLATER_AY_JETPAC, -PLAYER_VY_JETPAC_MAX);		
		pthrust = 1;
		if (!(thrustct)) fumettos_add ();
				thrustct ++; if (thrustct == 7) thrustct = 0; // so it stays out of phase
	} else thrustct = pthrust = 0;
#endif

#ifdef PLAYER_SPINS
	//if (!pvy < 0) pspin = 0;
	if (pad & PAD_DOWN) {
		if (ppossee && ABS (pvx) > PLAYER_VX_MIN) {
			pspin = 1; sfx_play (SFX_BUTT_FALL, SC_PLAYER);
		}
	}
#endif

	