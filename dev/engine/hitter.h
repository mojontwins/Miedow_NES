// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// (Adapted from) Vostok Engine MK2 v1.0
// Not ready yet to be implemented into MK2 fully. Hacky.
// Copyleft 2017 by The Mojon Twins

#define HITTER_STEPS	9
#define HIT_F0			4
#define HIT_F1			6

//                                              H  H  H
const unsigned char hoffs_x [] = { -2, 0, 2, 4, 6, 8, 8, 4, 0 };

void hitter_do (void) {
	if (hitter_on) {
		hitter_y = pry - 6;
		hitter_x = pfacing ? prx - 8 - hoffs_x [hitter_frame] : prx + hoffs_x [hitter_frame];

		oam_index = oam_meta_spr (
			hitter_x, hitter_y + SPRITE_ADJUST,
			oam_index,
			pfacing ? ssit_tb_01_a : ssit_tb_01_a
		);

		if (half_life) { hitter_frame ++; if (hitter_frame == HITTER_STEPS) hitter_on = 0; }
	} 
}
