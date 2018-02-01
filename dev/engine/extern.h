// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

// Functions controlled from the script

const unsigned char eat1 [] = "NOTICE: USE%THAT SHRINE%WITH HEARTS%TO REGAIN%YOUR MOJO!";
const unsigned char eat2 [] = "NOTICE:%STICK TO THE%HEART . . .";
const unsigned char eat3 [] = "I HAVE ALREADY%ACTIVATED THIS%TRAP . . .";
const unsigned char eat4 [] = "THIS ACTIVATES%SOMETHING, BUT%I NEED A LEVER%TO FIT IN THIS%HOLE . . .";
const unsigned char eat5 [] = "NOTICE:TO OPEN%THAT DOOR, YOU%MUST ACTIVATE%THE 2 BUTTONS%AT ONCE!";
const unsigned char eat6 [] = "MAINTENANCE:%THERE ARE%3 ENGINE%PIECES TO BE%REPLACED.";
const unsigned char eat7 [] = "MAINTENANCE:%ENGINE PIECE%REPLACEMENT.%HANDLE WITH  %CARE";
const unsigned char eat8 [] = "THIS WAY TO%RETURN . . .";
const unsigned char eat9 [] = "I PRESS THE%BUTTON BUT%NOTHING%HAPPENS . . .";
const unsigned char eat10 [] = "THE ENGINE%STARTS BUT%DOESN'T WORK%QUITE RIGHT.";
const unsigned char eat11 [] = "MAYBE THERE'S%A MISSING%OR MISPLACED%PIECE?";
const unsigned char eat12 [] = "MAINTENANCE:%INDICATIVE%PLATES NEED%REPAIRS!";
const unsigned char eat13 [] = "THE MACHINE%IS WORKING!%";
const unsigned char eat14 [] = "INSTRUCTIONS%USE [A] TO% JUMP.%USE [B] TO...% HUMMM...";
const unsigned char eat15 [] = "YOU CAN JUMP%ON BADDIES.%NOBODY WILL%GET HURT.";
const unsigned char eat16 [] = "GREEN SLIME%IS DANGEROUS%SO YOU MUST%AVOID IT...";
const unsigned char eat17 [] = "YOU CAN CARRY%ONE OBJECT.%PRESS [B] TO%GET THAT LEVER";
const unsigned char eat18 [] = "USE THE LEVER%IN THAT NOTCH.%PRESS [B] TO%OPEN THE GATE";
const unsigned char eat19 [] = "MUTANT BATS%WILL DIE IF%THEY TOUCH THE%SLIME TOO.%USE THAT.";
const unsigned char eat20 [] = "BATS ARE SO%FAST. BETTER%NEUTRALIZE%THEM FIRST.";
const unsigned char eat21 [] = "NEVER, NEVER%WALK OVER A%TILE WITH A%SKULL.";
const unsigned char eat22 [] = "NOW, THE REAL%ADVENTURE IS%ABOUT TO%START!";
const unsigned char eat23 [] = "MAINTENANCE:%I'VE FIXED THE%FANS. TRY%THEM, IT'S%QUITE FUN!";
const unsigned char eat24 [] = "MAINTENANCE:%THE COMPUTER%TO OPEN THIS%GATE IS TO%THE LEFT...";
const unsigned char eat25 [] = "MAINTENANCE:%USE 1 FLOPPY%TO UNLOCK THIS%COMPUTER.";
const unsigned char eat26 [] = "COMPUTER:%ACCESS GRANTED%THE GATE TO%NEXT LEVEL IS%NOW OPEN . . .";
const unsigned char eat27 [] = "A HYDRAULIC%ENGINE SOUNDS%NEARBY . . .";
const unsigned char eat28 [] = "MIND THE SAW%IN THE UPPER%FLOOR!";
const unsigned char eat29 [] = "THIS SWITCHES%BOTH GATES.";
const unsigned char eat30 [] = "THIS SWITCHES%ONE GATE.";
const unsigned char eat31 [] = "CAN'T BE READ";

const unsigned char * const extern_action_texts [] = {
	   0,   eat1,  eat2,  eat3,  eat4,  eat5,  eat6,  eat7, 
	 eat8,  eat9, eat10, eat11, eat12, eat13, eat14, eat15,
	eat16, eat17, eat18, eat19, eat20, eat21, eat22, eat23,
	eat24, eat25, eat26, eat27, eat28, eat29, eat30, eat31
};

const unsigned char stbf [] = {
	45, 46, 46, 46, 46, 46, 46, 47,
	48,  0,  0,  0,  0,  0,  0, 49,
	48,  0,  0,  0,  0,  0,  0, 49,
	48,  0,  0,  0,  0,  0,  0, 49,
	48,  0,  0,  0,  0,  0,  0, 49,
	50, 51, 51, 51, 51, 51, 51, 52
};

void extern_frame (void) {
	// Draws and covers the text frame depending on rdd
	rdx = 8; rdy = 10; gp_gen = (unsigned char *) stbf;
	gpkt = 52; // 4 + (3 << 4)
	gpit = 48; while (gpit --) {
		if (0 == (rdx & 3)) ul = update_list;
		rdt = rdd ? scr_buff [gpkt ++] : *gp_gen ++;
		update_list_tile ();
		rdx += 2;
		if (0 == (rdx & 3)) close_update_cycle ();
		if (rdx == 24) { rdx = 8; rdy += 2; gpkt += 8; }
	}
}

void do_extern_action (void) {
	oam_hide_rest (20);

	// In this game, 
	// EXTERN n (n = 1..127) will show a simple text box.

	// I like to reserve EXTERN 0 for other stuff.

	/*
	switch (n) {
		default:
	*/
			// Draw frame
			rdd = 0; extern_frame ();

			gp_gen = (unsigned char *) extern_action_texts [sc_n];
			gp_addr = NAMETABLE_A + 361; // 9 + 11*32
			update_list [3] = NT_UPD_EOF;
			while (rda = *gp_gen ++) {
				if (rda == '%') {
					gp_addr = ((gp_addr + 64) & 0xffe0) + 9;
				} else {
					update_list [0] = MSB (gp_addr);
					update_list [1] = LSB (gp_addr ++);
					update_list [2] = rda - 32;					
				}
				ppu_wait_nmi ();
			}

			// Wait
			while (!(pad_poll (0) & PAD_B));

			// Restore screen
			rdd = 1; extern_frame ();
	/*
			break;
	}
	*/
}
