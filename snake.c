/**
 * @file snake.c
 * @author Mattia Forlin, Matteo Toffoli
 * @brief Header's functions implementation.
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "snake.h"
#include "colors.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct snake {
  char head;
  int x_snake_pos;
  int y_snake_pos;
  snake_t *next;
};

struct labyrinth {
  int M;
  int N;
  char **labyrinth_matrix;
  int score;
  int drill;
};

void labyrinth_init(labyrinth_t *l, int M, int N, snake_t *s) {
  l->M = M;
  l->N = N;
  l->labyrinth_matrix = malloc(sizeof(char *) * M);
  l->score = 1000;
  l->drill = 0;

  s->head = 'o';
  s->x_snake_pos = 0;
  s->y_snake_pos = 0;
  s->next = NULL;

  for (int j = 0; j < N; j++) {
    l->labyrinth_matrix[j] = (char*) malloc(sizeof(char) * N);
    scanf(" %[^\n]s", l->labyrinth_matrix[j]);
  }
}

void labyrinth_free(labyrinth_t *l, snake_t* s) {
  for (int i = 0; i < l->M; ++i)
    free(l->labyrinth_matrix[i]);
  free(l->labyrinth_matrix);
  free(l);
  free(s);
}

void labyrinth_print(labyrinth_t *l, int M, int N, snake_t *s) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (j == s->x_snake_pos && i == s->y_snake_pos) {
        snake_t *tail = s;
        printf(BOLD_COLOR_WHITE "%c", tail->head);
        printf(COLOR_RESET);
        while (tail->next != NULL) {
          tail = tail->next;
          printf(BOLD_COLOR_WHITE "%c", tail->head);
          printf(COLOR_RESET);
        }
      } else {
        if (l->labyrinth_matrix[i][j] == '#') {
          printf(BOLD_COLOR_RED "%c", l->labyrinth_matrix[i][j]);
          printf(COLOR_RESET);
        } else {
          if (l->labyrinth_matrix[i][j] == '$') {
            printf(BOLD_COLOR_PURPLE "%c", l->labyrinth_matrix[i][j]);
            printf(COLOR_RESET);
          } else {
            if (l->labyrinth_matrix[i][j] == 'T') {
              printf(BOLD_COLOR_BLUE "%c", l->labyrinth_matrix[i][j]);
              printf(COLOR_RESET);
            } else {
              if (l->labyrinth_matrix[i][j] == '!') {
                printf(BOLD_COLOR_GREEN "%c", l->labyrinth_matrix[i][j]);
                printf(COLOR_RESET);
              } else {
                printf("%c", l->labyrinth_matrix[i][j]);
              }
            }
          }
        }
      }
    }
    printf("\n");
  }
  printf(COLOR_WHITE_HIGH_BACKGROUND BOLD_COLOR_BLACK "SCORE: %d\n", l->score);
  printf(COLOR_RESET);
  printf(COLOR_WHITE_HIGH_BACKGROUND BOLD_COLOR_BLACK "DRILL: %d\n", l->drill);
  printf(COLOR_RESET);
}

void find_initial_position(labyrinth_t *l, int *x, int *y) {
  int i = 0, j = 0;
  bool found = false;
  while (i < l->N) {
    while (j < l->M && !found) {
      if (l->labyrinth_matrix[i][j] == 'o') {
        found = true;
        *x = j;
        *y = i;
        l->labyrinth_matrix[i][j] = ' ';
      }
      j++;
    }
    j = 0;
    i++;
  }
}

void labyrinth_run(int M, int N) {
  labyrinth_t *l = (labyrinth_t *)malloc(sizeof(labyrinth_t));
  snake_t *s = (snake_t *)malloc(sizeof(snake_t));
  char *moves = (char *) malloc(M * N + 1);
  char *tmp = moves;
  labyrinth_init(l, M, N, s);

  find_initial_position(l, &s->x_snake_pos, &s->y_snake_pos);

  char move;
  bool win = false;

  while (!win) {
    system("clear");
    labyrinth_print(l, l->M, l->N, s);

    printf(BOLD_COLOR_WHITE "Enter a move (" BOLD_COLOR_GREEN "N" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "S" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "E" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "O" BOLD_COLOR_WHITE "): ");
    printf(COLOR_RESET);
    scanf("%c", &move);
    move = getchar();

    int row = s->y_snake_pos;
    int col = s->x_snake_pos;
    
    switch (move) {
      case 'N':
        *(tmp++) = move;
        row--;
        l->score--;
        break;
      case 'O':
        *(tmp++) = move;
        col--;
        l->score--;
        break;
      case 'S':
        *(tmp++) = move;
        row++;
        l->score--;
        break;
      case 'E':
        *(tmp++) = move;
        col++;
        l->score--;
        break;
      default:
        printf("Invalid move!\n");
        break;
    }

    if (l->labyrinth_matrix[row][col] == '#' && l->drill > 0 && (row > 0 || row < N) && (col > 0 || col < M)) {
      l->drill -= 1;
      l->labyrinth_matrix[row][col] = ' ';
    }

    if (row <= 0 || row >= N || col <= 0 || col >= M) {
      printf("Invalid move!\n");
      return;
    }
    
    if (l->labyrinth_matrix[row][col] == '$') {
      l->score += 10;
      l->labyrinth_matrix[row][col] = ' ';
      snake_t *tail = s;
      while (tail->next != NULL)
        tail = tail->next;
      tail->next = (snake_t*) malloc(sizeof(snake_t));
      tail->next->head = 'o';
      tail->next->x_snake_pos = s->x_snake_pos;
      tail->next->y_snake_pos = s->y_snake_pos;
      tail->next->next = NULL;
    }

    if (l->labyrinth_matrix[row][col] == '!') {
      l->score = 1000 + ((l->score - 1000) / 2);
      l->labyrinth_matrix[row][col] = ' ';
    }
    
    if (l->labyrinth_matrix[row][col] == 'T') {
      l->drill += 3;
      l->labyrinth_matrix[row][col] = ' ';
    }

    s->y_snake_pos = row;
    s->x_snake_pos = col;
    snake_t *node = s;
    while (node->next != NULL) {
        int tmp_x = node->x_snake_pos, tmp_y = node->y_snake_pos;
        node->x_snake_pos = row;
        node->y_snake_pos = col;
        row = tmp_x;
        col = tmp_y;
        node = node->next;
    }

    if (l->labyrinth_matrix[row][col] == '_') {
      *(tmp++) = '\0';
      moves = realloc(moves, tmp-moves);
      system("clear");
      printf(COLOR_GREEN_HIGH_BACKGROUND BOLD_COLOR_BLACK "%s\n", moves);
      win = true;
    }
  }
  labyrinth_free(l, s);
  exit(0);
}
