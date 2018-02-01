	// Jump!

	if (pj) {
		pctj ++; if (pctj == PLAYER_PRECALC_JUMP_STEPS)	{
			pj = 0;
			cy1 = cy2 = (pry + 15) >> 4; cm_two_points ();
			if (IS_HOLE (at1) && IS_HOLE (at2)) player_holed ();
		}
	}
