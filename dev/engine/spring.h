// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Spikes over springs
// (complete with proximity sensor)
// TM!

// Define SPRINGS_X and SPRINGS_Y in definitions.h
// so I know where to look to get the coordinates.

void springs_add (void) {
#ifdef SPRINGS_CREATE_FROM_MAP
	springs_x [springs_idx] = rdx << 3;
	springs_y [springs_idx ++] = (rdy << 3) - 32;
#else
	springs_x [springs_idx] = SPRINGS_X << 4;
	springs_y [springs_idx ++] = 16 + (SPRINGS_Y << 4);
#endif
}

void springs_do (void) {
	gpit = springs_idx; while (gpit --) {
		if (pry <= springs_y [gpit]) {
			if (prx + 7 >= springs_x [gpit] && prx <= springs_x [gpit] + 15) {
				set_map_tile (springs_x [gpit] >> 4, (springs_y [gpit] >> 4) - 1, SPRINGS_TILE);
				sfx_play (SPRINGS_SOUND, SC_LEVEL);
				springs_y [gpit] = 0;
			}
		}
	}
}
