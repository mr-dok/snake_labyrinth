#include "snake.h"
#include <stdlib.h>

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
  t->labyrinth_matrix = malloc(sizeof(labyrinth_t *) * M); 
}
