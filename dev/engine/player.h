// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement & stuff

#ifdef PLAYER_SAFE
void player_register_safe_spot (void) {
	safe_prx = prx; safe_pry = pry;
	safe_n_pant = n_pant;
}

void player_restore_safe_spot (void) {
	prx = safe_prx; px = prx << FIX_BITS;
	pry = safe_pry; py = pry << FIX_BITS;
	n_pant = safe_n_pant;	
}
#endif

#ifdef ENABLE_HOLES
void player_holed (void) {
	pholed = 48; 
	pvx = ADD_SIGN(pvx, PLAYER_V_INERTIA_X);
	pvy = ADD_SIGN(pvy, PLAYER_V_INERTIA_Y);
	pad = 0;
	sfx_play (SFX_BUTT_FALL, SC_PLAYER);
}
#endif

void player_reset_movement (void) {
	pvx = pvy = 0;
#ifdef PLAYER_CAN_FIRE
	pfixct_fire = pfiring = 0;
#endif
	phit = 0;
	pvylast = 0;
#ifdef PLAYER_JUMPS	
	pj = pjustjumped = 0;
#endif
#ifdef PLAYER_JETPAC	
	pthrust = 0;
#endif
#ifdef PLAYER_SPINS	
	pspin = 0;
#endif	
#ifdef PLAYER_BUTT
	pbutt = 0;
#endif
#ifdef ENABLE_HOLES
	pholed = 0;
#endif
#ifdef ENABLE_FUMETTOS
	thrustct = 0;
#endif
#ifdef ENABLE_WATER
	pwater = 0;
#endif
#ifdef PLAYER_FLOATS
	pfloat = 0;
#endif
}

#if defined (PLAYER_PUSH_BOXES) || defined (HOTSPOT_TYPE_KEY)
void prepare_process_block_vars (void) {
	if (by0) by0 --;
	if (by1) by1 --;
	rdf = bx0 | (by0 << 4);
	rde = bx1 | (by1 << 4);
}
#endif

#ifdef PLAYER_PUSH_BOXES
void player_push_box (void) {
	// Push box
	prepare_process_block_vars ();
	
	if (bx0 == 0 || bx0 == 15 || by0 == 0 || by0 == 11) return;

	if (0 == scr_attr [rde]) {
		
		sfx_play (SFX_BUTT_HIT, SC_LEVEL);

#ifdef FLOATY_PUSH_BOXES
		// Get which push box!
		rdd = rdt = scr_attr [rdf] >> 4;

		// Draw it in the new position
		rdx = (bx1 << 1); rdy = (by1 << 1) + TOP_ADJUST;
		update_list_tile ();

		// Copy attribute to new position
		scr_attr [rde] = scr_attr [rdf];

		// Now delete it
		set_map_tile (bx0, by0, scr_buff [rdf]);

#ifdef ENABLE_TOUCHPLATES
		if (c_tp_defs) {
			rda = scr_buff [rde]; 			// Tile in destination cell
			if (rdb = c_tp_defs [rda]) {	// If it's a touchplate
				if (c_tp_defs [rdd] == 0 || c_tp_defs [rdd] == rda) {
					
					// If the push block activates any or that touchplate,
					sfx_play (SFX_TU, SC_PLAYER);

					// Fix pushbox so it can no longer be moved
					scr_attr [rde] = 8;

					// Decrease related bolt's "life"
					bolts_decrease_life ();
				}
			}
		}
#endif

#else		
		set_map_tile (bx0, by0, 0); 
		set_map_tile (bx1, by1, scr_buff [rdf]);
#endif		

	}
}
#endif

#if defined (HOTSPOT_TYPE_KEY) 
void player_push_bolt (void) {
	// Key hole
	prepare_process_block_vars ();

#ifdef SPECIAL_BOLTS
	if (scr_buff [rdf] != KEY_HOLE_BOLT) return;
#endif	
	
	if (pkeys) {
		pkeys --;
		bolts_clear_bolt ();
		set_map_tile (bx0, by0, 0);
		sfx_play (SFX_CHOF, SC_LEVEL);
	}
}
#endif

void player_init (void) {
	// Init player data
	prx = (signed int) (player_ini_x [level] << 4); px = prx << FIX_BITS;
	pry = (signed int) (player_ini_y [level] << 4); py = pry << FIX_BITS;

#ifdef PLAYER_SAFE
	player_register_safe_spot ();
#endif
	
#ifdef PLAYER_GENITAL
	pfacing = pfacingv = CELL_FACING_DOWN;		
	pfacinglast = pfacingh = CELL_FACING_RIGHT;
#else
	pfacing = CELL_FACING_RIGHT;
#endif

	player_reset_movement ();
	pkilled = 0;

	// CUSTOM {
	// psprid = 0;
	// } END_OF_CUSTOM

#ifdef PLAYER_FLICKERS
	pflickering = 0;
#endif	
}

void player_render (void) {
#if defined (ENGINE_TYPE_NEW_GENITAL) && defined (PLAYER_JUMPS)
	rdy = pry; if (pj) rdy -= player_precalc_jump [pctj];
	if (!pflickering || half_life) {
		oam_meta_spr (prx, rdy + SPRITE_ADJUST, 20, spr_player [psprid]);	
	} else {
		oam_meta_spr (prx, rdy + SPRITE_ADJUST, 20, ssplempty);
	}
#else
	if (!pflickering || half_life) {
		oam_meta_spr (prx, pry + SPRITE_ADJUST, 20, spr_player [psprid]);	
	} else {
		oam_meta_spr (prx, pry + SPRITE_ADJUST, 20, ssplempty);
	}
#endif

#ifdef PLAYER_NO
	if (no_ct) {
		no_ct --;
		oam_index = oam_meta_spr (
			prx + 2, pry - 24 + SPRITE_ADJUST,
			oam_index,
			SPRITE_NO
		);
	}
#endif
}

void player_hit (void) {
	sfx_play (SFX_ENEMY_HIT, SC_PLAYER);

	close_update_cycle ();

#ifdef PLAYER_DIE_AND_RESPAWN
	//player_render ();
	pad0 = 0;
	music_pause (1);
	delay (60);
	music_pause (0);
	player_reset_movement ();
	player_restore_safe_spot ();
#endif

#ifdef ENABLE_HOLES
	if (pholed) {
		player_reset_movement ();
		player_restore_safe_spot ();
		pholed = 0;
		poverhole = 0;
	}
#endif

#ifdef PLAYER_FLICKERS
	pflickering = PLAYER_FLICKERS;
#endif
	
	if (plife) {
		plife --;
	} else {
		pkilled = 1;
	}
	
	phit = PLAYER_HIT_FRAMES;

	pwashit = 0;
}

void player_move (void) {

	// Controls player state (phit, pflickering, pfixct_*)
	// Contains use_ct / guay_ct stuff
	// Initializes stuff
	// Copies pad0 into pad if suited.
	#include "engine/player_mods/initial_checks.h"

	// Vertical axis. Controls movement in the vertical axis.
	// Choose which code to include depending on the selected engine.
#if defined (ENGINE_TYPE_CLASSIC)
	// Gravity, pad polling, movement, collision,
	// Floor detections (side view), jumping.
	#include "engine/player_mods/vertical_axis_classic.h"
#elif defined (ENGINE_TYPE_NEW_GENITAL)
#ifdef PLAYER_JUMPS
	#include "engine/player_mods/jump_new_genital_init.h"
#endif
	// Pad polling, movement, collision.
	#include "engine/player_mods/vertical_axis_new_genital.h"
#endif

	// Horizontal axis. Controls movement in the horizonta axis.
	// Choose which code to include depending on the selected engine.
#if defined (ENGINE_TYPE_CLASSIC)
	// pad polling, movement, collision, solve facing (top-down)
	#include "engine/player_mods/horizontal_axis_classic.h"
#elif defined (ENGINE_TYPE_NEW_GENITAL)
	// pad polling, movement, collision, solve facing (top-down)
	#include "engine/player_mods/horizontal_axis_new_genital.h"
#ifdef PLAYER_JUMPS
	#include "engine/player_mods/jump_new_genital_do.h"
#endif
#endif
	
	// Center point detections:
	// Evil tile detection (center), water, tile_get, etc
#ifdef ENGINE_TYPE_CLASSIC
	#include "engine/player_mods/center_point_classic.h"
#endif	

	// Evil tile reaction. Evil tile is detected before
	// (different ways), and the reaction to detection
	// is performed here:
#if defined (ENGINE_TYPE_CLASSIC)
	#include "engine/player_mods/evil_tile_classic.h"
#elif defined (ENGINE_TYPE_NEW_GENITAL)
	#include "engine/player_mods/evil_tile_new_genital.h"
#endif

	// Extra stuff
#ifdef ENGINE_TYPE_CLASSIC
	// Hidden, spinning, float, butt, hitter.	
	#include "engine/player_mods/extra_stuff_classic.h"
#endif

	// Fire button
	#include "engine/player_mods/fire_button.h"	

	// Sprite cell selection is usually pretty custom...
	#include "engine/player_mods/cell_selection.h"
}
