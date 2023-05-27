#ifndef __GAME_H
#define __GAME_H


#include <stdint.h>
#include <time.h>

#include "constants.h"
#include "player.h"


typedef struct Game_s {// Represente l'etat de jeu
	Player players[PLAYER_AMOUNT];//  tableau de joueurs de taille PLAYER_AMOUNT (defini dans constants.h ) /stockage de info sur joueurs
	uint8_t player_turn, piece_turn;//  le numero de la piece actuellement selectionnee pour le mouvement

	uint8_t curr_round, round_amount;//le numero du tour actuel
	time_t round_start_time;
	bool curr_round_first_piece_picked;	//1ere peice selectionee
} Game;

// Declarations des fonctions, procedures
void Game_init(Game *game, uint8_t round_amount);

bool Game_canStartWith(const Game *game, uint8_t x, uint8_t y);
void Game_startWith(Game *game, uint8_t x, uint8_t y);

bool Game_canMove(const Game *game);// Verifie si un mouvement est possible dans le jeu en cours
bool Game_isMoveValid(const Game *game, uint8_t x, uint8_t y);// Verifie si un mouvement aux coordonnees specifiees (x et y) est valide dans le jeu en cours
void Game_playMove(Game *game, uint8_t x, uint8_t y);//Effectue un mouvement aux coordonnees specifiees (x et y) dans le jeu en cours.

bool Game_wasRoundJustWon(const Game *game);//Commence le jeu avec les coordonnees specifiees (x et y)
void Game_updateScoreAndPromote(Game *game);//Verifie si le tour vient d'etre remporte
uint8_t Game_getRoundWinner(const Game *game);//Recupere le numéro du joueur qui a remporte le tour.
bool Game_wasFinalRound(const Game *game);//Verifie si le tour en cours est le dernier tour
void Game_goToNextRound(Game *game);// Passe au tour suivant dans le jeu

uint8_t Game_getOverallWinner(const Game *game);//: Recupere le numero du joueur qui a remporte le jeu dans son ensemble.

void Game_goToNextTurn(Game *game);//Passe au tour suivant dans le jeu en incrementant le joueur et la piece actuelle.

void Game_draw(const Game *game);//Dessine l'etat actuel du jeu

void Game_saveToFile(const Game *game, const char *file_path);
bool Game_restoreFromFile(Game *game, const char *file_path);


#endif  // __GAME_H