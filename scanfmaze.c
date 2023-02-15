#include <stdio.h>

int main() {
    int M, N;
    scanf("%d",&M); //colonne
    scanf("%d",&N); //righe
    int COLS=M;
    int ROWS=N;
    char game_board[ROWS][COLS];

    // leggi le righe del piano di gioco
    for (int i = 0; i < N; i++) {
        printf("inserisci un carattere %d: \n",i); 
        scanf(" %[^\n]s",game_board[i]); // leggi una riga del piano di gioco come una stringa
    }


    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
          printf("%c ", game_board[i][j]);
        }
      printf("\n");
    }
    
    return 0;
}
