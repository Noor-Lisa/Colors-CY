#include <stdio.h>
#include "board.h"

void filingBoard( int (*square)[SIZETAB]){
    
    // Remplissage du tableau de couleurs
    for (int i = 0; i < SIZETAB; i++) {
      for (int j = 0; j < SIZETAB; j++) {
         if(i+j==3||i+j==11){//magenta clair
            square[i][j]=4;
          }
         if(j-i==4||i-j==4){//jaune
            square[i][j]=2;
          } 
          if(i==j){//rouge 
            square[i][j]=0; 
          }
          if(i+j==7){ //noir 
            square[i][j]=7;
          }
          if(i-j==2&&i%2!=0){ //bleu
            square[i][j]=3;
          }
          if(j-i==2&&i%2==0){
            square[i][j]=3;
          }
          if(j-i==2&&i%2!=0){//magenta foncé
            square[i][j]=6;
          }
          if(i-j==2&&i%2==0){
            square[i][j]=6;
          }
          if(i==6&&j==0||i==1&&j==7){
            square[i][j]=3;
          }
          if(i==0&&j==6||i==7&&j==1){
            square[i][j]=6;
          }
         if(i+j==5&&i%2==0){//cyan
            square[i][j]=5;
          }
          if(i+j==9&&i%2!=0){
            square[i][j]=5;
          }
          if(i==6&&j==7){
            square[i][j]=5;
          }
          if(i==1&&j==0){
            square[i][j]=5;
          }
          if(i+j==5&&i%2!=0){ //vert 
            square[i][j]=1;
          }
          if(i+j==9&&i%2==0){
            square[i][j]=1;
          }
          if(i==7&&j==6){
            square[i][j]=1;
          }
          if(i==0&&j==1){
            square[i][j]=1;
          }
          
      }    
    }
}


void piece(int a, int b){

  char colorStr[20];
  sprintf(colorStr, "%d", a); // Formatage de la valeur de pa
    colors(colorStr);  // Affichage de la couleur pour pa
  
    sprintf(colorStr, "%d", b);  // Formatage de la valeur de pb
    colors(colorStr); 
printf("[*]");
colors("0");
}

void displayBoardPiece(int *width, int *height,int (*square)[SIZETAB], int x) {
  int a,b;
  printf("    1    2    3    4    5    6    7    8   ");
  printf("\n");
  // Affichage du tableau de couleurs
    for (int i = 0; i < SIZETAB; i++) {
      for(int k=0; k<*height; k++){ // Agrandir la taile de la case
        if(k==0){
        printf("  ");
        }
          if(k==1&&i==0){ 
         printf("1 ");          
        }   
        if(k==1&&i==1){ 
         printf("2 ");          
        } 
        if(k==1&&i==2){ 
         printf("3 ");          
        } 
        if(k==1&&i==3){ 
         printf("4 ");          
        } 
        if(k==1&&i==4){ 
         printf("5 ");          
        } 
        if(k==1&&i==5){ 
         printf("6 ");          
        } 
        if(k==1&&i==6){ 
         printf("7 ");          
        } 
        if(k==1&&i==7){ 
         printf("8 ");          
        } 
        if(k==2){
          printf("  ");
        }
        for (int j = 0; j < SIZETAB; j++) {
            switch (square[i][j]) {
              case 0: // Rouge
                for (x = 0; x < *width; x++) {
                  if(i==0 && k==1 && x==1){
                    colors("101;7"); 
                    printf("[");
                    colors("0");
                    /*a=101;
                    b=7;
                    piece(a,b);*/
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
                    for (x = 0; x < *width; x++) {
                      /*if(i==0 && k==1 && (x==4 || x==5)){
                        colors("102"); 
                        printf(" ");
                        colors("0");
                      }*/
                      if(i==0 && k==1 && x==1){
                        colors("102;7"); 
                        printf("[");
                        colors("0");
                        /*a=102;
                        b=7;
                        piece(a,b);*/
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
                    for (x = 0; x < *width; x++) {
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
                    for (x = 0; x < *width; x++) {
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
                    for (x = 0; x < *width; x++) {
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
                      else {
                        colors("105"); 
                        printf(" ");
                        colors("0");
                      } 
                    }
                    break;
                case 5: // Cyan
                    for (x = 0; x < *width; x++) {
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
                    for (x = 0; x < *width; x++) {
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
                    for (x = 0; x < *width; x++) {
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
}
void move(int (*square)[SIZETAB], int *px, int *py, int *pa, int *py){
  int i=SIZETAB;
  int j=SIZETAB;
  int square[i][j];
  i=*px;
  j=*py;
  piece(a,b);
  
}

void coordinates(){
  int x, y,a,b
  Piece a;
  int *px =&x
  int *py =&y
  int *pa =&a
  int *pb =&b
    do{
      printf("\nQuel pion souhaitez-vous déplacer ? (coordonnée x, y)\n");
      scanf("%d %d", &a, &b);
    } while(a<1 || a>8 || b<1 || b>8);  
    do{
      printf("Entrez les coordonnées (x, y) du pion à déplacer : ");
      scanf("%d %d", &x, &y);
    } while(x<1 || x>8 || y<1 || y>8);  
  move(square, px, py, pa, pb);
}

int main(){
  int width = 5;
  int * pwidth = &width;
  int height=3;
  int * pheight = &height;
  int x,a,b;
  int *px=&x;
  /*a = 101;
  b= 7;
  int * pa = &a;
  int * pb = &b;*/
  Square square[SIZETAB][SIZETAB];// Déclaration du tableau de couleurs
  filingBoard(square);
  displayBoardPiece(pwidth, pheight, square, x);  
  move();
  return 0;
}
