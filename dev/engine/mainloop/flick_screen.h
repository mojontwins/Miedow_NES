		// Change screen
		// Very basic. Extend when needed.

		if (0 == pholed) {
			if (prx == 4 && pvx < 0) {
				n_pant --;
				px = 244 << FIX_BITS;
			} else if (prx == 244 && pvx > 0) {
				n_pant ++;
				px = 8<<FIX_BITS;
			} 

			if (
	#ifdef PLAYER_GENITAL
				pry <= 16 && 
	#else
				pry == 0 &&
	#endif			
				pvy < 0
	#ifdef MAP_CHECK_TOP
				&& n_pant >= map_w
	#endif
			) {
				n_pant -= map_w;
				py = 192<<FIX_BITS;
	#if (defined (PLAYER_JUMPS) || defined (PLAYER_MONONO)) && defined (ENGINE_TYPE_CLASSIC)
			
	#ifdef ENABLE_WATER
				if (pwater) pvy = -PLAYER_VY_FLICK_TOP_SWIMMING; else
	#endif
				{ pvy = -PLAYER_VY_FLICK_TOP; pj = 0; }
	#endif
			} else if (pry >= 192 && pvy > 0) {
				n_pant += map_w;
	#ifdef PLAYER_GENITAL
				py = 16<<FIX_BITS;
	#else
				py = 0;
	#endif			
			}
		}

		if (on_pant != n_pant) {
			game_prepare_screen ();
			on_pant = n_pant;
		} 
