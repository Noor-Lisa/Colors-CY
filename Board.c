#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colors.h"
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
         if(i+j==3||i+j==11){//rose
            colors[i][j]=4;
          }
         if(j-i==4||i-j==4){//jaune
           colors[i][j]=2;
          } 
          if(i==j){//rouge 
           colors[i][j]=0; 
          }
          if(i+j==7){ //noir 
          colors[i][j]=7;
              }
          
          if(i-j==2&&i%2!=0){//bleu
            colors[i][j]=3;
              }
          if(j-i==2&&i%2==0){
            colors[i][j]=3;
             }
          if(j-i==2&&i%2!=0){//blanc
            colors[i][j]=6;
              }
          if(i-j==2&&i%2==0){
            colors[i][j]=6;
             }
          if(i==6&&j==0||i==1&&j==7){
            colors[i][j]=3;
              }
          if(i==0&&j==6||i==7&&j==1){
            colors[i][j]=6;
             }
         if(i+j==5&&i%2==0){//cyan vert 
            colors[i][j]=5;
              }
          if(i+j==9&&i%2!=0){
            colors[i][j]=5;
             }
          if(i==6&&j==7){
            colors[i][j]=5;
              }
          if(i==1&&j==0){
            colors[i][j]=5;
             }
         if(i+j==5&&i%2!=0){ //vert 
           colors[i][j]=1;
            }
          if(i+j==9&&i%2==0){
            colors[i][j]=1;
            }
          if(i==7&&j==6){
            colors[i][j]=1;
              }
          if(i==0&&j==1){
            colors[i][j]=1;
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
                      if(i==0 && k==1 && x==1){
                        colors("101;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("101;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("101;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("91;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("91;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("91;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("101"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 1: // Vert
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("102;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("102;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("102;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("92;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("92;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("92;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("102"); 
                        printf(" ");
                        colors("0");
                      } 
                    } 
                    break;
                case 2: // Jaune
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("103;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("103;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("103;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("93;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("93;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("93;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("103"); 
                        printf(" ");
                        colors("0");
                      } 
                    } 
                    break;
                case 3: // Bleu
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("104;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("104;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("104;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("94;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("94;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("94;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("104"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 4: // Magenta
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("105;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("105;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("105;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("95;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("95;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("95;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("105"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 5: // Cyan
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("106;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("106;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("106;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("96;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("96;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("96;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("106"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 6: // Magenta foncé
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("35;107");
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("35;107");
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("35;107"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("35;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("35;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("35;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("45"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 7: // Noir
                    for (x = 0; x < width; x++) {
                      if(i==0 && k==1 && x==1){
                        colors("100;7"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==2){
                        colors("100;7"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==0 && k==1 && x==3){
                        colors("100;7"); 
                        printf("]");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==1){
                        colors("90;100"); 
                        printf("[");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==2){
                        colors("90;100"); 
                        printf("*");
                        colors("0");
                      }
                      else if(i==7 && k==1 && x==3){
                        colors("90;100"); 
                        printf("]");
                        colors("0");
                      }
                      else{
                        colors("90"); 
                        printf(" ");
                        colors("0");
                      } 
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
