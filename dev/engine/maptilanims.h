// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Maptilanims

void maptilanims_init (void) {
	gpit = MAPTILANIMS_MAX; while (gpit --) {
		mta_ac [gpit] = 0;
		mta_slots [gpit] = gpit;
	}
	mta_slot = MAPTILANIMS_MAX;
}

void maptilanims_activate (void) {
	// xy = rdc
	// gp_gen = pointer to animation. Animations are sequences of (frame #, tile #,)+ 0xff.
	mta_slot --; rda = mta_slots [mta_slot];
	mta_ac [rda] = (const unsigned char *) gp_gen;
	mta_xy [rda] = rdc;
	mta_ct [rda] = 0;
}

void maptilanims_do (void) {
	gpit = MAPTILANIMS_MAX; while (gpit --) if (gp_gen = mta_ac [gpit]) {
		if (mta_ct [gpit]) mta_ct [gpit] --; else {
			// Time out, read another frame
			mta_ct [gpit] = *gp_gen ++;
			if (mta_ct [gpit] == 0xff) { mta_ac [gpit] = 0; continue; }
			rdb = *gp_gen ++;
			mta_ac [gpit] = gp_gen;
			// Render
			rdc = mta_xy [gpit];
			set_map_tile (rdc & 0xf, rdc >> 4, rdb);
		}
	}
}
