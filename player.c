#include "player.h"

#include <stdlib.h>


Piece *Player_pieceAt(Player *player, uint8_t x, uint8_t y)
{
	Piece *found_piece = NULL;  // Pion selectionne initiliase NULL

	for (uint8_t p = 0; p < PIECE_AMOUNT; p++) {
		Piece *piece = &player->pieces[p];    // Les pieces des deuxc joueurs

		if (piece->x == x && piece->y == y)
			found_piece = piece;    //Condition est verifie -> piece est choisie
	}

	return found_piece;
}

// Recherche un pion specifique d'un joueur en fonction de ses coordonnees
const Piece *Player_constPieceAt(const Player *player, uint8_t x, uint8_t y)
{
	const Piece *found_piece = NULL; 

	for (uint8_t p = 0; p < PIECE_AMOUNT; p++) {
		const Piece *piece = &player->pieces[p];

		if (piece->x == x && piece->y == y)
			found_piece = piece;
	}

	return found_piece; // retourne un pointeur vers la piece trouve ou NULL si aucune piece ne correspond aux coordonnees specifiees
}