// MT MK2 NES v0.9 - New D'Veel'Ng!
// Copyleft 2017 by The Mojon Twins

//#define STANDALONE	// Comment when assembling to main ROM.
//#define DEBUG

// Shiru's

#include "neslib-CNROM.h"

// Some needed stuff...

#include "definitions.h"

// Main const includes

#include "assets/palettes.h"
#include "assets/precalcs.h"
#include "assets/chr-rom-maps.h"
#include "assets/enems0.h"
#include "assets/enems1.h"
#include "assets/enems2.h"
#include "assets/enems3.h"
#include "assets/enems4.h"
#include "assets/enemsi.h"
#include "assets/tiledata.h"
#include "assets/metasprites.h"
#include "assets/behs.h"
#include "assets/levelset.h"
//#include "assets/texts.h"
//#include "assets/script_texts.h"
//#include "assets/talk_scripts.h"
//#include "assets/dialogue.h"
//#include "assets/title_rle.h"
#include "assets/title_bg_rle.h"
#ifdef COMPO
#include "assets/intro_rle_compo.h"
#else
#include "assets/intro_rle.h"
#endif
#include "assets/hud_rle.h"
#include "assets/cuts0_rle.h"
//#include "assets/ending_rle.h"

// Some variables

#pragma bss-name (push,"ZEROPAGE")
#pragma data-name(push,"ZEROPAGE")

#include "ram/zp.h"

#pragma bss-name (push,"BSS")
#pragma data-name(push,"BSS")

#include "ram/bss.h"

// Engine functions

#include "someprotos.h"
#include "engine/printer.h"
#include "engine/general.h"
#include "engine/screens.h"
#ifdef ENABLE_EXPLOSIONS
#include "engine/explosions.h"
#endif
#ifdef ENABLE_SPRINGS
#include "engine/spring.h"
#endif
#ifdef ENABLE_PROPELLERS
#include "engine/propellers.h"
#endif
#ifdef ENABLE_ESTRUJATORS
#include "engine/estrujators.h"
#endif
#ifdef ENABLE_CATARACTS
#include "engine/cataracts.h"
#endif
#ifdef SCRIPTING_ON
#ifdef ENABLE_EXTERN_CODE
#include "engine/extern.h"
#endif
#include "engine/mscnes.h"
#endif
#ifdef SHOOTING_DRAINS
#include "engine/flower.h"
#endif
#ifdef ENABLE_SHINES
#include "engine/shines.h"
#endif
#ifdef BREAKABLE_WALLS
#include "engine/breakable.h"
#endif
#ifdef PLAYER_CAN_FIRE
#include "engine/bullets.h"
#endif
#ifndef DISABLE_HOTSPOTS
#include "engine/hotspots.h"
#endif
#if defined (HOTSPOT_TYPE_KEY) || defined (ENABLE_TOUCHPLATES) || defined (ENABLE_LIGHTABLE)
#include "engine/bolts.h"
#endif
#ifdef ENABLE_FUMETTOS
#include "engine/fumettos.h"
#endif
#ifdef ENABLE_PUAS
#include "engine/puas.h"
#endif
#include "engine/hud.h"
#ifdef ENABLE_CONTAINERS
#include "engine/containers.h"
#endif
#ifdef ENABLE_FABOLEES
#include "engine/fabolee_int.h"
#endif
#include "engine/player.h"
#ifdef ENABLE_COCOS
#include "engine/simplecoco.h"
#endif
#include "engine/enems.h"
//#include "engine/talkbox.h"
#include "engine/game.h"

// Holy Holy - hold on to anyone

void do_level (void) {
	scroll (0, SCROLL_Y);
	hud_draw ();
	game_init ();
	game_loop ();
}

void main (void) {
	bank_bg (0);
	bank_spr (1);
			
	ticks = ppu_system () ? 60 : 50;
	halfticks = ticks >> 1;

	oam_size (0);
	pal_bright (0);

	// Run the game here.
	while (1) {
		pal_spr (palss0);
		
		game_title ();
		game_intro ();

		pcontinues = 3; plife = 5; levelseq = 0;
		
		while (1) {

			psleeping = 1; psprid = 33;	level = 0; 	do_level ();
			if (levelseq < 10) game_level ();
			psprid = 14; level = 1 + levelseq; 		do_level ();
			
			if (pkilled) {
				game_over ();
				if (signal_continue) {
					pcontinues --;
					plife = 5;
				} else break;
			} else {
				if (levelseq < 10) {
					game_cuts ();
					levelseq ++; 
					plife ++;
				} else {
					game_ending ();
					break;
				}
			} 
		}
	}
}
