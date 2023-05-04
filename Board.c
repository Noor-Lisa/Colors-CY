#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colors.c"
#define SIZETAB 8

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    int width = 5;
    int height = 3;
    int x, y;
    // Déclaration et initialisation du tableau de couleurs
    int colors[SIZETAB][SIZETAB] = {0};

    // Remplissage du tableau de couleurs
    for (int i = 0; i < SIZETAB; i++) {
      for (int j = 0; j < SIZETAB; j++) {
          colors[i][j] = rand()%8;
        
        if(i==j){
          colors[i][j]=0; // Diagonale rouge
        }
        if(i+j==7){
          colors[i][j]=7; // Diagonale noir
        }
        if(i+j==3){
          colors[i][j]=4; // Diagonale magenta
        }  
        if(i+j==11){
          colors[i][j]=4; // Diagonale magenta
        } 
        if(i-j==4){
          colors[i][j]=2; // Diagonale jaune
        }
        if(j-i==4){
          colors[i][j]=2; // Diagonale jaune
        } 
      }
    }

    // Affichage du tableau de couleurs
    for (int i = 0; i < SIZETAB; i++) {
      for(int k=0; k<height; k++){ // Agrandir la taile du case
        for (int j = 0; j < SIZETAB; j++) {
            switch (colors[i][j]) {
                case 0: // Rouge
                    for (x = 0; x < width; x++) {
                      colors("101"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 1: // Vert
                    for (x = 0; x < width; x++) {
                      colors("102"); 
                      printf(" ");
                      colors("0");
                    } 
                    break;
                case 2: // Jaune
                    for (x = 0; x < width; x++) {
                      colors("103"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 3: // Bleu
                    for (x = 0; x < width; x++) {
                      colors("104"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 4: // Magenta
                    for (x = 0; x < width; x++) {
                      colors("105"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 5: // Cyan
                    for (x = 0; x < width; x++) {
                      colors("106"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 6: // Blanc
                    for (x = 0; x < width; x++) {
                      colors("107"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                case 7: // Noir
                    for (x = 0; x < width; x++) {
                      colors("100"); 
                      printf(" ");
                      colors("0");
                    }
                    break;
                default:
                    break;
            }
        }
        printf("\n");
      }
    }

    return 0;
}
