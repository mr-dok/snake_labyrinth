#include "snake.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct snake {
  int data;
  int x_snake_pos;
  int y_snake_pos;
  snake_t *next;
};

struct labyrinth {
  int M;
  int N;
  char **labyrinth_matrix;
  int score;
  char moves[200];
};

void labyrinth_init(labyrinth_t *l, int M, int N) {
  l->M = M;
  l->N = N;
  l->labyrinth_matrix = malloc(sizeof(char *) * M);
  l->score = 0;

  for (int j = 0; j < N; j++) {
    l->labyrinth_matrix[j] = malloc(sizeof(char) * N);
    scanf(" %[^\n]s", l->labyrinth_matrix[j]);
  }
}

void labyrinth_free(labyrinth_t *l, snake_t* s) {
  for (int i = 0; i < l->M; ++i)
    free(l->labyrinth_matrix[i]);
  free(l->labyrinth_matrix);
  free(s);
}

void labyrinth_print(labyrinth_t *l, int M, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printf("%c", l->labyrinth_matrix[i][j]);
    }
    printf("\n");
  }
}

void find_initial_position(labyrinth_t *l, int *x, int *y) {
  int i = 0, j = 0;
  bool found = false;
  while (i < l->N) {
    while (j < l->M && !found) {
      if (l->labyrinth_matrix[i][j] == 'o') {
        found = true;
        *x = i;
        *y = j;
      }
      j++;
    }
    j = 0;
    i++;
  }
}

void move_snake(labyrinth_t *l, snake_t *s, int x, int y) {
  char current_square = l->labyrinth_matrix[y][x];

  if (current_square == '#') {
    printf("Snake ran into a wall! Game over.\n");
    exit(0);
  } else if (current_square == '_') {
    printf("%s\n", l->moves);
    exit(0);
  } else if (current_square == '$') {
    l->score += 10;
  } else if (current_square == '!') {
    l->score /= 2;
  }

  l->labyrinth_matrix[s->y_snake_pos][s->x_snake_pos] = ' ';
  s->x_snake_pos = x;
  s->y_snake_pos = y;
  l->labyrinth_matrix[y][x] = 'o';
}

void labyrinth_run(int M, int N) {
  labyrinth_t *l = (labyrinth_t *)malloc(sizeof(labyrinth_t));
  snake_t *s = (snake_t *)malloc(sizeof(snake_t));
  labyrinth_init(l, M, N);

  find_initial_position(l, &s->x_snake_pos, &s->y_snake_pos);

  char move;

  while (l->labyrinth_matrix[s->x_snake_pos][s->y_snake_pos] != '_') {
    labyrinth_print(l, M, N);

    printf("Enter a move (N/S/E/O): ");
    scanf("%c", &move);
    getchar();
    switch (move) {
      case 'N':
        sprintf(l->moves, "%s%c", l->moves, move);
        move_snake(l, s, s->x_snake_pos, s->y_snake_pos - 1);
        break;
      case 'O':
        sprintf(l->moves, "%s%c", l->moves, move);
        move_snake(l, s, s->x_snake_pos - 1, s->y_snake_pos);
        break;
      case 'S':
        sprintf(l->moves, "%s%c", l->moves, move);
        move_snake(l, s, s->x_snake_pos, s->y_snake_pos + 1);
        break;
      case 'E':
        sprintf(l->moves, "%s%c", l->moves, move);
        move_snake(l, s, s->x_snake_pos + 1, s->y_snake_pos);
        break;
      default:
        printf("Invalid move!\n");
        break;
    }
  }
  labyrinth_free(l, s);
}
