#ifndef __PIECE_H
#define __PIECE_H


#include <stdbool.h>
#include <stdint.h>

#include "color.h"


typedef struct Piece_s {
	uint8_t x, y;
	Color color;
	bool promoted;
} Piece;



#endif  //__PIECE_H