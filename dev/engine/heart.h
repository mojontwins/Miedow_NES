// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// heart.h, a simple particle
// v2.0.Journey, customized to be bubbles which only
// exist on tiles with the water bit set.

// To save RAM, I've removed hearts_l as it won't be used.
// So this is almost a full rewrite.

// I love when this happens ...

/*
void heart_create (void) {
	bi = MAX_HEARTS; while (bi --) if (!hearts_l [bi]) {
		hearts_l [bi] = halfticks + (rand8 () & 0xf); hearts_x [bi] = en_x [gpit] + 4; hearts_y [bi] = en_y [gpit] - 4;
		break;
	}
}

void hearts_move (void) {
	bi = MAX_HEARTS; while (bi --) if (hearts_l [bi]) {
		hearts_l [bi] --; hearts_y [bi] -= (1 + (rand8 () & 1)); hearts_x [bi] += ((rand8 () & 1) << 1) - 1;
		if (hearts_y [bi] < 16) hearts_l [bi] = 0;
		
		oam_index = oam_spr (hearts_x [bi], hearts_y [bi] + SPRITE_ADJUST, 2, 0, oam_index);
	}
}

void hearts_init (void) {
	bi = MAX_HEARTS; while (bi --) hearts_l [bi] = 0;
}
*/

void hearts_init (void) {
	bi = MAX_HEARTS; while (bi --) hearts_y [bi] = 0;
}

void hearts_create (void) {
	if (pry < 8) return;
	bi = MAX_HEARTS; while (bi --) if (!hearts_y [bi]) {
		hearts_x [bi] = prx; hearts_y [bi] = pry - 4;
		break;
	}
}

void hearts_move (void) {
	bi = MAX_HEARTS; while (bi --) if (hearts_y [bi]) {
		if (half_life) { hearts_y [bi] -= (1 + (rand8 () & 1)); hearts_x [bi] += ((rand8 () & 1) << 1) - 1; }
		if (hearts_y [bi] < 16 
			|| 0 == (IS_WATER (scr_attr [(hearts_x [bi]>>4)|((hearts_y [bi] & 0xf0)-16)]))
		) { hearts_y [bi] = 0; break; }
		if ((bi & 1) == half_life) oam_index = oam_spr (hearts_x [bi], hearts_y [bi] + SPRITE_ADJUST, 6 | (bi & 1), 2, oam_index);
	}
}
