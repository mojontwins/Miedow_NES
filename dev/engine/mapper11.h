// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Communication pool utilites.
// Needs 
// #define COMM_POOL ((unsigned char*)0x0300)
// #define COMM_CHECKSUM COMM_POOK [0xf]

// Mapper 11 (Colordreams) is CCCCPPPP

/*
void m11_comm_pool_checksum_calculate (void) {
	rda = 0; for (gpit = 1; gpit < 15; gpit ++) rda += COMM_POOL [gpit];
}

// You can comment out these from "head" ROM if space is tight:

unsigned char m11_comm_pool_checksum_check (void) {
	m11_comm_pool_checksum_calculate ();	// Written to rda
	return (COMM_CHECKSUM == rda);
}

void m11_handle_reset (void) {
	if (m11_comm_pool_checksum_check ()) {
		COMM_CHECKSUM = 0xff; 				// Bad
		return;
	}
	COMM_GAME_SELECT = 0x00;
	COMM_REG = 0x00; // CCCCPPPP
	__asm__ ("jmp _change_rom");
}

*/

void m11_handle_reset (void) {
	rda = 0; for (gpit = 1; gpit < 15; gpit ++) rda += COMM_POOL [gpit];
	if (COMM_CHECKSUM == rda) {
		COMM_CHECKSUM = 0xff; return;
	}
	COMM_GAME_SELECT = 0x00; COMM_REG = 0x00; 
	__asm__ ("jmp _change_rom");	
}
