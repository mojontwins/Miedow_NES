// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Game loop & shit

#ifdef SCRIPTING_ON
void game_run_fire_script (void) {
	run_script (2 * MAX_PANTS + 2);		// Press fire in any room.
	run_script (n_pant + n_pant + 1);	// Press fire in current room.
}
#endif

// CUSTOM {
void rain_new (void) {
	/*
	SLOW
	do {
		rdx = rand_pregen [rand_i ++];
		do { rdy = rand_pregen [rand_i ++]; } while (rdy < 28 || rdy > 212);
	} while (scr_attr [((rdx+4) >> 4) | ((rdy+4-28) & 0xf0)]);
	*/

	rdx = rand_pregen [rand_i ++];
	rdy = rand_pregen [rand_i ++];
	if (rdy < 28 || rdy > 212 || IS_NOT_RAINABLE(scr_attr [((rdx+4) >> 4) | ((rdy+4-28) & 0xf0)])) rain_c [gpit] = 0;
	
	rain_y [gpit] = rdy; rain_x [gpit] = rdx;
	rand_i ++;
}

void rain_reset_int (void) {
	rain_intm = -1; 
	rain_intct = rain_intmaxct = 16 + (rand_pregen [rand_i ++] & 15);
}
// } END_OF_CUSTOM

void game_init (void) {
	// Multiple level support (pseudo custom)
	// Some things are hardcoded for some games.

	pal_bg (l_pal_ts [level]);
	pal_spr (palss0);

	cur_bank = 0;						// CHR-ROM active

	c_ts_pals = l_ts_pals [level];
	c_ts_tmaps = l_ts_tmaps [level];
	c_behs = l_behs [level]; 
	c_tp_defs = l_tp_defs [level];

	// This game has MAP_CHR_ROM
	c_chr_rom = l_chr_rom [level];
	c_map = l_map [level];
	c_locks = l_locks [level];
	c_fpbs = l_fpbs [level];
	// c_decos = l_decos [level];
	c_max_bolts = l_max_bolts [level];

	c_enems = l_enems [level];
	c_hotspots = l_hotspots [level];
	max_hotspots_type_1 = l_max_hotspots_type_1 [level];
	spr_enems = spr_enems0; 			// l_spr_enems [level];
	spr_player = spr_player0; 			// l_spr_player [level];

	// Scalar types dealt with together
	// This produces better code.

	n_pant = l_scr_ini [level];
	
	map_w = 5; 							// l_map_w [level];
	
#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)
	enems_persistent_deaths_init ();
#endif	

#ifdef PERSISTENT_ENEMIES
	persistent_enems_load ();
#endif

#ifdef PERSISTENT_TILE_GET
	gpint = MAX_PANTS*12; while (gpint --) tile_got [gpint] = 0;
#endif

#ifdef HOTSPOT_TYPE_KEY
	bolts_load ();
#endif

	player_init ();

#ifndef DISABLE_HOTSPOTS		
	hotspots_ini ();
#endif	

	// Scripting / flags stuff

#ifdef COUNT_KILLED_ON_FLAG
	flags [COUNT_KILLED_ON_FLAG] = 0;
#endif

#ifdef ONLY_ONE_OBJECT_FLAG
	flags [ONLY_ONE_OBJECT_FLAG] = 0;
#endif

#ifdef PLAYER_INV_FLAG
	flags [PLAYER_INV_FLAG] = 0;
#endif

#ifdef SCRIPTING_ON
	// Script init
	script_pool = level_scripts [level];
#endif

	// CUSTOM {
	custom_on_off = l_custom_on_off [level];
	if (custom_on_off & FLAG_RAIN) {
		rain_int = (custom_on_off & FLAG_VARIABLE) ? ((rand_pregen [rand_i ++] & 0x3) + 1) : RAIN_MAX_DROPS;
		rain_reset_int ();
	}
	pfacing = pfacingv = l_facing [level];
	// } END_OF_CUSTOM

	// Game values (lifes, etc)

	oplife = 0xff;
	pobjs = 0; opobjs = 0xff;
	pbodycount = 0; opbodycount = 0xff;
	pkeys = 0; opkeys = 0xff;
	//pammo = AMMO_MAX; opammo = 0x0ff;

	// The almighty debug line!
	//n_pant = 18; px=224<<FIX_BITS; pkeys=1;
}

void game_prepare_screen (void) {
	no_ct = 0;
	update_list [0] = NT_UPD_EOF;
	ppu_wait_nmi ();

	if (first_time) first_time = 0; else fade_out ();
	ppu_off ();

#ifdef ENABLE_SPRINGS
	springs_idx = 0;
#endif

#ifdef ENABLE_SHINES
	shw = 0;
#endif

#ifdef ENABLE_PROPELLERS
	propellers_idx = 0;
#endif

#if defined (ENABLE_ESTRUJATORS) || defined (ENABLE_CATARACTS)
	est_ini_delay = est_idx = 0;
#endif	

#ifdef ENABLE_CATARACTS
	cataracts_on = 0;
#endif

	draw_scr ();

#ifdef ENABLE_FUMETTOS
	fumettos_init ();
#endif

#ifdef HOTSPOT_TYPE_KEY
	bolts_update_screen ();
#endif

#ifdef ENABLE_PUAS
	puas_init ();
#endif	

#ifdef PLAYER_CAN_FIRE	
	bullets_ini ();
#endif

#ifdef SHOOTING_DRAINS	
	flower_ini ();
#endif

#ifdef PERSISTENT_ENEMIES
	persistent_update ();
#endif	

#ifdef BREAKABLE_WALLS
	breakable_init ();
#endif

	enems_load ();

#ifndef DISABLE_HOTSPOTS	
	hotspots_load ();
#endif

#ifdef SHOOTING_DRAINS		
	pgauge = 30; bullets_draw_gauge_offline ();
#endif

#ifdef ENABLE_COCOS	
	simplecoco_init ();
#endif

#ifdef ENABLE_FABOLEES
	fabolee_init ();
#endif

#ifdef ENABLE_EXPLOSIONS
	expl_ini ();
#endif

	show_attributes ();

	ppu_on_all ();

	oam_index = 44;
	prx = px >> FIX_BITS; pry = py >> FIX_BITS;
	player_render ();

#ifndef DISABLE_HOTSPOTS	
	hotspots_do ();
#endif	

	enems_do ();

	// CUSTOM {
	rand_i = rand8 ();
	if (custom_on_off & FLAG_RAIN) {
		gpit = RAIN_MAX_DROPS; while (gpit --) {
			rain_c [gpit] = 1 + (rand_pregen [rand_i ++] & 3); rain_new ();
			if (rain_c [gpit]) {
				rain_c [gpit] --;
				if (oam_index < 248 && gpit < rain_int) oam_index = oam_spr (rain_x [gpit], rain_y [gpit], 0xd-rain_c [gpit], 3, oam_index);
			}
		}
	}
	//

	oam_hide_rest (oam_index);
	ul = update_list; 
	hud_update (); 
	close_update_cycle ();

#ifdef ENABLE_CONTAINERS
	c_idx = 0;
#endif

#ifdef SCRIPTING_ON
	run_script (2 * MAX_PANTS + 1);		// Entering any script
	run_script (n_pant + n_pant);			// Entering this room script
#endif

#ifdef ENABLE_HOLES
	player_register_safe_spot ();
#endif

	fade_in ();
}

void game_loop (void) {
	half_life = 0;
	first_time = 1;
	on_pant = 99;

	scroll (0, SCROLL_Y);
	reset_attributes ();
	// gpit = 8; while (gpit --) attr_table [gpit] = 0x55;
	
	ppu_on_all ();
	
	if (levelseq == 10 && level == 0) music_play (MUSIC_4);
	else if (levelseq < 10 && l_music [level] != 0xff) music_play (l_music [level]);

	set_vram_update (update_list);
	pwashit = 0; 
	pcharacter = 0;

	// Entering Game
#ifdef SCRIPTING_ON
#ifdef CLEAR_FLAGS
	msc_clear_flags ();
#endif
	script_result = 0;
	// Entering game script
	run_script (2 * MAX_PANTS);
#endif

	paused = 0; update_list [0] = NT_UPD_EOF;

	while (1) {

		//*((unsigned char*)0x2001) = 0x1e;
		ppu_wait_frame ();
		//*((unsigned char*)0x2001) = 0x1f;
		
		half_life = 1 - half_life;		// Main flip-flop
		frame_counter ++;				// Increase frame counter
		//if (ticker) ticker --; else ticker = ticks;
	
		pad_read ();	

		// CUSTOM {
		if (psleeping) {
			if (pad_this_frame) {
				psleeping = 0;
				pj = 1; pctj = PLAYER_PRECALC_JUMP_STEPS >> 1;
				pad_this_frame = 0;
			}
		}
		// } END_OF_CUSTOM

		if (pwashit) player_hit ();

		// Press Fire At
#ifdef SCRIPTING_ON
		if (f_zone_ac) {
			if (pry >= fzy1 && pry <= fzy2)
				if (prx >= fzx1 && prx <= fzx2)
					game_run_fire_script ();
		}
#endif

		if (pad_this_frame & PAD_START) {
			paused = !paused;
			if (paused) pal_bright (3); else pal_bright (4);
			music_pause (paused);
			sfx_play (0, SC_LEVEL);
		}

		// Exit condition
		if (level && pobjs == max_hotspots_type_1) {
			game_state = GS_EXIT_WITH_DECO;
			break;
		}
		if (pkilled 
			|| (level == 0 && pry < 32 && n_pant == 2)
			|| ((pad0 & (PAD_SELECT | PAD_B | PAD_UP)) == (PAD_SELECT | PAD_B | PAD_UP))
		) {
			game_state = GS_EXIT;
			break;
		}
			
		#include "engine/mainloop/flick_screen.h"

		if (!paused) {
			ul = update_list;				// Reset pointer to update list
			oam_index = 44;					// Reset OAM index; skip sprite #0 & player
		
			pgotten = pgtmx = pgtmy = 0;

			hud_update (); 	

#ifdef ENABLE_PUAS
			puas_do ();
#endif
#ifdef PLAYER_CAN_FIRE
			bullets_do ();
#endif
#ifndef DISABLE_HOTSPOTS		
			hotspots_do ();
#endif		
#ifdef ENABLE_FABOLEES
			fabolee_do ();
#endif
#ifdef ENABLE_EXPLOSIONS
			expl_do ();
#endif

			enems_do ();
		
#ifdef ENABLE_COCOS		
			simplecoco_do ();
#endif		
#ifdef SHOOTING_DRAINS			
			flower_do ();
#endif
#ifdef BREAKABLE_WALLS
			breakable_do ();
#endif		

			// If both active, cataracts and estrujators are exclusive
#ifdef ENABLE_CATARACTS
			if (cataracts_on) cataracts_do ();
#ifdef ENABLE_ESTRUJATORS
			else
#endif
#endif
#ifdef ENABLE_ESTRUJATORS
			estrujators_do ();
#endif

			player_move ();	
			if (n_pant == on_pant) player_render ();

#ifdef ENABLE_FUMETTOS
			fumettos_do ();
#endif
#ifdef ENABLE_CONTAINERS
			containers_draw ();
#endif
#ifdef ENABLE_SPRINGS
			if (springs_idx) springs_do ();
#endif
#ifdef ENABLE_PROPELLERS
			if (propellers_idx) propellers_do ();
#endif			
		
#if defined (ENGINE_TYPE_NEW_GENITAL) && defined (PLAYER_JUMPS) && defined (PLAYER_SHADOW)
			if (!pholed) oam_index = oam_spr (prx, pry + 9 + SPRITE_ADJUST + (poverhole ? 16 : 0), PLAYER_SHADOW, 1, oam_index);
#endif			

#ifdef ENABLE_SHINES
			if (shw) shines_do ();
#endif

// CUSTOM {
			if (red) {
				red --;
				if (red == 0) { 
					pal_bg (l_pal_ts [level]); pal_spr (palss0); sfx_play (SFX_RING, SC_ROOM); 
					enems_persistent_deaths_init ();
					enems_load ();
					lightning = 0;
				}
			} else {
				if (custom_on_off & FLAG_LIGHTNING) {
					if (rand8 () == 1) {
						lightning = 16;
						sfx_play (SFX_THUNDER, SC_LEVEL);
					}

					if (lightning) {
						if (lightning == 16 || lightning == 8) { pal_bg (paltsl); pal_spr (palssl); }
						if (lightning == 12 || lightning == 4) { pal_bg (l_pal_ts [level]); pal_spr (palss0); }
						lightning --;
					}
				}
				if (custom_on_off & FLAG_RAIN) {
					for (gpit = half_life; gpit < rain_int; gpit += 2) {
						if (rain_c [gpit]) {
							rain_c [gpit] --;
							if (oam_index < 248) oam_index = oam_spr (rain_x [gpit], rain_y [gpit], 0xd-rain_c [gpit], 3, oam_index);
						} else { 
							rain_c [gpit] = 4; 
							rain_new (); 
						}
					}

					if (custom_on_off & FLAG_VARIABLE) {
						if (rain_intct) rain_intct --; else {
							rain_int += rain_intm;
							if (rain_int == 0) { rain_intm = 1; }
							else if (rain_int == RAIN_MAX_DROPS) rain_reset_int ();
							rain_intct = rain_intmaxct;
						}
					}
				}
			}
// } END_OF_CUSTOM

			oam_hide_rest (oam_index);
		}

		*ul = NT_UPD_EOF;
	}
	
	set_vram_update (0);
	
	// CUSTOM {
	// exit_cleanly ();

	if (levelseq < 10) music_stop ();

	if (game_state == GS_EXIT_WITH_DECO) {
		oam_hide_rest (44);
		psprid = 34; player_render (); 
		pal_bg_bright (3); delay (15);
		pal_bg_bright (2); delay (15);
		psprid = 35; player_render (); 
		pal_bg_bright (1); delay (15);
		pal_bg_bright (0); delay (45);
		delay (ticks);
	
		gpit = 4; while (gpit != 255) {
			pal_spr_bright (gpit);
			delay (4);
			gpit --;
		}

		oam_hide_rest (0);
		ppu_wait_nmi ();
		ppu_off ();
	} else {
		oam_hide_rest (0);
		fade_out ();
		ppu_off ();	
	}

	// } END_OF_CUSTOM
}

void game_title (void) {
	bankswitch (3);
	enter_screen (paltstitle, screen_title);
	pal_spr (palsstitle);
	music_play (MUSIC_TITLE);
	
	half_life = 0;

	while (1) {
		half_life = 1 - half_life;
		pad_read ();	
		if (pad_this_frame & PAD_START) break;

		oam_hide_rest (
			half_life ? 
			( 
				oam_meta_spr (
					104, 103,
					0,
					title_fg_00
				)
			)
			: 0
		);
		ppu_wait_nmi ();
	}

	music_stop ();
	sfx_play (SFX_START, SC_LEVEL);
	
	exit_cleanly ();
	delay (halfticks);

	bankswitch (0);
}

void game_over (void) {
	enter_screen (palcuts0, screen_game_over);
	signal_continue = 0;

	if (levelseq && pcontinues) {
		while (1) {
			pad_read ();

			if (pad_this_frame & PAD_RIGHT) {
				if (signal_continue) sfx_play (SFX_ENEMY_HIT, 0); signal_continue = 0;
			}

			if (pad_this_frame & PAD_LEFT) {
				if (!signal_continue) sfx_play (SFX_ENEMY_HIT, 0); signal_continue = 1;
			}

			if (pad_this_frame & (PAD_A|PAD_B|PAD_START)) { sfx_play (SFX_START, 0); break; }

			oam_hide_rest (oam_spr (signal_continue ? 88 : 160, 135, 0x12, 0, 0));
			ppu_wait_nmi ();
		}

		exit_cleanly ();
	} else do_screen (10);
}

void game_level (void) {
	enter_screen (palcuts0, screen_level);
	//music_play (MUSIC_GAME_OVER);
	do_screen (2);
}

void game_ending (void) {
	rdb = ticks << 1;
	bankswitch (3);
	set_vram_update (update_list);
	*update_list = NT_UPD_EOF;
	enter_screen (palcuts0, screen_game_ending);
	delay (rdb);
	rda = 0x6c;
	screen_ending_mod_update ();
	delay (ticks);
	screen_ending_mod_update ();
	delay (rdb);
	gp_addr = NAMETABLE_A + (20<<5) + 5;
	p_s_ul_s ("SO... IS THIS THE END?");
	delay (rdb);
	gp_addr = NAMETABLE_A + (20<<5);
	p_s_cl_l ();
	gp_addr = NAMETABLE_A + (20<<5) + 7;
	p_s_ul_s ("AM I REALLY AWAKE?");
	do_screen (255);
	set_vram_update (0);
	bankswitch (0);
}

void game_cuts (void) {
	bankswitch (3);
	enter_screen (palcuts0, screen_cuts);
	//music_play (MUSIC_TITLE);
	do_screen (10);
	bankswitch (0);
}

void game_intro (void) {
	rdb = ticks << 1;
	rdc = 0;
	bankswitch (3);
	bank_bg (1);
	set_vram_update (update_list);
	*update_list = NT_UPD_EOF;
	enter_screen (palcuts0, screen_intro);
	music_play (MUSIC_CUTS);
	
	breakable_ticks_wait ();
pal_col(0,0xf);
	screen_textcycle ("  CHERIL... CAN YOU HEAR ME?");
	screen_textcycle ("      FIND MY DAUGHTERS...");
	screen_textcycle ("      AND I\"LL RELEASE YOU");

	if (rdc == 0) do_screen (2); else exit_cleanly ();
	bank_bg (0);
	bankswitch (0);
}
