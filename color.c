#include "color.h"

// Couleur des cases
const static uint8_t COLOR_FG_ANSI_CODE[] = {  
	[BLACK]  = 30,
	[RED]    = 31,
	[GREEN]  = 32,
	[ORANGE] = 33,
	[BLUE]   = 34,
	[PINK]   = 35,
	[CYAN]   = 36,
	[GREY]   = 37
};
// Couleur des pieces
const static uint8_t COLOR_BG_ANSI_CODE[] = {
	[BLACK]  = 40,
	[RED]    = 41,
	[GREEN]  = 42,
	[ORANGE] = 43,
	[BLUE]   = 44,
	[PINK]   = 45,
	[CYAN]   = 46,
	[GREY]   = 47
};
// Les 2 fonctions prennent en parametre une couleur et renvoie le code ANSI correspondant pour definir la couleur du texte en avant-plan et arriere plan.

uint8_t Color_fgAnsiCode(Color color)
{
	return COLOR_FG_ANSI_CODE[color];
}


uint8_t Color_bgAnsiCode(Color color)
{
	return COLOR_BG_ANSI_CODE[color];
}