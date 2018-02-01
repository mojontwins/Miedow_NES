// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// If you end up not using those in your game, just whipe them for 20 extra bytes (WOW!)
const unsigned char bitmasks [] = { 0xfc, 0xf3, 0xcf, 0x3f };
#if defined (SHOOTING_DRAINS) || defined (ENEMS_UPSIDE_DOWN)
	const unsigned char jitter [] = { 0,1,1,0,0,1,0,1,1,0,0,0,1,0,1,1 };
#endif

#ifdef PLAYER_CAN_FIRE
	// RIGHT LEFT DOWN UP
	const signed char en_dx [] = {1, -1, 0, 0};
	const signed char en_dy [] = {0, 0, 1, -1};
	const signed char boffsx [] = {12, -8, 0, 0};
	const signed char boffsy [] = {3, 3, 12, -4};
#endif

#ifdef ENABLE_COCO_STRAIGHT
	// LEFT UP RIGHT DOWN
	const signed char coco_vx_precalc [] = { -COCO_V, 0, COCO_V, 0 };
	const signed char coco_vy_precalc [] = { 0, -COCO_V, 0, COCO_V };
#endif

#ifdef ENABLE_MONOCOCO
	const unsigned char monococo_state_times [] = {
		MONOCOCO_BASE_TIME_HIDDEN, MONOCOCO_BASE_TIME_APPEARING, MONOCOCO_BASE_TIME_ONBOARD, MONOCOCO_BASE_TIME_APPEARING
	};
#endif 
	
/*
const unsigned char box_buff [] = {
	17,18,18,18,18,18,18,18,18,18,18,19, 99, 99, 99, 99,
	20,21,21,21,21,21,21,21,21,21,21,22, 99, 99, 99, 99,
	20,21,21,21,21,21,21,21,21,21,21,22, 99, 99, 99, 99,
	23,24,24,24,24,24,24,24,24,24,24,25
};
*/

const signed char jitter_big [] = {
	-1, -1, -1, -4, 4, -3, 0, -4, -2, 3, -3, 2, 1, -1, 0, -2
};

#if defined (ENABLE_PRECALC_FANTY) || defined (ENABLE_PRECALC_HOMING_FANTY) || defined (ENABLE_PRECALC_TIMED_FANTY)
	#define FANTY_INCS_MAX 16
	const signed char fanty_incs [] = {
		// Slower fanty
		0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1
		// Faster fanty
		// 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
		// Much faster fanty
		// 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2
	};
#endif

#ifdef ENABLE_PRECALC_HOMING_FANTY
	#define FANTY_RETREAT_INCS_MAX 4
	const signed char fanty_retreat_incs [] = {
		1, 0, 0, 0
	};
#endif

#ifdef ENABLE_PRECALC_PEZON
	#define PEZON_INCS_MAX 48
	#define PEZON_INCS_FIRST_FALL 26
	const signed char pezon_incs [] = {
		-6, -6, -5, -5, -5, -4, -4, -4,
		-4, -4, -3, -3, -3, -2, -2, -2, 
		-2, -2, -1, -1, -1, 0, 0, 0, 
		0, 0, 1, 1, 1, 2, 2, 2, 
		2, 2, 3, 3, 3, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4
	};
#endif

#ifdef ENABLE_FABOLEES
	#define FBL_INCR_MAX_X 59
	const unsigned char fbl_incr_x [] = {
		0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 
		0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x01, 0x02, 
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 
		0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00 //, 0x00, 0x00, 0x00, 0x00
	};

	#define FBL_INCR_MAX_Y 53
	const unsigned char fbl_incr_y [] = {
		0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 
		0x01, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 
		0x01, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x02, 0x01, 0x02, 0x01, 0x01, 
		0x02, 0x02, 0x01, 0x02, 0x01, 0x02 //, 0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x02
	};
#endif

unsigned char bitmask [] = {
	1, 2, 4, 8, 16, 32, 64, 128
};

// New genital jump. Several flavours. Uncoment which you favour.
#if defined (ENGINE_TYPE_NEW_GENITAL) && defined (PLAYER_JUMPS)
	/*
	#define PLAYER_PRECALC_JUMP_STEPS 15
	const unsigned char player_precalc_jump [] = {
		4, 7, 10, 12, 14, 15, 16, 16, 16, 15, 14, 12, 10, 7, 4
	};
	#define PLAYER_PRECALC_JUMP_SAFE_ZONE0 4
	#define PLAYER_PRECALC_JUMP_SAFE_ZONE1 10
	*/

	#define PLAYER_PRECALC_JUMP_STEPS 24
	const unsigned char player_precalc_jump [] = {
		3, 5, 7, 9, 11, 12, 13, 14, 15, 16, 16, 16, 16, 16, 15, 14, 13, 12, 11, 9, 7, 5, 3, 0
	};
	#define PLAYER_PRECALC_JUMP_SAFE_ZONE0 5
	#define PLAYER_PRECALC_JUMP_SAFE_ZONE1 17
#endif

// CUSTOM {
unsigned char rand_pregen [] = {
	201, 4,   185, 32,  152, 191, 241, 6,
	95,  130, 33,  90,  171, 188, 14,  145,
	158, 213, 217, 146, 255, 7,   215, 117,
	28,  228, 3,   204, 20,  83,  121, 89,
	106, 233, 141, 69,  129, 97,  240, 151,
	132, 136, 41,  235, 15,  87,  128, 109,
	239, 103, 99,  96,  249, 123, 56,  26,
	230, 206, 19,  205, 251, 189, 115, 252,
	68,  200, 178, 148, 92,  149, 18,  16,
	27,  182, 42,  197, 37,  108, 170, 8,
	102, 114, 147, 79,  138, 51,  154, 187,
	73,  112, 135, 52,  184, 50,  45,  160,
	61,  13,  100, 88,  162, 224, 167, 66,
	238, 53,  227, 142, 166, 180, 174, 93,
	202, 1,   12,  75,  190, 254, 131, 35,
	59,  164, 219, 67,  122, 2,   253, 55,
	22,  63,  165, 246, 86,  113, 143, 48,
	80,  192, 163, 78,  225, 34,  194, 139,
	232, 234, 5,   221, 248, 214, 175, 74,
	47,  181, 40,  44,  244, 17,  127, 76,
	168, 161, 155, 144, 62,  212, 186, 105,
	94,  243, 242, 229, 179, 211, 137, 218,
	71,  82,  236, 126, 111, 110, 31,  177,
	196, 46,  199, 10,  208, 49,  21,  124,
	36,  107, 193, 156, 85,  209, 11,  43,
	29,  54,  222, 84,  65,  169, 104, 119,
	220, 64,  207, 150, 247, 9,   58,  183,
	231, 116, 118, 203, 70,  23,  250, 176,
	25,  0,   159, 173, 101, 81,  77,  153,
	216, 72,  198, 57,  39,  245, 223, 237,
	134, 120, 38,  98,  133, 140, 30,  125,
	157, 210, 91,  226, 172, 24,  60,  195
};
// } END_OF_CUSTOM
