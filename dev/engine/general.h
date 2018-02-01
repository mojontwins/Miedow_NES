// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// General stuff

void cm_two_points (void) {
	// Calculates at1 & at2 from cx1, cy1 & cx2, cy2
	if (cy1 > 12 || cy2 > 12) { at1 = at2 = 0; return; }
	caux = cy1 ? cy1 - 1 : 0;	
	at1 = scr_attr [cx1 | (caux << 4)];
	caux = cy2 ? cy2 - 1 : 0;
	at2 = scr_attr [cx2 | (caux << 4)];
} 

unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
//#ifdef ENABLE_FABOLEES
//	return (x1 + 8 >= x2 && x1 <= x2 + 8 && y1 + 8 >= y2 && y1 <= y2 + 8);
//#else
	return (x1 + 7 >= x2 && x1 <= x2 + 15 && y1 + 7 >= y2 && y1 <= y2 + 15);
//#endif
}

void pad_read (void) {
	// Thanks for this, Nicole & nesdev!
	// https://forums.nesdev.com/viewtopic.php?p=179315#p179315
	pad_this_frame = pad0;
	pad0 = pad_poll (0);			// Read pads here.
	pad_this_frame = (pad_this_frame ^ pad0) & pad0;
}

void pad_clean (void) {
	pad0 = pad_this_frame = 0;
}
