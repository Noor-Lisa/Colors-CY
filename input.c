#include "input.h"

#include <stdio.h>
#include <string.h>

#include "macros.h"


static void PutPromptInputIn(char *buffer, uint8_t buff_size);
static void ClearStdIn();


PlayInfo AskToPlay()
{
	char buffer[25];		// On met l entree utlisateur

	PlayInfo play_info;
	play_info.x = -1;
	play_info.y = -1;

	while (true) {
		PutPromptInputIn(buffer, SIZE_OF_ARRAY(buffer));

		if (strncmp(buffer, "play", 4) == 0) {
			// Obtenir les coordonnees de jeu
			int processed_arg_amount = sscanf(				//sscanf pour lire les valeurs a partir d une chaine de caracteres
				&buffer[5],
				"%c%d",										// %c%d car le premier est type char et le der,ier type int
				&play_info.x, (int *) &play_info.y
			);
			
			if (processed_arg_amount == 2) { // savoir si l utilisateur met 2 coordonnees ou pas
				play_info.x -= 'A';
				play_info.y -= 1;
			} else {
				play_info.x = -1;
				play_info.y = -1;
			}

			// Verifier si les coordonnees sont valides
			if (play_info.x < 8 && play_info.y < 8) {
				play_info.is_quitting = false;
				play_info.is_saving = false;
				break;
			} else {
				// Affiche un message d aide
				printf(
					"Expected \"play xy\", with x "
					"between A and H, and y between 1 and 8"
					"\n"
				);
			}
		} else if (strcmp(buffer, "save") == 0) {
			play_info.is_quitting = false;
			play_info.is_saving = true;
			break;
		} else if (strcmp(buffer, "quit") == 0) {
			play_info.is_quitting = true;
			play_info.is_saving = false;
			break;
		} else {
			// Affiche un message d aide
			printf("Expected \"play xy\", \"save\" or \"quit\"\n");
		}
	}

	return play_info;
}


MenuChoice MenuAsk()
{
	char buffer[25];

	while (true) {
		PutPromptInputIn(buffer, SIZE_OF_ARRAY(buffer));

		if (strcmp(buffer, "new game") == 0) {
			return ChoiceNewGame;
		} else if (strcmp(buffer, "restore game") == 0) {
			return ChoiceRestoreGame;
		} else if (strcmp(buffer, "quit") == 0) {
			return ChoiceQuit;
		} else {
			// Affiche un message d aide
			printf("Expected \"new game\", \"restore game\", or "
				"\"quit\"\n");
		}
	}
}


uint8_t AskRoundAmount()
{
	char buffer[25];

	while (true) {
		PutPromptInputIn(buffer, SIZE_OF_ARRAY(buffer));

		uint8_t round_amount;
		if (sscanf(buffer, "%hhd", &round_amount) == 1) {	//%hhd pour charartere signe sur 8-bits
			return round_amount;
		} else {
			printf("Expected a number\n");
		}
	}
}


static void PutPromptInputIn(char *buffer, uint8_t buff_size)
{
	// Empêche le débordement de buffer en donnant une limite d entree à scanf
	char format_buffer[16];
	sprintf(format_buffer, "%%%d[^\n]", buff_size - 1);

	// Ecrire le pmompt et scanf
	printf("> ");
	scanf(format_buffer, buffer);

	// Effacez le std in des caractères \n et EOF de fin
	// Source :  https://stackoverflow.com/questions/64368589/how-to-avoid-buffer-overflow-using-scanf
	ClearStdIn();
}


static void ClearStdIn()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}