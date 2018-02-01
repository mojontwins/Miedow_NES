// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Propellers

// Propellers may be added by different means, 
// But anyway you should call this funcion.

// Define PROPELLERS_X and PROPELLERS_Y in definitions.h
// so I know where to look to get the coordinates.

void propellers_add (void) {
#ifdef PROPELLERS_ON_OFF
#ifndef PROPELLERS_MAX_CTR_FIXED	
	propellers_max_ctr [propellers_idx] = PROPELLERS_MAX_CTR_FIXED;
#endif	
	propellers_ctr [propellers_idx] = PROPELLERS_INI_CTR;
	propellers_on [propellers_idx] = 0;
#endif

#ifdef PROPELLERS_CREATE_FROM_MAP
	rda = gpit - 16;
	gpint = NAMETABLE_A + rdx + (rdy << 5);
#else
	rda = PROPELLERS_X + (PROPELLERS_Y << 4) - 16;
	gpint = GAME_AREA_ADR + (PROPELLERS_X << 1) + (PROPELLERS_Y << 6);
#endif
	
#ifdef PROPELLERS_ON_OFF	
	propellers_rda [propellers_idx] = rda;
#else	
#ifdef PROPELLERS_LIMIT
	rdb = PROPELLERS_LIMIT;
	while (!scr_attr [rda] && rda < 192 && rdb --) { scr_attr [rda] = PROPELLERS_BIT; rda -= 16; }
#else
	while (!scr_attr [rda] && rda < 192) { scr_attr [rda] = PROPELLERS_BIT; rda -= 16; }
#endif
#endif	

	propellers_add_hi [propellers_idx] = MSB (gpint) | NT_UPD_HORZ;
	propellers_add_lo [propellers_idx ++] = LSB (gpint);
}

void propellers_do (void) {
	rdd = frame_counter & 2;
	gpit = propellers_idx; while (gpit --) {
#ifdef PROPELLERS_ON_OFF
		if (propellers_ctr [gpit]) propellers_ctr [gpit] --; else {
#ifdef PROPELLERS_MAX_CTR_FIXED
			propellers_ctr [gpit] = PROPELLERS_MAX_CTR_FIXED;
#else
			propellers_ctr [gpit] = propellers_max_ctr [gpit];
#endif			
			propellers_on [gpit] = 1 - propellers_on [gpit];
// CUSTOM {			
			if (propellers_on [gpit]) {
				rda = propellers_rda [gpit];
				rdx = ((rda & 0xf) << 4) + 4;
				rdy = (rda & 0xf0) + 15;
				rda = 2;
				particles_create ();
			}
// } END_OF_CUSTOM				
			rda = propellers_rda [gpit];
#ifdef PROPELLERS_LIMIT
			rdb = PROPELLERS_LIMIT;
			while (!(scr_attr [rda]&(~PROPELLERS_BIT)) && rda < 192 && rdb --) { scr_attr [rda] = (propellers_on [gpit] ? PROPELLERS_BIT : 0); rda -= 16; }
#else
			while (!(scr_attr [rda]&(~PROPELLERS_BIT)) && rda < 192) { scr_attr [rda] = (propellers_on [gpit] ? PROPELLERS_BIT : 0); rda -= 16; }
#endif			
		}

		rda = propellers_on [gpit] << 1;
		*ul ++ = propellers_add_hi [gpit];
		*ul ++ = propellers_add_lo [gpit];
		*ul ++ = 2;
		*ul ++ = PROPELLERS_PATTERN + rda;
		*ul ++ = PROPELLERS_PATTERN + (rda | 1);
#else		
		*ul ++ = propellers_add_hi [gpit];
		*ul ++ = propellers_add_lo [gpit];
		*ul ++ = 2;
		*ul ++ = PROPELLERS_PATTERN + rdd;
		*ul ++ = PROPELLERS_PATTERN + (rdd | 1);
#endif		
	}
}
