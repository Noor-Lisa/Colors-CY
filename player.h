#ifndef __PLAYER_H
#define __PLAYER_H


#include <stdint.h>

#include "constants.h"
#include "piece.h"


typedef struct Player_s {
	Piece pieces[PIECE_AMOUNT];
	uint8_t score;
} Player;


Piece *Player_pieceAt(Player *player, uint8_t x, uint8_t y);
const Piece *Player_constPieceAt(const Player *player, uint8_t x, uint8_t y);


#endif  // __PLAYER_H