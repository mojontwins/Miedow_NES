// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Hotspots

void hotspots_ini (void) {
#ifdef HOTSPOTS_MAY_CHANGE
	gp_gen = (unsigned char *) c_hotspots;
	for (gpit = 0; gpit < MAX_PANTS; ++gpit) {
		ht [gpit] = *gp_gen ++; gp_gen ++;
		hact [gpit] = 1;
	}
#else
	gpit = MAX_PANTS; while (gpit --) hact [gpit] = 1;
#endif
}

void hotspots_load (void) {
	if (hact [n_pant]) {
#ifdef HOTSPOTS_MAY_CHANGE
		rda = c_hotspots [1 + (n_pant << 1)];
		hrt = ht [n_pant];
#else
		gp_gen = (unsigned char *) c_hotspots + (n_pant << 1);
		hrt = *gp_gen ++; rda = *gp_gen;
#endif
		hry = rda & 0xf0; hrx = rda << 4;
	} else hrt = 0;

	//pal_col (0,hrt);
}

void hotspots_do (void) {

	if (hrt) {
// CUSTOM {		
		if (hr_hit) hr_hit --;
		
		if (hrt == HOTSPOT_TYPE_OBJECT && (pflickering == 0 || half_life)) 
			spr_id = 6 + ((frame_counter >> 4) & 1) + ((!!hr_hit) << 1);
		else
// } END_OF_CUSTOM		 
			spr_id = hrt;
		oam_index = oam_meta_spr (hrx, hry + SPRITE_ADJUST, oam_index, spr_items [spr_id]);

		// Check
		if (collide (prx, pry, hrx, hry)) {
#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
			rda = 1;
#endif
			switch (hrt) {
#ifdef HOTSPOT_TYPE_REFILL
				case HOTSPOT_TYPE_REFILL:			
					plife += LIFE_REFILL; if (plife > 99) plife = 99;
					break;
#endif

#ifdef HOTSPOT_TYPE_OBJECT
// CUSTOM {					
				case HOTSPOT_TYPE_CHERIL:
// } END_OF_CUSTOM				
				case HOTSPOT_TYPE_OBJECT:
#ifdef ONLY_ONE_OBJECT_FLAG
					if (flags [ONLY_ONE_OBJECT_FLAG]) {
						rda = 0;
					} else {
						flags [ONLY_ONE_OBJECT_FLAG] = 1;
					}
#else				
					pobjs ++;
#endif
					break;
#endif

#ifdef HOTSPOT_TYPE_KEY
				case HOTSPOT_TYPE_KEY:
					pkeys ++;
					break;
#endif

#ifdef HOTSPOT_TYPE_AMMO
				case HOTSPOT_TYPE_AMMO:
					if (AMMO_MAX - pammo < AMMO_REFILL) pammo = AMMO_MAX; else pammo += AMMO_REFILL;
					break;
#endif

// CUSTOM {
				case HOTSPOT_TYPE_SKULL:
					red = 50;
					pal_bg (paltsr); pal_spr (paltsr);
					sfx_play (SFX_ESTRUJATOR, SC_ROOM);
					break;

// } END_OF_CUSTOM
			}
			
#ifdef HOTSPOTS_LOGIC_MORE_COMPLEX
			if (rda)
#endif
			{
// CUSTOM 
				if (hrt != HOTSPOT_TYPE_SKULL && hrt != HOTSPOT_TYPE_CHERIL)
// } END_OF_CUSTOM				
					sfx_play (0, SC_LEVEL);
				hact [n_pant] = hrt = 0;
			}
		}
	}
}
