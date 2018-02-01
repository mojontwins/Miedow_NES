// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Code for fixed screens

void enter_screen (const unsigned char *p, void (*func) (void)) {
	cls ();
	pal_bg (p);
	
	(*func) ();
	
	scroll (0, 0);
	ppu_on_all ();
	fade_in ();
}

void exit_cleanly (void) {
	oam_hide_rest (0);
	music_stop ();
	fade_out ();
	ppu_off ();	
}

void wait_time_or_input (void) {
	rda = (pad_poll (0) != 0);
	while (game_time) {
		ticker ++; if (ticker == ticks) {
			ticker = 0;
			game_time --;
		}

		if (pad0 = pad_poll (0)) {
			if (!rda) break;
		} else {
			rda = 0;
		}

		ppu_wait_nmi ();
	}
}

void do_screen (unsigned char seconds) {
	game_time = seconds; ticker = 0;
	wait_time_or_input ();
	exit_cleanly ();
}

void screen_title (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (title_bg_rle);
	p_s (10, 21, "PRESS START!");
	p_s (5, 25, "@ 2018 THE MOJON TWINS");
	#ifdef COMPO
		p_s (4, 27, "NESDEV COMPO EDITION 1.0");
	#endif
}

void screen_game_over (void) {
	// Game over
	if (levelseq && pcontinues) {
		rdb = 13;
#ifdef LANG_ES		
		p_s (11, 15, "CONTINUA "); vram_put (DIGIT (pcontinues));
		p_s (12, 17, "SI    NO");
#else	
		p_s (11, 15, "CONTINUE "); vram_put (DIGIT (pcontinues));
		p_s (12, 17, "YES / NO");
#endif		
	} else rdb = 15;
	p_s (11, rdb, "GAME OVER!");
}

void screen_ending_mod_update (void) {
	// rda = base tile
	ul = update_list; 
	gp_addr = NAMETABLE_A + (15<<5) + 15;
	*ul ++ = MSB (gp_addr);
	*ul ++ = LSB (gp_addr);
	*ul ++ = rda ++;
	gp_addr += 31;
	update_list_horz_2 ();
	*ul ++ = rda ++; 
	*ul ++ = rda ++;
	close_update_cycle ();
}

void p_s_ul_s (unsigned char *s) {
	while (rda = *s ++) {
		pad_read (); if (pad_this_frame & (PAD_A|PAD_B|PAD_START)) { rdc = 1; }
		if (!rdc) ul = update_list;
		update_list_write (rda-32);
		if (!rdc) {
			close_update_cycle ();
			delay (3);
		}
	}
	if (rdc) {
		close_update_cycle ();
		ppu_wait_nmi ();
	}
}

void p_s_cl_l () {
	ul = update_list;
	*ul ++ = MSB (gp_addr) | NT_UPD_HORZ;
	*ul ++ = LSB (gp_addr);
	*ul ++ = 32;
	gpit = 32; while (gpit --) *ul ++ = 0;
	close_update_cycle ();
}

void breakable_ticks_wait (void) {
	if (rdc) return;
	rdd = ticks << 1; while (rdd --) {
		pad_read ();
		if (pad_this_frame & (PAD_A|PAD_B|PAD_START)) {
			rdc = 1; break;
		}
		ppu_wait_nmi ();
	}
}

void screen_textcycle (unsigned char *s) {
	if (rdc) return;
	gp_addr = NAMETABLE_A + (20<<5);
	p_s_ul_s (s);
	breakable_ticks_wait ();
	gp_addr = NAMETABLE_A + (20<<5);
	p_s_cl_l ();
}

void screen_game_ending (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (cuts0_rle);
}

void screen_level (void) {
	// Level XX
	if (levelseq < 9) {
		p_s (12, 14, "DREAM ");
		vram_put (levelseq + 17);
	} else if (levelseq == 9) p_s (12, 14, "DREAM 10");
	else p_s (10, 14, "LAST DREAM");
}

void screen_cuts (void) {
	vram_adr (NAMETABLE_A);
	vram_unrle (cuts0_rle);
}

void screen_intro (void) {
	vram_adr (NAMETABLE_A);
	#ifdef COMPO
		vram_unrle (intro_rle_compo);
	#else
		vram_unrle (intro_rle);
	#endif
}
