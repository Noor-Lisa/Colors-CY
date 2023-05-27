#ifndef __INPUT_H
#define __INPUT_H


#include <stdbool.h>
#include <stdint.h>


typedef struct PlayInfo_s {
	bool is_quitting;
	bool is_saving;
	uint8_t x, y;
} PlayInfo;

typedef enum MenuChoice_e {
	ChoiceNewGame, ChoiceRestoreGame, ChoiceQuit
} MenuChoice;

// Declarations des fonctions
PlayInfo AskToPlay();
MenuChoice MenuAsk();
uint8_t AskRoundAmount();


#endif  // __INPUT_H