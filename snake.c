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

void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s) {
  l->M = M;
  l->N = N;
  l->labyrinth_matrix = malloc(sizeof(int[N][M]));
  l->score = 1000;
  l->drill = 0;

  s->head = 'O';
  s->x_snake_pos = 0;
  s->y_snake_pos = 0;
  s->next = NULL;

  for (int j = 0; j < N; j++) {
    l->labyrinth_matrix[j] = (char *) malloc(sizeof(char) * M);
    scanf(" %[^\n]s", l->labyrinth_matrix[j]);
  }
}

void labyrinth_free (labyrinth_t *l, snake_t *s) {
  for (int i = 0; i < l->M; ++i)
    free(l->labyrinth_matrix[i]);
  free(l->labyrinth_matrix);
  free(l);
  free(s);
}

void labyrinth_print (labyrinth_t *l, int M, int N, snake_t *s) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (j == s->x_snake_pos && i == s->y_snake_pos) {
        printf(BOLD_COLOR_WHITE "%c ", s->head);
        printf(COLOR_RESET);
      } else {
        int is_tail = 0;
        snake_t *tail = s->next;
        while (tail != NULL) {
          if (i == tail->y_snake_pos && j == tail->x_snake_pos) {
            printf(BOLD_COLOR_WHITE "%c ", tail->head);
            is_tail = 1;
            break;
          }
          tail = tail->next;
        }
        if (!is_tail) {
          if (l->labyrinth_matrix[i][j] == '#') {
            printf(BOLD_COLOR_RED "%c ", l->labyrinth_matrix[i][j]);
            printf(COLOR_RESET);
          } else {
            if (l->labyrinth_matrix[i][j] == '$') {
              printf(BOLD_COLOR_PURPLE "%c ", l->labyrinth_matrix[i][j]);
              printf(COLOR_RESET);
            } else {
              if (l->labyrinth_matrix[i][j] == 'T') {
                printf(BOLD_COLOR_BLUE "%c ", l->labyrinth_matrix[i][j]);
                printf(COLOR_RESET);
              } else {
                if (l->labyrinth_matrix[i][j] == '!') {
                  printf(BOLD_COLOR_GREEN "%c ", l->labyrinth_matrix[i][j]);
                  printf(COLOR_RESET);
                } else {
                  printf("%c ", l->labyrinth_matrix[i][j]);
                }
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

void find_initial_position (labyrinth_t *l, int *x, int *y) {
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

void moves_input (char *move, char *moves, int *row, int *col, int *score, snake_t *head, labyrinth_t *l) {
  printf(BOLD_COLOR_WHITE "Enter a move (" BOLD_COLOR_GREEN "N" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "S" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "E" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "O" BOLD_COLOR_WHITE "): ");
  printf(COLOR_RESET);
  
  scanf("%c", move);
  *move = getchar();
  
  char *tmp = moves;
  
  int old_x = head->x_snake_pos;
  int old_y = head->y_snake_pos;
  int count = 0;
  
  snake_t *prev = head;

  switch (*move) {
    case 'N':
      *tmp = *move;
      *row -= 1;
      *score -= 1;
      head->y_snake_pos -= 1;
    break;
    case 'O':
      *tmp = *move;
      *col -= 1;
      *score -= 1;
      head->x_snake_pos -= 1;
    break;
    case 'S':
      *tmp = *move;
      *row += 1;
      *score -= 1;
      head->y_snake_pos += 1;
    break;
    case 'E':
      *tmp = *move;
      *col += 1;
      *score -= 1;
      head->x_snake_pos += 1;
    break;
    default:
      printf("Invalid move!\n");
    break;
  }

  prev = head->next;
  while (prev != NULL) {
    if (head->x_snake_pos == prev->x_snake_pos && head->y_snake_pos == prev->y_snake_pos) {
      // elimino parte compresa tra incontro e coda
      while (prev->next != NULL) {
        count++;
        snake_t *temp = prev->next;
        prev->next = temp->next;
        free(temp);
      }
      break;
    }
    prev = prev->next;
  }
  
  l->score -= count * 10;

  //aggiorno parti del corpo
  prev = head->next;
  while (prev != NULL) {
    int temp_x = prev->x_snake_pos;
    int temp_y = prev->y_snake_pos;
    prev->x_snake_pos = old_x;
    prev->y_snake_pos = old_y;
    old_x = temp_x;
    old_y = temp_y;
    prev = prev->next;
  }
}

void obstacles_borders_check (labyrinth_t *l, snake_t *head, int *row, int *col, int *N, int *M) {
  if (*row < 0 || *row == l->N || *col < 0 || *col == l->M) {
    printf("Invalid move!\n");
    exit(1);
  }

  if (l->labyrinth_matrix[*row][*col] == '#') {
    if (l->drill <= 0) {
      printf("Game over! You hit a wall.\n");
      exit(1);
    } else {
      l->drill -= 1;
    }
  }
  
  if (l->labyrinth_matrix[*row][*col] == '!') {
    //l->score = 1000 + ((l->score - 1000) / 2);
    l->labyrinth_matrix[*row][*col] = ' ';

    int length = 0;
    snake_t* temp = head;
    while (temp != NULL) {
      length++;
      temp = temp->next;
    }

    // Dimezza la lunghezza
    length /= 2;
    l->score -= length * 10;

    // Rimuovi gli elementi dalla lista
    if (length > 0) {
      snake_t* temp = head;
      for (int i = 0; i < length-1; i++) {
        temp = temp->next;
      }
      while (temp->next != NULL) {
        snake_t* to_remove = temp->next;
        temp->next = to_remove->next;
        free(to_remove);
      }
    }
  }

  if (l->labyrinth_matrix[*row][*col] == 'T') {
    l->drill += 3;
    l->labyrinth_matrix[*row][*col] = ' ';
  }
}

void add_tail (snake_t *head) {
  snake_t *tail = head;
  while (tail->next != NULL)
    tail = tail->next;
  tail->next = (snake_t *) malloc(sizeof(snake_t));
  tail->next->head = 'o';
  tail->next->x_snake_pos = tail->x_snake_pos;
  tail->next->y_snake_pos = tail->y_snake_pos;
  tail->next->next = NULL;
}

void check_dead_ends (labyrinth_t *l, snake_t *head) {
  int row = head->y_snake_pos, col = head->x_snake_pos;
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
    return;
  }
  if (l->labyrinth_matrix[head->y_snake_pos -1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
    return;
  }
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos-1][head->x_snake_pos] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
    return;
  }
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos-1][head->x_snake_pos] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
    return;
  }
}

void labyrinth_interactive_mode_run (int M, int N) {
  labyrinth_t *l = (labyrinth_t *) malloc(sizeof(labyrinth_t));
  snake_t *s = (snake_t *) malloc(sizeof(snake_t));
  char *moves = (char *) malloc(M * N + 1);
  char *tmp = moves; 
  labyrinth_init(l, M, N, s);

  find_initial_position(l, &s->x_snake_pos, &s->y_snake_pos);

  char move;
  bool win = false;

  while (!win) {
    system("clear");
    labyrinth_print(l, l->M, l->N, s);

    int row = s->y_snake_pos, col = s->x_snake_pos;

    moves_input(&move, tmp++, &row, &col, &l->score, s, l);
    
    check_dead_ends(l, s);

    obstacles_borders_check(l, s, &row, &col, &N, &M);

    if (l->labyrinth_matrix[row][col] == '$') {
      l->score += 10;
      l->labyrinth_matrix[row][col] = ' ';
      add_tail(s); 
    }

    s->y_snake_pos = row;
    s->x_snake_pos = col;

    if (l->labyrinth_matrix[row][col] == '_') {
      *(tmp++) = '\0';
      moves = realloc(moves, tmp - moves);
      system("clear");
      printf(COLOR_GREEN_HIGH_BACKGROUND BOLD_COLOR_BLACK "%s\n", moves);
      win = true; 
    }
  }
  labyrinth_free(l, s);
  exit(0);
}
