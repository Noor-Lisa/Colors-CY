#ifndef __COLOR_H
#define __COLOR_H


#include <stdint.h>


typedef enum Color_e {
	BLACK,
	RED,
	GREEN,
	ORANGE,
	BLUE,
	PINK,
	CYAN,
	GREY
} Color;

// Declaration des fonctions

uint8_t Color_fgAnsiCode(Color color);
uint8_t Color_bgAnsiCode(Color color);


#endif  // __COLOR_H