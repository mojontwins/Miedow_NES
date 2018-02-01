// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Breakable walls

void breakable_init (void) {
	gpit = BREAKABLE_MAX; while (gpit --) {
		brk_ac [gpit] = 0;
		brk_slots [gpit] = gpit;
	}
	brk_slot = BREAKABLE_MAX;
}

void breakable_break (void) {
	// Increment count at 1cc· ····
	scr_attr [rdi] += 0x20;

	// Encode this value carefully when modifying the "define"
	if ((scr_attr [rdi] & 0x60) == BREAKABLE_HITS) {
		set_map_tile (rdi & 15, rdi >> 4, 0);
		rdb = BREAKABLE_FRAMES_DESTROY;		
	} else rdb = BREAKABLE_FRAMES_HIT;

	process_breakable = 1;

	// Get slot
	if (brk_slot){
		brk_slot --; rda = brk_slots [brk_slot];
		brk_ac [rda] = rdb;
		brk_x [rda] = (rdi & 0xf) << 4;
		brk_y [rda] = (rdi & 0xf0) + 16;
	}
}

void breakable_do (void) {
	if (0 == process_breakable) return;

	process_breakable = 0;
	gpit = BREAKABLE_MAX; while (gpit --) {
		if (brk_ac [gpit]) {
			oam_index = oam_meta_spr (
				brk_x [gpit] + jitter_big [rda], 
				brk_y [gpit] + jitter_big [15 - rda] + SPRITE_ADJUST, 
				oam_index, 
				SPRITE_EXPLOSION
			);
			if (brk_ac [gpit] --) {
				process_breakable = 1;
			} else {
				brk_ac [gpit] = 0;
				brk_slots [brk_slot] = gpit; brk_slot ++;	
			}
		}
	}
}
