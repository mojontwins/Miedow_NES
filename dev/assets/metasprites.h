// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Metaspriteset

#include "assets/spritedata.h"
#include "assets/spritedata2.h"

// Customize as fit

const unsigned char * const spr_enems0 [] = {
	// Linear 
	ssena_00_a, ssena_01_a, ssena_00_b, ssena_01_b,	
	ssena_02_a, ssena_03_a, ssena_02_b, ssena_03_b,	
	ssena_04_a, ssena_05_a, ssena_04_b, ssena_05_b,	
	ssena_06_a, ssena_07_a, ssena_06_b, ssena_07_b,	

	// Fanty 16
	ssena_08_a, ssena_09_a, ssena_08_b, ssena_09_b,

	// Generator 20
	ssenb_00, ssenb_01, 0, 0,

	// Saw 24
	ssenb_02, ssenb_03, 0, 0
};

const unsigned char * const spr_player0 [] = {
	sspl_00, sspl_01, sspl_02, sspl_03, sspl_04, sspl_05, sspl_06, 
	sspl_07, sspl_08, sspl_09, sspl_0A, sspl_0B, sspl_0C, sspl_0D, 
	sspl_0E, sspl_0F, sspl_10, sspl_11,	sspl_12, sspl_13, sspl_14, 
	sspl_15, sspl_16, sspl_17, sspl_18, sspl_19, sspl_1A, sspl_1B,
	sspl_1C, sspl_1D,

	// holed: 30 onwards
	ssplh_02, ssplh_01, ssplh_00,

	// Sleeping: 33
	sssleep_03, sssleep_04, sssleep_05
};

// Items are: [nothing] [nothing] key refill skull
// The wasted space saves a bit of code
const unsigned char * const spr_items [] = {
	0, 0, ssitb_00, ssitb_01, ssitb_02, ssitc,
	// Prisoners start @ 6
	ssita_00, ssita_01, ssita_02, ssita_03
};


const unsigned char ssplempty [] = {
	-4, -8, 0, 0, 4, -8, 0, 0, 
	-4, 0, 0, 0, 4, 0, 0, 0, 
	-4, 8, 0, 0, 4, 8, 0, 0, 
	0x80
};

const unsigned char * const spr_expl [] = {
	ssexpl_03, ssexpl_02, ssexpl_01, ssexpl_00
};
