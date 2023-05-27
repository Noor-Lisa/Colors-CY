#include "game.h"

#include <stdio.h>

#include "board.h"
#include "constants.h"
#include "macros.h"

// Declarations des fonctions et des procedures
static void Game_initPlayer(Player *player, bool is_up);

static uint8_t Game_maxMoveForward(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov);
static uint8_t Game_promotedMaxMoveForward(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov);
static uint8_t Game_maxMoveSide(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t side_mov);
static uint8_t Game_maxMoveDiagonal(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov, int8_t side_mov);

static void Game_drawGrid(const Game *game);
static void Game_drawColumnNames(uint8_t next_piece_x, bool first_piece_picked);
static void Game_drawLineName(uint8_t next_piece_y, uint8_t line,
	bool first_piece_picked);
static void Game_drawCellTopOrBottom(const Game *game, uint8_t x, uint8_t y);
static void Game_drawCell(const Game *game, uint8_t x, uint8_t y);
static void Game_drawInfo(const Game *game);

static bool Game_isCellOccupied(const Game *game, uint8_t x, uint8_t y);

// macro qui retourne une valeur booleenne true ou false
#define HAS_SAME_SIGN(a, b) ((a) * (b) >= 0)

//Initialisation la structure Game en lui attribuant les valeurs initiales
void Game_init(Game *game, uint8_t round_amount)
{
	for (int p = 0; p < PLAYER_AMOUNT; p++)
		Game_initPlayer(&game->players[p], p == 0);

	game->player_turn = 0;
	game->piece_turn = 0;

	game->curr_round = 0;
	game->round_amount = round_amount;

	game->round_start_time = time(NULL);
	game->curr_round_first_piece_picked = false;
}


static void Game_initPlayer(Player *player, bool is_up)
{
	player->score = 0;
	uint8_t piece_y = (is_up)? 0 : BOARD_H - 1;	//Si is_up est true, les pieces sont plcees a la ligne 0 (Joueur 1). Sinon, elles sont placees a la ligne 7 (Joueur 2)

	for (int p = 0; p < PIECE_AMOUNT; p++) {
		Piece *piece = &player->pieces[p];
		piece->x = p; // p augmente a chaque iteration
		piece->y = piece_y; // ici = 0 
		piece->color = board[piece_y][p]; // Tableau du plateu avec toutes les couleurs
		piece->promoted = false;
	}
}

//Plateau initial
bool Game_canStartWith(const Game *game, uint8_t x, uint8_t y)
{
	const Player *player = &game->players[game->player_turn]; // recupere le pointeur du joueur actuel
	return Player_constPieceAt(player, x, y) != NULL; 
} // la fonction renvoie true si Player_constPieceAt renvoie un pointeur non nul

// Démarre le jeu et choisi le premier pion par le joueur
void Game_startWith(Game *game, uint8_t x, uint8_t y)
{
	Player *player = &game->players[game->player_turn]; // recupere le pointeur du joueur actuel

	for (uint8_t p = 0; p < PIECE_AMOUNT; p++) {
		if (player->pieces[p].x == x && player->pieces[p].y == y)
			game->piece_turn = p; // Vérifie si les coordonnées du pion actuel correspondent aux coordonnées de x et y.
	}
	game->curr_round_first_piece_picked = true; // indique que le premier pion est du tour en cours a ete selectionnee
}

//Le tableau MIN_MOVES_POSSIBLE contient des coordonnées de deplacement minimum possibles pour les pieces du jeu.
const int8_t MIN_MOVES_POSSIBLE[][2] = {
	{ 1, 0 }, { -1, 0 }, //deplacement d'une case vers la droite / gauche
	{ 1, 1 }, { -1, 1 }, // deplacement diagonal d'une case vers la droite / gauche et vers le haut
	{ 0, 1 }, // deplacement d'une case vers le haut
	{ 0, 2 } // Que pour les pions promus
};

//Determine si le joueur actuel peut effectuer un mouvement avec la piece actuelle dans le jeu
bool Game_canMove(const Game *game)
{
	int8_t forward_mov = (game->player_turn == 0)? 1 : -1;	

	const Piece *piece =
		&game->players[game->player_turn].pieces[game->piece_turn];
	uint8_t x = piece->x;
	uint8_t y = piece->y;

	bool can_move = false;

	// Ne verifie pas le dernier deplacement si la piece n'est pas promu
	uint8_t possible_moves_amount = SIZE_OF_ARRAY(MIN_MOVES_POSSIBLE);
	if (!piece->promoted)
		possible_moves_amount--;

	// Essaye de trouver au moins une case libre
	for (uint8_t m = 0; m < possible_moves_amount; m++) {
		uint8_t new_x = x + MIN_MOVES_POSSIBLE[m][0];
		uint8_t new_y = y + MIN_MOVES_POSSIBLE[m][1] * forward_mov;

		if (new_x < 8 && new_y < 8)
			can_move = can_move ||
				!Game_isCellOccupied(game, new_x, new_y);
	}

	return can_move;
}


bool Game_isMoveValid(const Game *game, uint8_t x, uint8_t y)
{
	int8_t forward_mov = (game->player_turn == PLAYER1)? 1 : -1;	//player1 avance vers le bas -> 1; player 2 avance vers le haut -> -1
		const Piece *piece =
		&game->players[game->player_turn].pieces[game->piece_turn];

	int8_t x_mov = x - piece->x;
	int8_t y_mov = y - piece->y;
	int8_t side_mov = (x_mov > 0)? 1 : -1; //Si vrai deplace a droite, sinon a gauche

	// Ne peut pas reculer
	if (!HAS_SAME_SIGN(forward_mov, y_mov))
		return false;
	// Ne bouge pas
	if (x_mov == 0 && y_mov == 0)
		return false;
	// Le deplacement n'est pas en diagonale, ni vers l'avant, ni de cote
	if (x_mov != 0 && y_mov != 0 && ABS(x_mov) != ABS(y_mov))
		return false;
	// Le pion promu ne peut pas deplacer plus de 5 pas
	if (MAX(x_mov, y_mov) > 5 && piece->promoted)
		return false;

	uint8_t max_movement;

	// Assure qu'aucun pion n'est en route
	if (y_mov != 0 && x_mov == 0) {
		if (piece->promoted)
			max_movement = Game_promotedMaxMoveForward(
				game, piece->x, piece->y, forward_mov
			);
		else
			max_movement = Game_maxMoveForward(
				game, piece->x, piece->y, forward_mov
			);
	} else if (x_mov != 0 && y_mov == 0) {
		max_movement = Game_maxMoveSide(game, piece->x, piece->y,
			side_mov);
	} else {
		max_movement = Game_maxMoveDiagonal(game, piece->x, piece->y,
			forward_mov, side_mov);
	}
	
	return MAX(ABS(x_mov), ABS(y_mov)) <= max_movement;		// ABS : x a droite est +ve et a gauche est -ve, MAX : pour savoir le maximum pas pris par le pion
}

//Avance maximale dans l'axe y
static uint8_t Game_maxMoveForward(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov)
{
	uint8_t counter = 0;
	uint8_t y = start_y + forward_mov;

	while (y <= BOARD_H && !Game_isCellOccupied(game, start_x, y)) {
		y += forward_mov;
		counter++;
	}

	return counter;
}

//Avance maximale dans l'axe y pour les pions promus
static uint8_t Game_promotedMaxMoveForward(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov)
{
	uint8_t counter = 0;
	uint8_t y = start_y + forward_mov;

	while (y <= BOARD_H && !Game_isCellOccupied(game, start_x, y)) {
		y += forward_mov;
		counter++;
	}

	const Player *other_player =
		&game->players[(game->player_turn + 1) % PLAYER_AMOUNT];
	const Piece *blocking_piece =
		Player_constPieceAt(other_player, start_x, y);

	// Vérifie si le joueur bloqueur est l'un des autres et s'il peut être pousse
	if ((uint8_t) (y + forward_mov) < BOARD_H &&
		blocking_piece != NULL && !blocking_piece->promoted &&
		!Game_isCellOccupied(game, start_x, y + forward_mov))
  // la piece d'obstacle est a l'oppose du joueur
  {
		counter++;
	}

	return counter;
}


//Avance maximale dans l'axe x
static uint8_t Game_maxMoveSide(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t side_mov)
{
	uint8_t counter = 0;
	uint8_t x = start_x + side_mov;

	while (x <= BOARD_W && !Game_isCellOccupied(game, x, start_y)) {
		x += side_mov;
		counter++;
	}

	return counter;
}


//Deplacement diagonal maximum
static uint8_t Game_maxMoveDiagonal(const Game *game, uint8_t start_x,
	uint8_t start_y, int8_t forward_mov, int8_t side_mov)
{
	uint8_t counter = 0;
	uint8_t x = start_x + side_mov;
	uint8_t y = start_y + forward_mov;

	while (x <= BOARD_W && y <= BOARD_H && !Game_isCellOccupied(game, x, y)) {
		x += side_mov;
		y += forward_mov;
		counter++;
	}

	return counter;
}



void Game_playMove(Game *game, uint8_t x, uint8_t y)
{
	int8_t forward_mov = (game->player_turn == PLAYER1)? 1 : -1;
	Piece *piece_to_move =
		&game->players[game->player_turn].pieces[game->piece_turn];
	
	// Deplace le pion s'il gêne
	Piece *in_the_way = Player_pieceAt(
		&game->players[(game->player_turn + 1) % PLAYER_AMOUNT],
		x, y
	);
	if (in_the_way != NULL) 		//s'il n'y a pas de pion devant, on peut avancer
		in_the_way->y += forward_mov;
	
	piece_to_move->x = x;
	piece_to_move->y = y;
}


// Le joueur a gagne la manche
bool Game_wasRoundJustWon(const Game *game)
{
	uint8_t last_piece_y =
		game->players[game->player_turn].pieces[game->piece_turn].y;
	
	return (game->player_turn == PLAYER1 && last_piece_y == LAST_LINE) ||
		(game->player_turn == PLAYER2 && last_piece_y == FIRST_LINE);
}


// On attribue le score au joueur
void Game_updateScoreAndPromote(Game *game)
{
	Player *player = &game->players[game->player_turn];
	Piece *piece = &player->pieces[game->piece_turn];
	player->score += (piece->promoted)? 2 : 1;
  //Si la manche a ete gagne avec la piece promue, on attribue 2 points au joueur, sinon on attribue 1 point

	piece->promoted = true;
}

//La prochaine manche commence avec le joueur qui a remporte la manche precedente
uint8_t Game_getRoundWinner(const Game *game)
{
	return game->player_turn; 
}


// Si les scores des deux joueurs different et que le nombre de manches en cours est egal a round_amount, alors il s'agit de la manche finale
bool Game_wasFinalRound(const Game *game)
{
	return game->curr_round + 1 >= game->round_amount &&
		game->players[PLAYER1].score != game->players[PLAYER2].score;
}


void Game_goToNextRound(Game *game)
{
	// Reinitialiser la position des pieces
	for (uint8_t p = 0; p < PLAYER_AMOUNT; p++) {
		Player *player = &game->players[p];
		uint8_t y_pos = (p == PLAYER1)? FIRST_LINE : LAST_LINE;

		for (uint8_t i = 0; i < PIECE_AMOUNT; i++) {
			player->pieces[i].x = i;
			player->pieces[i].y = y_pos;
		}
	}

	game->piece_turn = 0;

	game->curr_round++;
	game->round_start_time = time(NULL);
	game->curr_round_first_piece_picked = false;
}

// Fin de jeu, retourne les joueurs avec leurs points 
uint8_t Game_getOverallWinner(const Game *game)
{
	return (game->players[PLAYER1].score > game->players[PLAYER2].score)?
		PLAYER1 : PLAYER2;
}


// Choisi le joueur et la couleur de la piece pour le prochain deplacement
void Game_goToNextTurn(Game *game)
{
	Piece *piece = &game->players[game->player_turn].pieces[game->piece_turn];
	Color next_color = board[piece->y][piece->x];

	game->player_turn = (game->player_turn + 1) % PLAYER_AMOUNT;
	Player *new_player = &game->players[game->player_turn];

	for (uint8_t p = 0; p < PIECE_AMOUNT; p++)
		if (new_player->pieces[p].color == next_color)
			game->piece_turn = p;
}

//Affiche les grilles du plateau et l'informations de jeu
void Game_draw(const Game *game)
{
	Game_drawGrid(game);
	Game_drawInfo(game);
}


static void Game_drawGrid(const Game *game)
{
	const Piece *next_piece =
		&game->players[game->player_turn].pieces[game->piece_turn];
	
	Game_drawColumnNames(next_piece->x, game->curr_round_first_piece_picked);

	for (int y = 0; y < BOARD_H; y++) {
		printf("  ");
		for (int x = 0; x < BOARD_W; x++)
			Game_drawCellTopOrBottom(game, x, y);
		printf("\n");

		Game_drawLineName(next_piece->y, y, game->curr_round_first_piece_picked);
		for (int x = 0; x < BOARD_W; x++)
			Game_drawCell(game, x, y);
		printf("\n");

		printf("  ");
		for (int x = 0; x < BOARD_W; x++)
			Game_drawCellTopOrBottom(game, x, y);
		printf("\n");
	}
}


static void Game_drawColumnNames(uint8_t next_piece_x, bool first_piece_picked)
{
	// Affiche les coordonnees des colonnes
	printf(" ");
	for (int i = 0; i < BOARD_W; i++) {
		char char_to_draw = 'A' + i;
		bool is_selected_column =
			next_piece_x == i && first_piece_picked;
// Selectionne la colonne de la piece choisie
		printf(
			"  \033[31m%c\033[m%c\033[31m%c\033[m",
			(is_selected_column)? 'v' : ' ',
			char_to_draw,
			(is_selected_column)? 'v' : ' '
		);
	}
	printf("\n");
}

// Affiche les coordonnees des lignes er selectionne la ligne de la piece choisie
static void Game_drawLineName(uint8_t next_piece_y, uint8_t line,
	bool first_piece_picked)
{
	printf(
		"%d%s",
		line + 1,
		(next_piece_y == line && first_piece_picked)?
			"\033[31m>\033[m" : " "
	);
}


// Affiche les pieces 
static void Game_drawCellTopOrBottom(const Game *game, uint8_t x, uint8_t y)
{
	printf("\033[%dm     \033[m", Color_bgAnsiCode(board[y][x]));
}

// Affiche les cases et les pieces
static void Game_drawCell(const Game *game, uint8_t x, uint8_t y)	
{
	const Piece *p0_piece = Player_constPieceAt(&game->players[0], x, y);
	const Piece *p1_piece = Player_constPieceAt(&game->players[1], x, y);

  //Symbols et couleur de player1 pieces normales et piece promue
	if (p0_piece != NULL)
		printf(
			"\033[%dm \033[m\033[%dm%s\033[m\033[%dm \033[m",
			Color_bgAnsiCode(board[y][x]),
			Color_bgAnsiCode(p0_piece->color),
			(p0_piece->promoted)? "($)" : "(*)",
			Color_bgAnsiCode(board[y][x])		// Plyaer1 : Pions normaux "(*)", pion promu : "($)"
		);
  
  // Symbols et couleur player2 pieces normales et piece promue
	else if (p1_piece != NULL)
		printf(
			"\033[%dm \033[m\033[%dm%s\033[m\033[%dm \033[m",
			Color_bgAnsiCode(board[y][x]),
			Color_bgAnsiCode(p1_piece->color),
			(p1_piece->promoted)? "[$]" : "[:]",
			Color_bgAnsiCode(board[y][x])		// Player2 : Pieces normales "[:]", piece promue : "[$]"
		);
	else
		printf("\033[%dm     \033[m", Color_bgAnsiCode(board[y][x]));
}

// Affiche les points des joueurs et le numero de la manche actuelle
static void Game_drawInfo(const Game *game)
{
	printf("  P1      Round      P2\n");
	printf(
		" %3d     %3d/%-3d     %3d\n",
		game->players[0].score,  //score de player1(P1)
		game->curr_round + 1,		// +1, car la manche est initialise en 0
		game->round_amount,    // Nombre total de manche
		game->players[1].score  // score de player2(P2)
	);
}

// verifie si la destination case est occupee
static bool Game_isCellOccupied(const Game *game, uint8_t x, uint8_t y)
{
	for (uint8_t p = 0; p < PLAYER_AMOUNT; p++)
		if (Player_constPieceAt(&game->players[p], x, y) != NULL)		// la condition verifie -> destination case vide
			return true;
	return false;
}



// Partie sauvegarde de jeu

void Game_saveToFile(const Game *game, const char *file_path)
{
	FILE *file = fopen(file_path, "w");
	if (file == NULL) {
		printf("Failed to open \"%s\"\n", file_path);
		return;
	}

	fprintf(
		file, "%hhd %hhd %hhd %hhd %hhd\n",
		game->player_turn, game->piece_turn,
		game->curr_round, game->round_amount,
		(game->curr_round_first_piece_picked)? 1 : 0
	);

	for (uint8_t pl = 0; pl < PLAYER_AMOUNT; pl++) {
		const Player *player = &game->players[pl];
		fprintf(file, "%hhd %hhd:", pl, player->score);

		for (uint8_t pi = 0; pi < PIECE_AMOUNT; pi++) {
			const Piece *piece = &player->pieces[pi];
			fprintf(
				file,
				"{%hhd %hhd %hhd %hhd %hhd}",
				pi,
				piece->x, piece->y,
				(uint8_t) piece->color,
				(piece->promoted)? 1 : 0
			);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}


bool Game_restoreFromFile(Game *game, const char *file_path)
{
	FILE *file = fopen(file_path, "r");
	if (file == NULL) {
		printf("Failed to open \"%s\"\n", file_path);
		return false;
	}
	
	uint8_t has_started_int;
	uint8_t values_scanned_amount = fscanf(
		file, "%hhd %hhd %hhd %hhd %hhd\n",
		&game->player_turn, &game->piece_turn,
		&game->curr_round, &game->round_amount,
		&has_started_int
	);

	if (values_scanned_amount != 5) {
		printf("Save file corrupt\n");
		return false;
	}

	game->curr_round_first_piece_picked = has_started_int == 1;

	for (uint8_t pl = 0; pl < PLAYER_AMOUNT; pl++) {
		uint8_t player_id;
		values_scanned_amount = fscanf(file, "%hhd", &player_id);
		if (values_scanned_amount != 1) {
			printf("Save file corrupt\n");
			return false;
		}

		Player *player = &game->players[player_id];
		values_scanned_amount = fscanf(file, " %hhd:", &player->score);
		if (values_scanned_amount != 1) {
			printf("Save file corrupt\n");
			return false;
		}

		for (uint8_t pi = 0; pi < PIECE_AMOUNT; pi++) {
			uint8_t piece_id;
			values_scanned_amount = fscanf(file, "{%hhd", &piece_id);
			if (values_scanned_amount != 1) {
				printf("Save file corrupt\n");
				return false;
			}

			Piece *piece = &player->pieces[piece_id];
			uint8_t promoted_int;
			values_scanned_amount = fscanf(
				file,
				" %hhd %hhd %hhd %hhd}",
				&piece->x, &piece->y,
				(uint8_t *) &piece->color,
				&promoted_int
			);
			if (values_scanned_amount != 4) {
				printf("Save file corrupt\n");
				return false;
			}

			piece->promoted = promoted_int == 1;
		}
		fscanf(file, "\n");
	}

	fclose(file);
	return true;
}