// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Bolts

void bolts_load (void) {
	gpit = c_max_bolts; while (gpit --) lkact [gpit] = 0;
}

// needs rdc = (y << 4) + x
void bolts_clear_bolt (void) {
	gp_gen = (unsigned char *) c_locks;

	for (gpit = 0; gpit < c_max_bolts; gpit ++) {

		rda = *gp_gen ++; // Screen
		rdb = *gp_gen ++; // YX

		if (n_pant == rda) {
			if (rdf == rdb) {
#ifdef ENABLE_TOUCHPLATES
				if (scr_buff [rdb] == TILE_KEYED_BOLT)
#endif
				lkact [gpit] = 1; break;
			}
		}
	}
}

void bolts_update_screen (void) {
	rdt = 0; gp_gen = (unsigned char *) c_locks;
	for (gpjt = 0; gpjt < c_max_bolts; gpjt ++) {
		rda = *gp_gen ++; 	// Screen
		rdb = *gp_gen ++;	// YX
		if (n_pant == rda) {
			if (lkact [gpjt]) {
				scr_buff [rdb] = scr_attr [rdb] = 0;
				rdx = rdb & 0xf; rdx = rdx + rdx;
				rdy = rdb >> 4; rdy = rdy + rdy + TOP_ADJUST;
				draw_tile ();
			}
		}
	}
}

#if defined (ENABLE_TOUCHPLATES) || defined (ENABLE_LIGHTABLE)
void bolts_decrease_life (void) {
	// rdb = which bolt.
	
	bolt_lives [rdb] --;

	if (bolt_lives [rdb] == 0) {
		// Clear this bolt

		// Look for the bolt
		gp_gen = (unsigned char *) c_locks;

		for (gpit = 0; gpit < c_max_bolts; gpit ++) {	
			rda = *gp_gen ++; // Screen
			rde = *gp_gen ++; // YX

			if (lkact [gpit] == 0) {
				if (n_pant == rda) {
					if (rdb == scr_buff [rde]) {
						lkact [gpit] = 1; break;
					}
				}
			}
		}

		// rdf contains the cleared bolt YX
		set_map_tile (rde & 0xf, rde >> 4, 0);
		sfx_play (SFX_CHOF, SC_LEVEL);

		// Effect for beauty
		rdx = rde << 4;	rdy = 16 + (rde & 0xf0); rde = 3;
		expl_create ();
	}
}
