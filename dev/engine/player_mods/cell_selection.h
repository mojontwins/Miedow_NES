// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Cell selection

	if (psleeping) {
		psprid = 33;
	} else if (pholed && pholed < 48) {
		psprid = CELL_PHOLED + (pholed >> 4);
	} else if (phit) {
		psprid = CELL_HIT_BASE + !!pfacingh;
	} else {
		if (pj) {
			psprid = CELL_JUMPING;
		} else if (pfixct_fire || pfixct_push) {
			psprid = CELL_FIRING;
		} else if (ABS (pvy) > PLAYER_VY_MIN) {
			psprid = CELL_WALK_BASE + ((pry >> 4) & 3);
		} else if (ABS (pvx) > PLAYER_VX_MIN) {
			psprid = CELL_WALK_BASE + ((prx >> 4) & 3);
		} else psprid = CELL_IDLE;

		psprid += pfacing;
	}
	