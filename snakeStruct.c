//FUNZIONANTE
//labyrinth[snake_y][snake_x] = ' '; manca questo per far sparire moneta dopo che la raccolgo
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 20
#define COLS 20

// Struttura per rappresentare la posizione del serpente
struct Snake {
  int row;
  int col;
};

int main(void) {
  char maze[ROWS][COLS] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '$', ' ', ' ', ' ', ' ', ' ', '$', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '_', '#'},
};
  struct Snake snake = {.row=1,
  .col=0}; // Posizione iniziale del serpente
  int score = 0; // Punteggio iniziale

  while (true) {
    // Visualizzazione del labirinto con il serpente
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        if (i == snake.row && j == snake.col) {
          printf("o ");
        } else {
          printf("%c ", maze[i][j]);
        }
      }
      printf("\n");
    }
    printf("Punteggio: %d\n", score);

    // Ricezione della mossa da parte dell'utente
    printf("Inserisci mossa (W, A, S, D): ");
    char move;
    scanf(" %c", &move);

    // Aggiornamento della posizione del serpente in base alla mossa
    int row = snake.row;
    int col = snake.col;
    switch (move) {
      case 'W':
        row--;
        break;
      case 'A':
        col--;
        break;
      case 'S':
        row++;
        break;
      case 'D':
        col++;
        break;
      default:
        printf("Mossa non valida!\n");
        continue;
    }

    // Controllo se la posizione successiva è valida
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
      printf("Mossa non valida!\n");
      continue;
    }

    // Aggiornamento del punteggio se viene raccolta una moneta
    if (maze[row][col] == '$') {
      score += 10;
    }

    // Aggiornamento della posizione del serpente
    snake.row = row;
    snake.col = col;

    // Controllo se il serpente ha raggiunto l'uscita
    if (maze[row][col] == '_') {
      printf("Complimenti, hai vinto! Punteggio finale: %d\n", score);
      return 0;
    }
  }

  return 0;
}
