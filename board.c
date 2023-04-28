// arranging the board
#include <stdio.h>
#include <string.h>
#include stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time?h>

#define BOARD_SIZE 64
#define ROW_SIZE 8
#define COLUMN_SIZE 8
#define COLORS 8
#define PIECES_PER_PLAYER 8
#define MAX_MOVES_PER_TURN 2
#define PROMOTION_PIECE_DISTANCE 5 //PP : Promotion piece
#define PROMOTION_RANK 7 //lign to reach for piece promotion
#define MAX_ROUND 10
#define PROMOTED_PIECE_SYMBOL V


typedef enum{RED, ORANGE, GREEN, INDIGO, PURPLE, YELLOW, BLUE, GRAY}
Color;

typedef enum{NORMAL, PROMOTED}
PieceType;


typedef struct{
    Color color;
    PieceType type;
    bool is_promoted;
}
Piece;

typedef struct{
    Piece piece[PIECES_PER_PLAYER];
    char name[30];
    int score;
    bool winner;
}
Player;

typedef struct{
    int row;
    int column;
}
Square;

typedef struct{
    Square squares[BOARD_SIZE];
    int active_color;
    int move_count;
    Square *last_moves_piece;
}
Board;


void init_board(Board *board){
    Piece red = {RED, NORMAL};
    Piece orange = {ORANGE, NORMAL};
    Piece green = {GREEN, NORMAL};
    Piece indigo = {INDIGO, NORMAL};
    Piece purple = {PURPLE, NORMAL};
    Piece yellow = {YELLOW, NORMAL};
    Piece blue = {BLUE, NORMAL};
    Piece gray = {GRAY, NORMAL};
  
  
}
