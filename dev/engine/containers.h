// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Containers are better than hotspots
// And are driven from the script. 

void containers_add (void) {
	c_x [c_idx] = CONTAINERS_X;
	c_y [c_idx] = CONTAINERS_Y;
	c_f [c_idx ++] = CONTAINERS_N;
}

void containers_do (void) {
	rdx = (prx + 4) >> 4; rdy = (pry + 8) >> 4;
	gpit = c_idx; while (gpit --) {
		if (ppossee && rdx == c_x [gpit] && rdy == c_y [gpit]) {
			containers_get = c_f [gpit];
			return;
		}
	}
}

void containers_draw (void) {
	gpit = c_idx; 
	while (gpit --) oam_index = oam_meta_spr (
		c_x [gpit] << 4, (c_y [gpit] << 4) + SPRITE_ADJUST,
		oam_index,
		spr_items [flags [c_f [gpit]]]
	);
}
