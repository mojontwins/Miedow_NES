
#ifdef ENABLE_HOLES	
	if (!pholed) 
#endif		
	{
		if (pad0 & PAD_A) {
			if (pjb == 0) {
				pjb = 1;
				if (pj == 0) {
					pj = 1; pctj = 0;
					sfx_play (SFX_JUMP, SC_PLAYER);					
				}
			}
		} else { 
			pjb = 0;
		}
	}
