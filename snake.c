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

void labyrinth_init (labyrinth_t *t, int M, int N) {
  t->M = M;
  t->N = N;
  t->labyrinth_matrix = malloc(sizeof(char *) * M);

  for (int j = 0; j < M; j++) {
    t->labyrinth_matrix[j] = malloc(sizeof(char *) * N);
    for (int i = 0; i < N; i++) {
      scanf(" %[^\n]s", t->labyrinth_matrix[i]);
    }
  }
}

void labyrinth_run(int M, int N) {
  labyrinth_t *l = (labyrinth_t *) malloc(sizeof(labyrinth_t));
  labyrinth_init(l, M, N);
}
