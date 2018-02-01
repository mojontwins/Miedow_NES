// MT MK2 NES v0.7a
// Copyleft32016 by The Mojon Twins

// Tile behaviours

// Walkable are xSHK0xxx.
// Obstacle are 00001TPL, with 00001010 = lock.

const unsigned char behs0 [] = {
	0, 0, 8, 8, 8, 8, 0,16, 8, 0,16, 8, 8, 8,10,15,
	0, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 8, 8,32,32, 8
};

const unsigned char behs1 [] = {
	0, 8, 8, 8,12, 0, 0,12,12, 0, 0,10,10,10,10,15,
	0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 0, 0, 0,15,16
};

// Touchplate definitions. For "floor" tiles, a number
// define which bolt it operates. For "push box" tiles,
// a number define which touchplate it activates; 0 activates anything.
const unsigned char tp_defs1 [] = {
//                                  /--/--/-- Those push boxes activate touchplates in tiles #27, #28, and #29, resp.
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,27,28,29,99, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,30,30,30, 0, 0
};
//                                   \__ Those touchplates activate bolt in tile #30

const unsigned char behs2 [] = {
	0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,12, 0, 0, 0, 0,
	0, 0, 0, 0,12,12, 0, 0, 8, 8, 8, 8, 8, 8, 0, 0
};

const unsigned char behs3 [] = {
	0, 0, 0, 0, 0, 8, 8, 8,64,32, 8, 8, 8,12,10,15,
	8, 8, 8, 8, 0, 0, 8, 8, 8,12, 8, 0,32,32, 0,15
};

const unsigned char tp_defs3 [] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,30, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,31, 0 
};

const unsigned char behs4 [] = {
	0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9,10,15,
	4, 8, 8,16, 8, 8,16, 0, 0, 0, 0, 0,32,32, 0,15
};

const unsigned char tp_defs4 [] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,31,30, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,31, 0
};

const unsigned char behs5 [] = {
	0, 8, 8, 8, 8, 8, 8, 8, 8, 8,10,10,10, 8, 8, 8,
	0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 0,64
};
