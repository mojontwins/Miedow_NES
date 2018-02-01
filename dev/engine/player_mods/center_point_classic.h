// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Player movement.
// Center point detections (Classic)

#ifdef PLAYER_ENABLE_CENTER_DETECTIONS
	cx1 = cx2 = (prx + 4) >> 4;
	cy1 = cy2 = (pry + 8) >> 4;
	cm_two_points ();

#ifdef EVIL_TILE_CENTER
	evil_tile_hit = IS_EVIL (at1);
#endif

#ifdef ENABLE_WATER
	rda = pwater;
	pwater = (IS_WATER (at1));
	if (pwater != rda) sfx_play (SFX_FLUSH, SC_PLAYER);
	if (!pwater && rda) pvy = -PLAYER_VY_OUT_OF_WATER;
#endif

#ifdef ENABLE_TILE_GET
	if (IS_TILE_GET (at1)) {

		set_map_tile (cx1, cy1 - 1, 0);
		sfx_play (SFX_RING, SC_LEVEL);

#ifdef TILE_GET_COUNT_ON_FLAG
		flags [TILE_GET_COUNT_ON_FLAG] ++;
#else 
		tile_get_ctr ++;
		if (tile_get_ctr == 100) {
			tile_get_ctr = 1; 
			plife ++;
			sfx_play (SFX_START, SC_PLAYER);
		}
#endif	

#ifdef PERSISTENT_TILE_GET
		gpint = tile_got_offset + (cy1 - 1);
		rda = tile_got [gpint];
		tile_got [gpint] = rda | bitmask [cx1 >> 1];
#endif
	}
#endif

#endif

	