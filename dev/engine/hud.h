// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Hud. Of course, this has to be customized for each game

void p_t1 (unsigned char x, unsigned char y, unsigned char n) {
	gp_addr = NAMETABLE_A + (y << 5) + x;
	update_list_write (DIGIT (n));
}

void hud_update (void) {
	if (plife != oplife) {
		p_t1 (4, 2, plife);
		oplife = plife;
	}

	if (level) {
		if (pobjs != opobjs) {
			p_t2 (18, 2, max_hotspots_type_1 - pobjs);
			opobjs = pobjs;
		}
		
		if (pkeys != opkeys) {
			p_t1 (28, 2, pkeys);
			opkeys = pkeys;
		}
	}
}

void hud_draw (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (hud_rle);
	if (level == 0) {
		vram_adr (NAMETABLE_A + 64 + 12);
		gpit = 16; while (gpit --) vram_put (0);
	}
}
