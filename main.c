#define clrsrc() printf("\033[H\033[2]")
#define colors(param) printf("\033[%sm", param)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "colors.c"
#define SIZETAB 8

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    int width = 7;
    int height = 3;
    int x, y;
    // Déclaration et initialisation du tableau de couleurs
    int colors[SIZETAB][SIZETAB] = {0};

    // Remplissage aléatoire du tableau de couleurs
    for (int i = 0; i < SIZETAB; i++) {
        for (int j = 0; j < SIZETAB; j++) {
            colors[i][j] = rand() % 8;
            
            
            //1st line
            
            if(i==0){
            if(j==i){
                colors[i][j] = 0;
            }if(j==i+1){
                colors[i][j] = 1;
            }
            if(j==i+2){
                colors[i][j] = 2;
            }
            if(j==i+3){
                colors[i][j] = 3;
            }
            if(j==i+4){
                colors[i][j] = 4;
            }
            if(j==i+5){
                colors[i][j] = 5;
            }
            if(j==i+6){
                colors[i][j] = 6;
            }
            if(j==i+7){
                colors[i][j] = 7;
            }
            }
            
            
            //Last line
            if(i==7){
            if(i==j){
                colors[i][j] = 0;
            }    
            if(i-1==j){
                colors[i][j] = 1;
            }
            if(i-2==j){
                colors[i][j] = 2;
            }
            if(i-3==j){
                colors[i][j] = 3;
            }
            if(i-4==j){
                colors[i][j] = 4;
            }
            if(i-5==j){
                colors[i][j] = 5;
            }
            if(i-6==j){
                colors[i][j] = 6;
            }
            if(i-7==j){
                colors[i][j] = 7;
            }
            }
            
            //Red diagonal
            if(i==j){
                colors[i][j]=0;
            }
            
            //Dark grey diagonal
            if(i+j==7){
                colors[i][j]=7;
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
                case 6: // Blanchttps://www.onlinegdb.com/onlinhttps://www.onlinegdb.com/online_c_compiler#tab-stdine_c_compiler#tab-stdin
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
