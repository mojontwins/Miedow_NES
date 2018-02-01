// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// talkbox.h - modified to fit. For the old version, check Bosque.

// Routines to show simple text boxes.

#define TAPESTRY_X_TILES 1
#define TAPESTRY_Y_TILES 4
#define OAM_LOCATION     220

const unsigned char stbf [] = {
	 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 
	 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9,
	10,11,12,13,13,13,13,13,13,13,13,13,13,14
};

void custom_tapestry (void) {
	rdx = TAPESTRY_X_TILES<<1;
	rdy = TOP_ADJUST + (TAPESTRY_Y_TILES<<1); 
	rde = 0;                                            // Update list control
	gp_gen = (unsigned char *) stbf;                    // Pointer to tapestry
	gpkt = TAPESTRY_X_TILES + (TAPESTRY_Y_TILES<<4);    // Index to scr_buff
	gpit = 42; while (gpit --) {
		if (rde == 0) ul = update_list;
		rdt = rdd ? scr_buff [gpkt ++] : *gp_gen ++;    // Upon rdd, paint or restore
		update_list_tile ();
		rdx += 2;
		rde = (rde + 1) & 3; if (rde == 0 || gpit == 0) close_update_cycle ();
		if (rdx == 30) { rdx = 2; rdy += 2; gpkt += 2; }
	}
}

void run_talk_script (void) {
	// Runs script #rda
	music_pause (1);

	gp_dia = (unsigned char *) dialogues [rda];

	c_ts_pals = tstb_pals;
	c_ts_tmaps = tstb_tmaps;

	while ((rdi = *gp_dia ++) != 0xff) {
		// rdi is the character talking

		// Draw marquee
		rdd = 0; custom_tapestry ();

		// Draw sprite
		oam_meta_spr (
			(TAPESTRY_X_TILES<<4)+12, 
			(TAPESTRY_Y_TILES<<4)+12+16 + SPRITE_ADJUST, 
			OAM_LOCATION, 
			spr_cuts [rdi]
		);

		// Show text
		rda = *gp_dia ++; 

		gp_aux = (unsigned char *) (texts [rda]);

		rdy = TOP_ADJUST + (TAPESTRY_Y_TILES<<1) + 1;
		gp_addr = NAMETABLE_A | (rdy << 5) | 8;

		rdc = 1;
		while (rda = *gp_aux ++) {
			if (rda == '%') {
				rdy ++; gp_addr = NAMETABLE_A | (rdy << 5) | 8;
				if (!rdc) { close_update_cycle (); ul = update_list; } 
			} else {
				if (rdc) {
					ul = update_list;
					update_list_write (rda-32);
					if (rda > 32) sfx_play (SFX_TU, SC_LEVEL);
					close_update_cycle ();
				} else update_list_write (rda-32);
			}

			pad_read (); 
			if (pad_this_frame & PAD_START) { rdi = 0xff; break; }
			else if (pad_this_frame) rdc = 0;
		}

		close_update_cycle ();
		if (rdi == 0xff) break;

		// Wait button

		while (1) {
			pad_read ();
			rda = pad_this_frame & PAD_START;
			if (pad_this_frame & (PAD_A | PAD_B | PAD_START)) break;
		}
		if (rda) break;
	}

	// Restore
	oam_hide_rest (OAM_LOCATION);
	c_ts_pals = l_ts_pals [level];
	c_ts_tmaps = l_ts_tmaps [level];
	rdd = 1; custom_tapestry ();

	music_pause (0);

	pad_clean ();
}
