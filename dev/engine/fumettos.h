// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Custom fumettos

void fumettos_init (void) {
	bi = FUMETTOS_MAX; while (bi --) fumettos_life [bi] = 0;
}

void fumettos_add (void) {
	bi = FUMETTOS_MAX; while (bi --) {
		if (!fumettos_life [bi]) {
			fumettos_life [bi] = 32;
			//if (pfacing) fumettos_x [bi] = prx + 4; else fumettos_x [bi] = prx - 4;
			fumettos_x [bi] = prx;
			fumettos_y [bi] = pry + 4;
			break;
		}
	}
}

void fumettos_do (void) {
	bi = FUMETTOS_MAX; while (bi --) {
		if (fumettos_life [bi]) {
			fumettos_life [bi] --;
			oam_index = oam_spr (fumettos_x [bi], fumettos_y [bi] + SPRITE_ADJUST, FUMETTO_BASE_PATTERN + 3-(fumettos_life [bi] >> 3), 2, oam_index);
		}
	}
}
