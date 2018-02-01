// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Fabolees (integer). Recoded. The SMS version was overly, unncessarily complex

void fabolee_init (void) {
	gpit = FABOLEES_MAX; while (gpit --) {
		fbl_ct [gpit] = 0; 
	}
}

void fabolee_new (void) {
	// Creates new fabolee at px, py.
	gpit = FABOLEES_MAX; while (gpit --) {
		if (!fbl_ct [gpit]) {
			// Coordinates
			fbl_y [gpit] = pry; fbl_x [gpit] = prx - 4;

			// Indexes for the precalculated arrays
			fbl_idx_y [gpit] = 0; fbl_idx_my [gpit] = 1;
			fbl_idx_x [gpit] = 0;

			// Other attributes
			fbl_facing [gpit] = pfacing;
			fbl_ct [gpit] = 200; fbl_lock_on [gpit] = 0xff;
			
			sfx_play (SFX_FABOLEE, SC_PLAYER);
			break;
		}
	}
}

void fabolee_do (void) {
	rdct = FABOLEES_MAX; while (rdct --) {
		if (fbl_ct [rdct]) {
			gpit = fbl_lock_on [rdct];

			if (gpit == 0xff) {

				_fbl_x = fbl_x [rdct];
				_fbl_y = fbl_y [rdct];
				_fbl_idx_x = fbl_idx_x [rdct];
				_fbl_idx_y = fbl_idx_y [rdct];
				_fbl_idx_my = fbl_idx_my [rdct];

				// Horizontal

				pdx = fbl_facing [rdct] ? -fbl_incr_x [_fbl_idx_x] : fbl_incr_x [_fbl_idx_x];
				_fbl_x += pdx;

				if (_fbl_idx_x < FBL_INCR_MAX_X) _fbl_idx_x ++;

				// Vertical

				if (_fbl_idx_my) {
					pdy = -fbl_incr_y [_fbl_idx_y]; 
					if (_fbl_idx_y < FBL_INCR_MAX_Y) _fbl_idx_y ++;
				} else {
					pdy = fbl_incr_y [_fbl_idx_y]; 
					_fbl_idx_y --; if (!_fbl_idx_y) _fbl_idx_my = 1;
				}
				_fbl_y += pdy;
				
				if (_fbl_x > 240) {
					if (fbl_facing [rdct]) {
						_fbl_x = fbl_facing [rdct] = 0;
					} else {
						_fbl_x = 240; fbl_facing [rdct] = 1;
					}
				}

				if (_fbl_y > 240) {
					_fbl_y = 0;
					//_fbl_idx_y = (4 + (rand8 () & 7)) << 1;
					_fbl_idx_y = 31;
					_fbl_idx_my = 0;
				}
			} else {	
				_fbl_x = en_x [gpit]; _fbl_y = en_y [gpit];
				if (en_y [gpit] == 192) {
					fbl_lock_on [rdct] = 0xff;
					enems_drain ();
				}
			}	

			if (fbl_ct [rdct] > 50 || half_life) oam_index = oam_meta_spr (
				_fbl_x, _fbl_y + SPRITE_ADJUST,
				oam_index,
				spr_fabolee [(frame_counter + rdct) & 3]
			);

			// Collide
			if (gpit == 0xff) {

				if (_fbl_y > 16 && (!pj)) {
					if (prx + 9 >= _fbl_x && prx <= _fbl_x + 17) {
						//if (pry + 17 >= _fbl_y && pry + 12 <= _fbl_y) {
						if (pry + 17 >= _fbl_y && pry + 12 <= _fbl_y) {
							pgotten = 1; 
							pgtmy = pdy << FIX_BITS; // Just need the sign
							pgtmx = pdx << FIX_BITS;
							pry = _fbl_y - 16; py = pry << FIX_BITS;
							pvy = 0;
						}
					}
				}
			}

			fbl_ct [rdct] --;

			// Free?
			if (!fbl_ct [rdct] && gpit != 0xff) {
				en_ud [gpit] = 0;
				if (en_t [gpit] == 0x98) enems_drain ();
			}

			fbl_x [rdct] = _fbl_x;
			fbl_y [rdct] = _fbl_y;
			fbl_idx_x [rdct] = _fbl_idx_x;
			fbl_idx_y [rdct] = _fbl_idx_y;
			fbl_idx_my [rdct] = _fbl_idx_my;
		} 
	}
}
