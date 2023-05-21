#ifndef BOARD
#define BOARD

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZETAB 8
#define clrscr() printf("\033[H\033[2J")
#define colors(param) printf("\033[%sm", param)

typedef struct {
    int beige;
    int green;
    int cyan;
    int lightMagenta;
    int yellow;
    int blue;
    int darkMagenta;
    int black;
} Colors;

typedef enum{NORMAL, PROMOTED}
PieceType;

typedef struct Square {
    Colors color;
    int square[SIZETAB][SIZETAB];
    PieceType type;
} Square;

typedef struct Board {
    int size;
    Square** squares;
} Board;

typedef struct Piece {
    int row;
    int column;
    int isSelected;
} Piece;

typedef struct Move {
    Piece coordinates;
    int newColor;
} Move;

typedef struct Player {
    char name[50];
    int score;
} Player;

#endif
