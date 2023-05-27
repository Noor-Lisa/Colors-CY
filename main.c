#include <stdio.h>

#include "game.h"
#include "input.h"


Game game;


void GameLoop()
{
	Game_draw(&game);
	bool is_piece_blocked;
	uint8_t last_piece_that_moved = 0;

	while (true) {
		if (!game.curr_round_first_piece_picked) {
			// Demande de choisir une piece
			printf(
				"Pick a starting piece to play (player %d)\n",
				game.player_turn + 1
			);
			PlayInfo start_info = AskToPlay();

			// Quitter ou enregistrer, si l utilisateur demande
			if (start_info.is_quitting) {
				break;
			} else if (start_info.is_saving) {
				printf("Saving game\n");
				Game_saveToFile(&game, SAVE_FILE);
				continue;
			}

			// Verifie si la piece souhaitee a utiliser est valide
			if (Game_canStartWith(&game, start_info.x, start_info.y)) {
				// Commende le jeu
				Game_startWith(&game, start_info.x, start_info.y);
				Game_draw(&game);
			} else {
				printf("This is not one of your pieces\n");
				continue;
			}
		}

		// Si la piece est bloquee, passe au tour suivant
		is_piece_blocked = !Game_canMove(&game);
		if (is_piece_blocked) {
			Game_goToNextTurn(&game);

			// Verifie si la piece est a nouveau bloquee, et si c est la derniere
      // le joueur qui s est deplace gagne
      if (!Game_canMove(&game)) {
				printf("player %d cant move %d\n", game.player_turn + 1, game.piece_turn);
				// Definissez la piece et le joueur qui ont permis de gagner
				Game_goToNextTurn(&game);
				game.player_turn = last_piece_that_moved;
        
      // Mettre a jour le score du joueur gagnant
				Game_updateScoreAndPromote(&game);
				printf(
					"Player %d won this round in %lds !\n",
					Game_getRoundWinner(&game) + 1,
					time(NULL) - game.round_start_time
				);

				// Si tous les tours sont termines
				if (Game_wasFinalRound(&game)) {
					printf(
						"The overall winner is player %d !\n",
						Game_getOverallWinner(&game) + 1
					);
					Game_draw(&game);
					break;
				}

				Game_goToNextRound(&game);
				Game_draw(&game);
				continue;
			}
			Game_draw(&game);
		}
		
		// Demande ce qu il faut faire
		PlayInfo play_info = AskToPlay();

		// Demande de quitter ou enregistrer
		if (play_info.is_quitting) {
			break;
		} else if (play_info.is_saving) {
			printf("Saving game\n");
			Game_saveToFile(&game, SAVE_FILE);
			continue;
		}
		
		// Prend les mouvements invalides
		if (!Game_isMoveValid(&game, play_info.x, play_info.y)) {
			printf("The move is not valid\n");
			continue;
		}
		
		Game_playMove(&game, play_info.x, play_info.y);
		last_piece_that_moved = game.piece_turn;

		if (Game_wasRoundJustWon(&game)) {
			Game_updateScoreAndPromote(&game);
			printf(
				"Player %d won this round in %lds !\n",
				Game_getRoundWinner(&game) + 1,
				time(NULL) - game.round_start_time
			);

			// Si tous les tours sont termines
			if (Game_wasFinalRound(&game)) {
				printf(
					"The overall winner is player %d !\n",
					Game_getOverallWinner(&game) + 1
				);
				Game_draw(&game);
				break;
			}

			Game_goToNextRound(&game);
		} else {
			Game_goToNextTurn(&game);
		}

		Game_draw(&game);
	}
}


void RoundAmountMenu()
{
	printf("How many rounds do you want to play ?\n");
	Game_init(&game, AskRoundAmount());
	GameLoop();
}


int main()
{
	bool menu_should_close = false;

	while (!menu_should_close) {
		printf("[Main Menu] What do you want to do ?\n");
		MenuChoice choice = MenuAsk();

		if (choice == ChoiceNewGame) {
			RoundAmountMenu();
		} else if (choice == ChoiceRestoreGame) {
			bool success = Game_restoreFromFile(&game, SAVE_FILE);
			if (success)
				GameLoop();
		} else if (choice == ChoiceQuit) {
			menu_should_close = true;
		}
	}
	
	return 0;
}