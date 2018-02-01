// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// The girl

void girl_init (void) {
	rda = 1 - active_girl;
	if (ini_n_pant [rda] == n_pant) {
		girlact = 1; othergirloffs = rda ? 14 : 0;
		girlx = ini_px [rda] >> FIX_BITS;
		girly = ini_py [rda] >> FIX_BITS;
	} else girlact = 0;
}

void girl_do (void) {
	if (girlact) {
		if (prx + 7 >= girlx && prx <= girlx + 7 && pry + 15 >= girly && pry <= girly + 15) {
			do_game = 0;
		}

		oam_index = oam_meta_spr (
			girlx, girly + SPRITE_ADJUST, 
			oam_index, 
			spr_player [othergirloffs]);
	}
}
