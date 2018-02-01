d// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Estrujators!

void estrujators_add (void) {
#ifdef ESTRUJATORS_CREATE_FROM_MAP
	est_x [est_idx] = rdx >> 1;
	est_y [est_idx] = (rdy - TOP_ADJUST) >> 1;
	est_max_ct [est_idx] = ticks + ((rdt - ESTRUJATORS_TILE) << 6);
#else
	est_x [est_idx] = ESTRUJATORS_X;
	est_y [est_idx] = ESTRUJATORS_Y;
	est_max_ct [est_idx] = (ESTRUJATORS_DELAY << 5);
#endif
	est_ct [est_idx] = est_max_ct [est_idx] - est_ini_delay;
	est_state [est_idx ++] = 0;
	est_ini_delay += 8;
}

void estrujators_do (void) {
	est_n_acts = 1;
	gpit = est_idx; while (gpit --) {
	
		_est_ct = est_ct [gpit];
		_est_state = est_state [gpit];
		_est_x = est_x [gpit];
		_est_y = est_y [gpit];

		switch (_est_state) {
			case 0:
				// Idling, top
			case 3:				
				// Idling, down
				if (_est_ct) _est_ct --; else _est_state ++;	
				break;
			case 2:
				// Just make the tip a obstacle
				scr_attr [((_est_y + ESTRUJATORS_HEIGHT - 1) << 4) | _est_x] = 8;
				_est_state = 3;
				break;
			case 1: 
				// Descending
				if (est_n_acts
#ifdef ESTRUJATORS_SLOW
					&& (gpit & 1) == half_life
#endif
				) {
					set_map_tile (_est_x, _est_y + _est_ct, ESTRUJATORS_TILE + 2);
					if (_est_ct) set_map_tile (_est_x, _est_y + _est_ct - 1, ESTRUJATORS_TILE + 1);
					_est_ct ++; if (_est_ct == ESTRUJATORS_HEIGHT) {
						_est_ct = ESTRUJATORS_DOWN_IDLE_TIME;
						_est_state = 2;
						sfx_play (SFX_ESTRUJATOR, SC_ROOM);
					}
					est_n_acts = 0;
				}
				break;
			case 4:
				// Ascending
				if (est_n_acts
#ifdef ESTRUJATORS_SLOW
					&& (gpit & 1) == half_life
#endif
				) {
					if (_est_ct < ESTRUJATORS_HEIGHT-1) set_map_tile (_est_x, _est_y + (ESTRUJATORS_HEIGHT-1) -_est_ct, ESTRUJATORS_TILE + 2);
					if (_est_ct) set_map_tile (_est_x, _est_y + ESTRUJATORS_HEIGHT - _est_ct, ESTRUJATORS_TILE_DELETER);
					_est_ct ++; if (_est_ct == ESTRUJATORS_HEIGHT) {
						_est_ct = est_max_ct [gpit];
						_est_state = 0;
						set_map_tile (_est_x, _est_y, ESTRUJATORS_TILE);
					}
					est_n_acts = 0;
				}
				break;
		}

		est_ct [gpit] = _est_ct;
		est_state [gpit] = _est_state;
		est_x [gpit] = _est_x;
		est_y [gpit] = _est_y;
	}
}
