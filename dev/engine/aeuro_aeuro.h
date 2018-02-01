// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Simple ring for Sonic Mal games
// Remember to launch the ring BEFORE sonic changes direction when hit

// Code is ugly, just does its work. 
#define RING_A 			2
#define RING_MAX_V 		32

void ring_init (void) {
	if (tile_get_ctr) {
		ring_on = 1;
		ring_x = px;
		ring_y = py;
		ring_vy = -96;
		//ring_vx = -(pvx << 1);//ADD_SIGN ((pvx), 96);
		if (pvx < 0) {
			if (pvx > -RING_MAX_V) ring_vx = -pvx; else ring_vx = RING_MAX_V;
		} else if (pvx > 0) {
			if (pvx < RING_MAX_V) ring_vx = -pvx; else ring_vx = -RING_MAX_V;
		} else ring_vx = 0;
		ring_timer = 180;
		ring_signal = 1;
		tile_get_ctr = 0;
	}
}

void ring_do (void) {
	if (ring_on) {
		if (ring_timer) {
			ring_timer --;

			ring_vy += PLAYER_G;
			ring_y += ring_vy;

			rdy = ring_y >> FIX_BITS;
			rdx = 8 + (ring_x >> FIX_BITS);
			if (ring_vy > 0) {
				cy1 = rdy - 1; // rdy + 15 - 16;
				at1 = scr_attr [(cy1 & 0xf0)|(rdx >> 4)];
				if (((rdy -1 ) & 15) < 6 && (IS_NOT_AIR (at1))) {
					//rdy = 16 + (((cy1 >> 4) - 1) << 4);
					rdy = cy1 & 0xf0;
					ring_vy = - ((ring_vy >> 1) + (ring_vy >> 2)) ;
				}
			} else if (ring_vy < 0) {
				cy1 = rdy - 16;
				at1 = scr_attr [(cy1 & 0xf0)|(rdx >> 4)];
				if (IS_NOT_AIR (at1)) {
					//rdy = 16 + (((cy1 >> 4) + 1) << 4);
					rdy = 32 + (cy1 & 0xf0);
					ring_vy = 0;
				}
			}
			ring_y = rdy << FIX_BITS;

			if (ring_vx > 0) {
				ring_vx -= RING_A; if (ring_vx < 0) ring_vx = 0;
			} else if (ring_vx < 0) {
				ring_vx += RING_A; if (ring_vx > 0) ring_vx = 0;
			}

			ring_x += ring_vx;
			if (ring_x < 0) { ring_x = 0; ring_vx = -ring_vx; }
			if (ring_x > 3840) { ring_x = 3840; ring_vx = -ring_vx; }

			rdy = 15 + (ring_y >> FIX_BITS) - 16;
			rdx = ring_x >> FIX_BITS;

			if (ring_vx > 0) {
				cx1 = (rdx + 12);
				if (scr_attr [(rdy & 0xf0)|(cx1>>4)] & 8) {
					rdx = (((cx1 >> 4) - 1) << 4) + 8;
					ring_x = rdx << FIX_BITS;
					ring_vx = -ring_vx;
				}
			} else if (ring_vx < 0) {
				cx1 = (rdx + 4);
				if (scr_attr [(rdy & 0xf0)|(cx1>>4)] & 8) {
					rdx = (((cx1 >> 4) - 1) << 4) - 4;
					ring_x = rdx << FIX_BITS;
					ring_vx = -ring_vx;
				}
			}

			// Calc

			rdx = ring_x >> FIX_BITS; rdy = (ring_y >> FIX_BITS);

			// Collide

			if (CL (prx, pry, rdx, rdy) && /*!pflickering*/ ring_timer < 120) {
				ring_timer = 0;
				sfx_play (SFX_RING, SC_LEVEL);
				tile_get_ctr = 1;
			}

			// Draw

			if (ring_timer > 50 || half_life) oam_index = oam_meta_spr (
				rdx, rdy + SPRITE_ADJUST,
				oam_index,
				spr_ring [(frame_counter >> 1) & 3]
			);
		} else ring_on = 0;
	}
}

