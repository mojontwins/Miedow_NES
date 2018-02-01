// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Enems

#ifdef PERSISTENT_ENEMIES
void persistent_enems_load (void) {
#ifdef ENEMS_FORMAT_UNPACKED
	gp_gen = (unsigned char *) (c_enems);
	for (ep_it = 0; ep_it < 3 * MAX_PANTS; ep_it ++) {

#ifdef LINEAR_NEW_GENITAL_SUBSTRACT
		rdt = *gp_gen ++;
#else
		// Skip t
		gp_gen ++;
#endif

		// YX1
		rda = *gp_gen ++;
		ep_y [ep_it] = rda & 0xf0;
		ep_x [ep_it] = (rda << 4);

		// YX2
		rda = *gp_gen ++;
		rdc = rda & 0xf0;
		rdb = rda << 4;

#ifdef LINEAR_NEW_GENITAL_SUBSTRACT
		if ((rdt & 0xf0) == 0x10) {
			ep_y [ep_it] -= LINEAR_NEW_GENITAL_SUBSTRACT;
			rdc -= LINEAR_NEW_GENITAL_SUBSTRACT;
		}
#endif

		// P, here used for speed
		rda = *gp_gen ++;
		if (rda > 1) rda >>= 1;
		ep_mx [ep_it] = ADD_SIGN2 (rdb, ep_x [ep_it], rda);
		ep_my [ep_it] = ADD_SIGN2 (rdc, ep_y [ep_it], rda);		
	}
#else
	gpit = MAX_PANTS; while (gpit --) {
		ep_it = gpit + gpit + gpit; //gpit + (gpit << 1);
		
		//if (gp_gen = (unsigned char *) (c_enems [gpit]))

		gp_gen = (unsigned char *) (c_enems [gpit]);
		if (gp_gen != 0) {
			gpjt = 3; while (gpjt --) {
				rdt = *gp_gen ++;
				if (!rdt) break;

				// YX1
				rda = *gp_gen ++;
				ep_y [ep_it] = rda & 0xf0;
				ep_x [ep_it] = (rda << 4);

				// YX2
				rda = *gp_gen ++;
				rdc = rda & 0xf0;
				rdb = rda << 4;

#ifdef LINEAR_NEW_GENITAL_SUBSTRACT
				if ((rdt & 0xf0) == 0x10) {
					ep_y [ep_it] -= LINEAR_NEW_GENITAL_SUBSTRACT;
					rdc -= LINEAR_NEW_GENITAL_SUBSTRACT;
				}
#endif

				// P, here used for speed
				rda = *gp_gen ++;
				if (rda > 1) rda >>= 1;
				ep_mx [ep_it] = ADD_SIGN2 (rdb, ep_x [ep_it], rda);
				ep_my [ep_it] = ADD_SIGN2 (rdc, ep_y [ep_it], rda);

				ep_it ++;
			}
		}	
	}
#endif
}

void persistent_update (void) {
	if (on_pant != 99) {
		for (gpit = 0; gpit < 3; gpit ++) {
			ep_x [enoffs] = en_x [gpit];
			ep_y [enoffs] = en_y [gpit];
			ep_mx [enoffs] = en_mx [gpit];
			ep_my [enoffs] = en_my [gpit];	
			enoffs ++;		
		}	
	}
}
#endif

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)
void enems_persistent_deaths_init (void) {
	gpit = MAX_PANTS * N_ENEMS; while (gpit --) ep_killed [gpit] = 0;
}
#endif

void enems_load (void) {

#ifdef ENEMS_FORMAT_UNPACKED	
	// Each screen holds 3 enemies, each enemy takes 4 bytes, so:
	gp_gen = (unsigned char *) (c_enems + (n_pant << 3) + (n_pant << 2));
#elif defined (ENEMS_FORMAT_COMPACTED)
	// There's a nice index
	rdct = 1;
	gp_gen = (unsigned char *) (c_enems [n_pant]);
	if (!gp_gen) rdct = 0;
#endif

#if defined (PERSISTENT_DEATHS) || defined (PERSISTENT_ENEMIES)
	rdc = enoffs = n_pant + n_pant + n_pant;
#endif
	for (gpit = 0; gpit < 3; gpit ++) {
#ifdef ENEMS_FORMAT_COMPACTED
		if (!rdct) {
			en_t [gpit] = 0;
			continue;
		}
#endif

#if defined(ENEMIES_CAN_DIE) && defined(PERSISTENT_DEATHS)	

#ifdef ENABLE_ESPECTROS
#else
		// Kill enemy
		if (ep_killed [rdc]) {
			en_t [gpit] = 0;	// Inactive
			gp_gen += 4; 		// Next enemy
		} else 
#endif


#endif		
		{
			// T YX1 YX2 P
			// Type 
			rda = *gp_gen ++;
#ifdef ENEMS_FORMAT_COMPACTED
			if (!rda) {
				en_t [gpit] = 0;
				rdct = 0;
				continue;
			}
#endif

#ifdef ENABLE_ESPECTROS
			if (ep_killed [rdc]) en_t [gpit] = 0x60; else 			
#endif
			en_t [gpit] = rda; 

			en_s [gpit] = (en_t [gpit] & 0x0f) << 2;
			rdt = en_t [gpit] & 0xf0;

#ifdef PERSISTENT_ENEMIES
			// YX1
			rdb = *gp_gen ++;
			en_x1 [gpit] = rdb << 4;
			en_y1 [gpit] = rdb & 0xf0;

			// YX2
			rdb = *gp_gen ++;
			en_x2 [gpit] = rdb << 4;
			en_y2 [gpit] = rdb & 0xf0;

#ifdef LINEAR_NEW_GENITAL_SUBSTRACT
			if ((rdt & 0xf0) == 0x10) {
				en_y1 [gpit] -= LINEAR_NEW_GENITAL_SUBSTRACT;
				en_y2 [gpit] -= LINEAR_NEW_GENITAL_SUBSTRACT;
			}
#endif

			// Attribute
			rdb = *gp_gen ++;

			// But...
			en_x [gpit] = ep_x [rdc];
			en_y [gpit] = ep_y [rdc];
#else
			// YX1
			rdb = *gp_gen ++;
			en_x1 [gpit] = en_x [gpit] = rdb << 4;
			en_y1 [gpit] = en_y [gpit] = rdb & 0xf0;

			// YX2
			rdb = *gp_gen ++;
			en_x2 [gpit] = rdb << 4;
			en_y2 [gpit] = rdb & 0xf0;


#ifdef LINEAR_NEW_GENITAL_SUBSTRACT
			if ((rdt & 0xf0) == 0x10) {
				en_y1 [gpit] -= LINEAR_NEW_GENITAL_SUBSTRACT;
				en_y2 [gpit] -= LINEAR_NEW_GENITAL_SUBSTRACT;
				en_y [gpit] -= LINEAR_NEW_GENITAL_SUBSTRACT;
			}
#endif

			// Attribute
			rdb = *gp_gen ++;
#endif
			en_state [gpit] = 0;
			en_life [gpit] = ENEMS_GENERAL_LIFE;

			// Define as per type
			switch (rdt) {
#ifdef ENABLE_LINEAR
				case 0x10:
				case 0x20:
					
					
#ifdef PERSISTENT_ENEMIES
					en_mx [gpit] = ep_mx [rdc];
					en_my [gpit] = ep_my [rdc];
					if (rdb == 1) {
						en_state [gpit] = 1;
					} 
#else
					if (rdb == 1) {
						en_state [gpit] = 1;
					} else {
						rdb >>= 1;
					}
					en_mx [gpit] = ADD_SIGN2 (en_x2 [gpit], en_x1 [gpit], rdb);
					en_my [gpit] = ADD_SIGN2 (en_y2 [gpit], en_y1 [gpit], rdb);
#endif

					// This comes handy when jumping on enemies
#ifdef PLAYER_STEPS_ON_ENEMIES
					if (en_y1 [gpit] > en_y2 [gpit]) {
						rda = en_y1 [gpit]; en_y1 [gpit] = en_y2 [gpit]; en_y2 [gpit] = rda;
					}
#endif
					break;
#endif
#ifdef ENABLE_FANTY
				case 0x30:
#ifdef FANTY_REPOSITION_NONETHELESS
					enf_x [gpit] = en_x1 [gpit] << FIX_BITS;
					enf_y [gpit] = en_y1 [gpit] << FIX_BITS;
#else
					enf_x [gpit] = en_x [gpit] << FIX_BITS;
					enf_y [gpit] = en_y [gpit] << FIX_BITS;
#endif
					enf_vy [gpit] = 0;
					enf_vx [gpit] = (en_x1 [gpit] < 128) ? -(FANTY_MAXV+FANTY_MAXV) : FANTY_MAXV+FANTY_MAXV;
					fanty_timer [gpit] = FANTY_TIMER_BASE;
					break;					
#elif defined (ENABLE_PRECALC_FANTY) || defined (ENABLE_PRECALC_HOMING_FANTY)
				case 0x30:
#ifdef FANTY_REPOSITION_NONETHELESS
					en_x [gpit] = en_x1 [gpit];
					en_y [gpit] = en_y1 [gpit];
#endif
					en_mx [gpit] = en_my [gpit] = 0;
#ifdef FANTY_LIFE;					
					en_life [gpit] = FANTY_LIFE;
#endif					
					break;
#elif defined (ENABLE_PRECALC_TIMED_FANTY)
				case 0x30:
					en_x [gpit] = en_x1 [gpit];
					en_y [gpit] = en_y1 [gpit];
					en_mx [gpit] = en_my [gpit] = 0;
					fanty_timer [gpit] = FANTY_TIMER_BASE;
					break;
#endif				


#ifdef ENABLE_CATACROCK
				case 0x40:
#ifdef PERSISTENT_ENEMIES
					en_y [gpit] = en_y1 [gpit];
#endif
					CATACROCK_WAIT [gpit] = CATACROCK_COUNTER [gpit] = rdb << 5;	// In frames
					break;
#endif
#ifdef ENABLE_GENERATONIS
				case 0x50:
					en_s [gpit] = (en_t [gpit] & 0x0f) << 2;
					GENERATONI_WAIT [gpit] = 31 + (rdb << 5);
					GENERATONI_COUNTER [gpit] = 0;
					en_y [gpit] = en_y1 [gpit]; en_x [gpit] = en_x1 [gpit];
					break;
#endif
#ifdef ENABLE_ESPECTROS
				case 0x60:
					enf_x [gpit] = en_x1 [gpit] << FIX_BITS;
					enf_y [gpit] = en_y1 [gpit] << FIX_BITS;
					enf_vx [gpit] = enf_vy [gpit] = 0;
					break;
#endif
#ifdef ENABLE_TYPE7				
				case 0x70:
#ifdef TYPE7_WITH_GENERATOR				
					en_gen_life [gpit] = TYPE7_GENERATOR_LIFE;
					en_gen_washit [gpit] = 0;
#endif					
					en_ct [gpit] = TYPE7_SPAWN_TIME;
					//infested ++;
					break;
#endif
#ifdef ENABLE_STEADY_SHOOTER
				case 0x80:
					// Let's calculate where to shoot at: 
					rda = ADD_SIGN2 (en_x2 [gpit], en_x1 [gpit], 1);
					if (rda) 
						STEADY_SHOOTER_DIRECTION [gpit] = rda + 1; 
					else 
						STEADY_SHOOTER_DIRECTION [gpit] = ADD_SIGN2 (en_y2 [gpit], en_y1 [gpit], 1) + 2;
					en_s [gpit] = STEADY_SHOOTER_CELL + en_my [gpit];
					// Seconds between shoots.
					STEADY_SHOOTER_WAIT [gpit] = rdb;	
					en_ct [gpit] = rdb; 
					break;
#endif
#ifdef ENABLE_MONOCOCO
				case 0x90:
					MONOCOCO_COUNTER [gpit] = MONOCOCO_BASE_TIME_HIDDEN - (rand8 () & 0x15);
					break;
#endif
#ifdef ENABLE_WALKER
				case 0xa0:
					en_facing [gpit] = 4;
					break;
#elif defined (ENABLE_PRECALC_PEZON)
				case 0xa0:
					PEZON_TIMER [gpit] = PEZON_MAX_TIME [gpit] = PEZON_WAIT + (rdd << 3); 
					break;
#endif
#ifdef ENABLE_GYROSAW
				case 0xb0:
					GYROSAW_COUNTER [gpit] = 0; 		// Counter
					GYROSAW_DIRECTION [gpit] = rdb; 	// clockwise = 1; counter-clockwise = 0
					en_x [gpit] = en_x1 [gpit];
					en_y [gpit] = en_y1 [gpit];
					break;
#elif defined (ENABLE_SAW)
				case 0xb0:
					// About SAWs:
					
					// It will emerge upwards/downwards / leftwards/rightwards depending on (en_t [gpit] & 0x0f):
					// 0 is negative (up/left); 2 is positive (down/right). So type can be 0xB0 or 0xB2.
					SAW_EMERGING_DIRECTION [gpit] = (en_t [gpit] & 0x0f) - 1;
					
					// Orientation / direction of momement when the saw is OUT is defined by the trajectory in "ponedor.exe".
					rda = (en_x1 [gpit] == en_x2 [gpit]);
					SAW_MOVING_DIRECTION [gpit] = (rda) ? 
						SGNC (en_y2 [gpit], en_y1 [gpit], SAW_V_DISPL) : 
						SGNC (en_x2 [gpit], en_x1 [gpit], SAW_V_DISPL);
					SAW_ORIENTATION [gpit] = rda;
					
					en_ct [gpit] = SAW_EMERGING_STEPS;

					break;					
#endif

#ifdef ENABLE_LAME_BOSS_1
				case 0xf0:
					en_mx [gpit] = -1;
					en_state [gpit] = 0;
					en_life [gpit] = 3;
					break;
#endif

#ifdef ENABLE_VIRAS
				case 0xf0:
					en_mx [gpit] = en_my [gpit] = 0;
					en_life [gpit] = 3;
					break;
#endif

			}

			// Finally
			en_washit [gpit] = 0;

#ifdef ENEMS_UPSIDE_DOWN
			en_ud [gpit] = 0;
#endif
		}
#if defined (PERSISTENT_DEATHS) || defined (PERSISTENT_ENEMIES)
		rdc ++;
#endif
	}
}

#ifdef ENEMIES_CAN_DIE

void enems_kill (void) {
	sfx_play (SFX_BUTT_HIT, SC_LEVEL);
	rdt = en_t [gpit] = 0;
#ifdef PERSISTENT_DEATHS	
	ep_killed [enoffs + gpit] = 1;
#endif

#ifdef COUNT_KILLED_ON_FLAG
	flags [COUNT_KILLED_ON_FLAG] ++;
#endif
	pbodycount ++;

#ifdef ENABLE_FABOLEES
	rdd = FABOLEES_MAX; while (rdd --) if (fbl_lock_on [rdd] == gpit) fbl_ct [rdd] = 0;
#endif
}

void enems_drain (void) {
	if (_en_washit) return;

	rdx = _en_x; rdy = _en_y; rde = 1; expl_create ();

#ifdef ENEMS_MIN_KILLABLE	
	if (_en_t < ENEMS_MIN_KILLABLE) return;	// Very, very bad
#endif	

#ifdef ENABLE_ESPECTROS
	if (rdt == 0x60) { sfx_play (SFX_BUTT_HIT, SC_LEVEL); _en_state = 3; _en_ct = ticks; return; }  
#endif

#if ENEMS_GENERAL_LIFE > 1
	sfx_play (SFX_BUTT_HIT, SC_LEVEL);
	
	_en_washit = ENEMS_GENERAL_HIT_FRAMES;

	if (en_life [gpit]) {
		en_life [gpit] --;
	} else {
		if (rdt <= 0x30) {
			_en_washit = 0;

			// Create explosion:
			rdx = _en_x; rdy = _en_y; rde = 2;
			expl_create ();
					
			enems_kill (); // Euh...
		} else if (rdt == 0x70) {
			_en_state = 0;
			_en_ct = TYPE7_SPAWN_TIME;
		}
	}
#else
	_en_washit = 0;
	
	// Create explosion:
	rdx = _en_x; rdy = _en_y; rde = 2;
	expl_create ();

	enems_kill (); 
#endif	
}

#endif

#ifdef ENABLE_TYPE7
#ifdef TYPE7_WITH_GENERATOR
void enems_draw_generator (void) {
	// Add generator
	if (genflipflop) oam_index = oam_meta_spr (
		en_x1 [gpit], en_y1 [gpit] + SPRITE_ADJUST, 
		oam_index, 
		spr_enems [TYPE7_BASE_SPRITE + !!en_gen_washit [gpit]]);
	genflipflop = 1 - genflipflop;
}
#endif
#endif

void enems_restore_vals (void) {
	en_x [gpit] = _en_x; en_y [gpit] = _en_y;
	en_mx [gpit] = _en_mx; en_my [gpit] = _en_my;
	en_ct [gpit] = _en_ct;
	en_state [gpit] = _en_state;
#ifdef ENEMS_UPSIDE_DOWN
	en_ud [gpit] = _en_ud;
#endif
#ifdef ENEMIES_NEED_FP
	enf_x [gpit] = _enf_x; enf_y [gpit] = _enf_y;
	enf_vx [gpit] = _enf_vx; enf_vy [gpit] = _enf_vy;
#endif	
#ifdef ENEMIES_CAN_DIE
	en_washit [gpit] = _en_washit;
#endif
}

void enems_do (void) {
	genflipflop = half_life;
	gpit = (frame_counter & 3);
	gpjt = 3; while (gpjt --) {
		gpit = gpit + 2; if (gpit > 2) gpit -= 3;

		// Consider this a sort of "local copy"
		
		_en_t = en_t [gpit];
		_en_x = en_x [gpit]; _en_y = en_y [gpit];
		_en_x1 = en_x1 [gpit]; _en_y1 = en_y1 [gpit];
		_en_x2 = en_x2 [gpit]; _en_y2 = en_y2 [gpit];
		_en_mx = en_mx [gpit]; _en_my = en_my [gpit];
		_en_state = en_state [gpit];
		_en_ct = en_ct [gpit];
#ifdef ENEMS_UPSIDE_DOWN
		_en_ud = en_ud [gpit];
#endif
#ifdef ENEMIES_NEED_FP
		_enf_x = enf_x [gpit]; _enf_y = enf_y [gpit];
		_enf_vx = enf_vx [gpit]; _enf_vy = enf_vy [gpit];
#endif		
#ifdef ENEMIES_CAN_DIE
		_en_washit = en_washit [gpit];
#endif
	
		// End of copy. Now use the copies.

#ifdef ENEMIES_CAN_DIE
		if (_en_washit) _en_washit --;
#endif		

		rdt = _en_t & 0xf0;
		if (rdt) {
#if defined (ENABLE_PLATFORMS) || defined (PLAYER_STEPS_ON_ENEMIES)
			is_platform = (rdt == 0x20);
			rda = _en_x;
			pregotten = (prx + 9 >= rda && prx <= rda + 17);
#endif

			// Animate (for some types)

			if (_en_mx != 0) {
				en_fr = ((_en_x + 4) >> 4) & 1;
			} else {
				en_fr = ((_en_y + 4) >> 4) & 1;
			}

			// Upside down

#ifdef ENEMS_UPSIDE_DOWN
			if (_en_ud) {
				rda = frame_counter & 0xf;
				oam_index = oam_meta_spr (
					_en_x + jitter [rda], _en_y + SPRITE_ADJUST + jitter [15 - rda], 
					oam_index, 
					spr_enems [en_s [gpit] + UPSIDE_DOWN_OFFSET + ((frame_counter >> 4) & 1)]);

				cx1 = (_en_x + 4) >> 4;
				cx2 = (_en_x + 11) >> 4;
				cy1 = cy2 = (_en_y + 15) >> 4;
				cm_two_points ();
				if (IS_UPSIDE_DOWN_STOPPER(at1|at2)) {
					if (rdt == 0x90) enems_drain ();
				} else {
					_en_y ++;
				}

				if (CL (prx, pry, _en_x, _en_y)) {
					if (pad0 & PAD_A) {
						pj = 1; pctj = 0; 
						pvy = -PLAYER_VY_JUMP_INITIAL;
					} else pvy = -PLAYER_VY_JUMP_FROM_ENEM;

					enems_drain ();
				} 

				enems_restore_vals ();
				continue;
			} 
#endif

			switch (rdt) {
#ifdef ENABLE_LINEAR				
				case 0x10:
				case 0x20:
					#include "engine/enemmods/enem_linear.h"
					break;
#endif

#ifdef ENABLE_FANTY
				case 0x30:
					#include "engine/enemmods/enem_fanty.h"
					break;
#elif defined(ENABLE_PRECALC_HOMING_FANTY)					
				case 0x30:
					#include "engine/enemmods/enem_precalc_homing_fanty.h"
					break;
#elif defined(ENABLE_PRECALC_FANTY)
				case 0x30:
					#include "engine/enemmods/enem_precalc_fanty.h"
					break;
#elif defined (ENABLE_PRECALC_TIMED_FANTY)
				case 0x30:
					#include "engine/enemmods/enem_precalc_timed_fanty.h"
					break;					
#endif

#ifdef ENABLE_CATACROCK
				case 0x40:
					#include "engine/enemmods/enem_catacrock.h"
					break;
#endif

#ifdef ENABLE_GENERATONIS
				case 0x50:
					#include "engine/enemmods/enem_generatoni.h"
					break;
#endif

#ifdef ENABLE_ESPECTROS
				case 0x60:
					#include "engine/enemmods/enem_espectro.h"
					break;
#endif

#ifdef ENABLE_TYPE7				
				case 0x70:
#ifdef TYPE7_WITH_GENERATOR				
					enems_draw_generator ();
#endif					
					#include "engine/enemmods/enem_type_7.h"
					break;
#endif

#ifdef ENABLE_STEADY_SHOOTER
				case 0x80:
					#include "engine/enemmods/enem_steady_shooter.h"
					break;
#endif

#ifdef ENABLE_MONOCOCO
				case 0x90:
					#include "engine/enemmods/enem_monococo.h"
					break;
#endif

#ifdef ENABLE_WALKER					
				case 0xa0:
					#include "engine/enemmods/enem_walker.h"
					break;
#elif defined (ENABLE_PRECALC_PEZON)
				case 0xa0:
					#include "engine/enemmods/enem_precalc_pezon.h"
					break;
#endif

#ifdef ENABLE_GYROSAW
				case 0xb0:
					#include "engine/enemmods/enem_gyrosaw.h"
					break;
#elif defined (ENABLE_SAW)
				case 0xb0:
					#include "engine/enemmods/enem_saw.h"
					break;					
#endif

#ifdef ENABLE_LAME_BOSS_1
				case 0xf0:
					#include "engine/enemmods/enem_lame_boss_1.h"
					break;
#elif defined (ENABLE_VIRAS)
				case 0xf0:
					#include "engine/enemmods/enem_viras.h"
					break;
#endif

			}

			// Paint

#if defined (ENABLE_TYPE7) && defined (TYPE7_WITH_GENERATOR)
			if (rdt == 0x70) enems_draw_generator ();
#endif		

			if (spr_id != 0xff) oam_index = oam_meta_spr (
				_en_x, _en_y + SPRITE_ADJUST, 
				oam_index, 
				spr_enems [spr_id]);

			// Moving platforms

#ifdef ENABLE_PLATFORMS			
			if (is_platform) {
				if (pregotten && !pgotten && !(pj && pvy <= 0)) {
					// Horizontal moving platforms
					if (_en_mx) {
						if (pry + 18 >= _en_y && pry + 12 <= _en_y) {
							pgotten = 1;
							pgtmx = _en_mx << (FIX_BITS - _en_state);
							pry = _en_y - 16; py = pry << FIX_BITS;
							pvy = 0;
						}
					}
					
					// Vertical moving platforms
					if (
						(_en_my < 0 && pry + 17 >= _en_y && pry + 12 <= _en_y) ||
						(_en_my > 0 && pry + 16 + _en_my >= _en_y && pry + 12 <= _en_y)
					) {
						pgotten = 1;
						pgtmy = _en_my << (FIX_BITS - _en_state);
						pry = _en_y - 16; py = pry << FIX_BITS;
						pvy = 0;
					}
				}

				enems_restore_vals ();
				continue;
			}
#endif

			// Enems <-> Evil tile collision handling

#ifdef ENEMS_DIE_ON_EVIL_TILE
			// attr at the middle of the 16x16 sprite. Unreadably optimized.
			if (
				(scr_attr [((_en_y - 7) & 0xf0) | ((_en_x + 7) >> 4)] & 1)
				&& (
	#ifdef ENABLE_LINEAR
					rdt == 0x10
	#endif

	#if defined (ENABLE_FANTY) || defined (ENABLE_PRECALC_HOMING_FANTY) || defined (ENABLE_PRECALC_FANTY) || defined (ENABLE_PRECALC_TIMED_FANTY)
					|| rdt == 0x30
	#endif

	#ifdef ENABLE_LAME_BOSS_1
					|| (rdt == 0xf0 && _en_state != 2)
	#endif

				)
			) {
	#ifdef ENABLE_LAME_BOSS_1
				if (rdt == 0xf0) _en_y -= LAME_BOSS_HIT_DISPLACEMENT;
	#endif
				enems_drain (); 
				enems_restore_vals ();
				continue;
			}
#endif		

			// Enems <-> Player collision handling

#ifdef PLAYER_STEPS_ON_ENEMIES
			if (pregotten && pry + 15 >= _en_y && pry + 8 <= _en_y
				&& pvy >= 0
	#ifdef PLAYER_BUTT
				&& pbutt
	#endif

	#if defined (ENABLE_SAW) || defined (ENABLE_GYROSAW)
				&& rdt != 0xb0 
	#endif
			) {

	#ifdef PLAYER_JUMPS_ON_ENEMIES
				if (pad0 & PAD_A) {
					pj = 1; pctj = 0; 
					pvy = -PLAYER_VY_JUMP_INITIAL;
				} else
	#endif
				pvy = -PLAYER_VY_BUTT_REBOUND;

	#ifdef PLAYER_DOUBLE_JUMP
				njumps = 1;
	#endif

	#ifdef ENABLE_FUMETTOS				
				fumettos_add ();
	#endif				
				sfx_play (SFX_BUTT_HIT, SC_LEVEL);

				// Affect enemies
				switch (rdt) {
					case 0x10:
						_en_my = ABS (_en_my);
						break;

	#if defined (ENABLE_PRECALC_FANTY) || defined (ENABLE_PRECALC_HOMING_FANTY) || defined (ENABLE_PRECALC_TIMED_FANTY)
					case 0x30:
						_en_my = FANTY_INCS_MAX - 1;
						break;
	#endif

	#ifdef ENABLE_LAME_BOSS_1
					case 0xf0:
						_en_y += LAME_BOSS_HIT_DISPLACEMENT;
						break;
	#endif
				}

	#ifdef PLAYER_STEPS_KILLS
		#ifdef KILLABLE_CONDITION
				if (KILLABLE_CONDITION)
		#endif
				{
					enems_drain ();
					enems_restore_vals ();
					continue;
				}
	#endif
			} else 
#endif	

			if (
				CL (prx, pry, _en_x, _en_y)
#ifdef ENABLE_MONOCOCO
				&& (rdt != 0x90 || en_state [gpit] == 2)
#endif
#ifdef ENABLE_CATACROCK
				&& (rdt != 0x40 || en_state [gpit] == 1)
#endif
#ifdef ENABLE_GENERATONIS
				&& (rdt != 0x50 || en_state [gpit])
#endif
#ifdef ENABLE_TYPE7
				&& (rdt != 0x70 || _en_state)
#endif
#ifdef ENABLE_LAME_BOSS_1
				&& (rdt != 0xf0 || _en_state == 1)
#endif
#ifdef ENABLE_ESPECTROS
				&& (rdt != 0x60 || _en_state == 1)
#endif

// New genital jump safe zone
#if defined (ENGINE_TYPE_NEW_GENITAL) && defined (PLAYER_JUMPS)
				&& (
					pj == 0 || (
						pctj < PLAYER_PRECALC_JUMP_SAFE_ZONE0 || 
						pctj > PLAYER_PRECALC_JUMP_SAFE_ZONE1
					)
				)
#endif

			) {
#ifdef PLAYER_SPINS_KILLS
				if ((pjustjumped || pspin)
				) {
					pvy = -pvy;
					enems_drain ();
					enems_restore_vals ();
					continue;
				} else
#endif			
				if (	
#ifdef PLAYER_FLICKERS
					!pflickering
#endif
				) {
					
#ifdef PLAYER_REBOUNDS					
	#ifdef PLAYER_REBOUND_REVERSE_DIRECTION	
					if (pvx || pvy) {
						if (ABS (pvx) > ABS (pvy)) {
							pvx = ADD_SIGN (-pvx, PLAYER_V_REBOUND);
						} else {
							pvy = ADD_SIGN (-pvy, PLAYER_V_REBOUND);
						}
					} else 
	#endif
					{
						pvx = ADD_SIGN (_en_mx, PLAYER_V_REBOUND);
						pvy = ADD_SIGN (_en_my, PLAYER_V_REBOUND);
					}
#endif					

#if defined (ENEMIES_CAN_DIE) && defined (ENEMS_SUFFER_WHEN_HITTING_PLAYER)
					enems_drain ();
#else
	#ifdef ENABLE_ESPECTROS
					if (rdt == 0x60) {
						_en_state = 3; _en_ct = 50;
					}
	#endif
#endif

#ifdef ENABLE_GENERATONIS
					if (rdt == 0x50) _en_mx = -_en_mx;
#endif
					pwashit = 1;
				}
			}

			// Enems <-> Stuff collision handling

			// Puas

#ifdef ENABLE_PUAS
			bi = PUAS_MAX; while (bi --) if (puas_y [bi] != 240) {
				if (collide (puas_x [bi], puas_y [bi], _en_x, _en_y)) {
					enems_drain ();
					puas_y [bi] = 240;
				}
			}
#endif

			// Bullets

#ifdef PLAYER_CAN_FIRE
			bi = BULLETS_MAX; while (bi --) if (b_ac [bi]) {
				if (collide (b_x [bi], b_y [bi], _en_x, _en_y)) {
					rda = 0; switch (rdt) {
	#ifdef ENABLE_TYPE7						
						case 0x70:
							if (_en_state) {
								rda = 1; enems_drain (); 
							}
							break;
	#endif
	#ifdef ENABLE_STEADY_SHOOTER
						case 0x80:
							rda = 1;
							_en_washit = TYPE7_MINION_HIT_FRAMES;
							break;
	#endif
	#ifdef ENABLE_WALKER							
						case 0xa0:
							rda = 1;
							_en_washit = WALKER_HIT_FRAMES;
							pwashit = 1;
							break;
	#endif							
						default:
							rda = 1;
							enems_drain ();							
							break;
					}
					
					if (rdt == 0x30) {
						_en_mx = -_en_mx; _en_my = -_en_my;
					}

					if (rda) {
						bullets_destroy ();
						break;
					}


				} 

	#if defined (ENABLE_TYPE7) && defined (TYPE7_WITH_GENERATOR)
				if (rdt == 0x70) if (collide (b_x [bi], b_y [bi], _en_x1, _en_y1)) {
					// Create explosion:
					rdx = _en_x1; rdy = _en_y1; 
									
					if (en_gen_life [gpit]) {
						en_gen_life [gpit] --;
						en_gen_washit [gpit] = TYPE7_GENERATOR_HIT_FRAMES;
						rde = 1;
					} else {
						enems_kill ();
						rde = 3;
					}
					
					expl_create ();

					bullets_destroy ();
					break;
				}
	#endif			

			}
#endif			

			// Fabolees

#ifdef ENABLE_FABOLEES
			if (!_en_ud) {
				bi = FABOLEES_MAX; while (bi --) if (fbl_ct [bi] && fbl_lock_on [bi] == 0xff) {
					if (
						1
	#ifdef ENABLE_MONOCOCO
						&& (rdt != 0x90 || en_state [gpit] == 2)
	#endif
	#if defined(ENABLE_GYROSAW) || defined(ENABLE_SAW)
						&& (rdt != 0xb0)
	#endif
					) {
						if (collide (fbl_x [bi], fbl_y [bi], _en_x, _en_y)) {
							_en_ud = 1;
							fbl_lock_on [bi] = gpit;
						}
					}
				}
			}
#endif
			// Done thing

		}

		// And when you are done, just undo the copy

		enems_restore_vals ();

		// That's it.
	}
}
