#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

struct snake_t {
  int data;
  int pos;
  snake_t *next;
};

struct labyrinth {
  int M;
  int N;
  char **labyrinth_matrix;
};

void labyrinth_init (labyrinth_t *l, int M, int N) {
  l->M = M;
  l->N = N;
  l->labyrinth_matrix = malloc(sizeof(char *) * M);

  for (int j = 0; j < N; j++) {
    l->labyrinth_matrix[j] = malloc(sizeof(char) * N); 
    scanf(" %[^\n]s", l->labyrinth_matrix[j]);
  }
}

void labyrinth_print(labyrinth_t *l, int M, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%c", l->labyrinth_matrix[i][j]);
    }
    printf("\n");
  }
}

void labyrinth_run(int M, int N) {
  labyrinth_t *l = (labyrinth_t *) malloc(sizeof(labyrinth_t));
  labyrinth_init(l, M, N);
  labyrinth_print(l, M, N);
}
