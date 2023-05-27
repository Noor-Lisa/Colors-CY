#ifndef __BOARD_H
#define __BOARD_H


#include "color.h"
#include "constants.h"

//BOARD_H : la hauteur du plateau
//BOARD_W : la largeur du plateau

// Le plateau 
const static Color board[BOARD_H][BOARD_W] = {
	{ RED, GREEN, BLUE, PINK, ORANGE, CYAN, GREY, BLACK },
	{ CYAN, RED, PINK, GREY, GREEN, ORANGE, BLACK, BLUE },
	{ GREY, PINK, RED, CYAN, BLUE, BLACK, ORANGE, GREEN },
	{ PINK, BLUE, GREEN, RED, BLACK, GREY, CYAN, ORANGE },
	{ ORANGE, CYAN, GREY, BLACK, RED, GREEN, BLUE, PINK },
	{ GREEN, ORANGE, BLACK, BLUE, CYAN, RED, PINK, GREY },
	{ BLUE, BLACK, ORANGE, GREEN, GREY, PINK, RED, CYAN },
	{ BLACK, GREY, CYAN, ORANGE, PINK, BLUE, GREEN, RED }
};


#endif  // __BOARD_H