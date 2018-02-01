// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Simple animated shines

void shines_add (void) {
	shxy [shw] = rdf;
	shw ++;
}

void shines_do (void) {
	rdb = 0; // offset
	shi = shw; while (shi --) {
		rda = shxy [shi];
		rdc = (((frame_counter >> 2) + shi) & 0x1f);
		oam_index = oam_spr (
			4 + (rda << 4),
			4 + (rda & 0xf0) + SPRITE_ADJUST + 16,
			rdc < 4 ? SHINES_BASE + rdc : SHINES_BASE,
			0,
			oam_index
		);
		rdb = rdb + 8;
	}
}
