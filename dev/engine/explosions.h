// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Explosions

void expl_ini (void) {
	gpit = EXPL_MAX; while (gpit --) {
		expl_ac [gpit] = 0;
		expl_slots [gpit] = gpit;
	} 
	expl_slot = EXPL_MAX;
}

void expl_create (void) {
	// Create @ rdx, rdy
	// Explodes rde times

	if (expl_slot == 0) return;
	expl_slot --; expli = expl_slots [expl_slot];

	expl_ac [expli] = rde + 1;
	expl_ct [expli] = 0;
	expl_x [expli] = rdx;
	expl_y [expli] = rdy;
}

void expl_do (void) {
	expli = EXPL_MAX; while (expli --) {
		if (expl_ac [expli]) {
			if (expl_ct [expli]) {
				// Draw frame
				expl_ct [expli] --;
				oam_index = oam_meta_spr (
					expl_x [expli] + expl_xd [expli],
					expl_y [expli] + expl_yd [expli] + SPRITE_ADJUST,
					oam_index,
					spr_expl [expl_ct [expli] >> 1]
				);
			} else {
				expl_ac [expli] --;
				if (expl_ac [expli]) {
					expl_ct [expli] = EXPL_FRAMES<<1;
					rda = frame_counter & 0xf;
					expl_xd [expli] = jitter_big [rda];
					expl_yd [expli] = jitter_big [15 - rda];
				} else {
					// Free slot
					expl_slots [expl_slot] = expli; 
					expl_slot ++;
				}
			}
		} 
	}
}
