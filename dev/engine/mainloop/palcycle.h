if ((frame_counter & 7) == 0) {
	gpit = pal_cycle [0]; 
	pal_cycle [0] = pal_cycle [1]; 
	pal_cycle [1] = pal_cycle [2]; 
	pal_cycle [2] = gpit; 
	pal_col (13, pal_cycle [0]);
	pal_col (14, pal_cycle [1]);
	pal_col (15, pal_cycle [2]);
}
