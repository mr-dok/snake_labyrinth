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
#include <time.h>
#include <unistd.h>
#include <string.h>

struct snake {
  char head;          /**< The character representing the snake's head. */
  int x_snake_pos;    /**< The X-coordinate of the snake's position. */
  int y_snake_pos;    /**< The Y-coordinate of the snake's position. */
  snake_t *next;      /**< Pointer to the next segment of the snake. */
};

struct labyrinth {
  int M;                    /**< The width of the labyrinth. */
  int N;                    /**< The height of the labyrinth. */
  char **labyrinth_matrix;  /**< The matrix representing the labyrinth layout. */
  int score;                /**< The current score of the game. */
  int drill;                /**< The number of drills available. */
};

void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s) {
  l->M = M;
  l->N = N;
  l->labyrinth_matrix = (char **) malloc(sizeof(char *) * N);
  
  if (l->labyrinth_matrix == NULL) {
    printf("error while allocating labyrinth_matrix\n");
    return;
  }

  for (int j = 0; j < N; j++) {
    l->labyrinth_matrix[j] = (char *) malloc(sizeof(char) * M + 1);
    if (l->labyrinth_matrix[j] == NULL) {
      printf("error while allocating row %d of labyrinth_matrix\n", j);
      for (int k = 0; k < j; k++) {
        free(l->labyrinth_matrix[k]);
      }
      free(l->labyrinth_matrix);
      return;
    }
    scanf(" %[^\n]s", l->labyrinth_matrix[j]);
  }

  l->score = 1000;
  l->drill = 0;

  s->head = 'O';
  s->x_snake_pos = 0;
  s->y_snake_pos = 0;
  s->next = NULL;
}

void labyrinth_free (labyrinth_t *l, snake_t *s) {
  for (int i = 0; i < l->N; ++i)
    free(l->labyrinth_matrix[i]);
  free(l->labyrinth_matrix);
  free(l);
  free(s);
}

void labyrinth_print (labyrinth_t *l, snake_t *s) {
  for (int i = 0; i < l->N; i++) {
    for (int j = 0; j < l->M; j++) {
      if (j == s->x_snake_pos && i == s->y_snake_pos) {
        printf(BOLD_COLOR_WHITE "%c ", s->head);
        printf(COLOR_RESET);
      } else {
        int is_tail = 0;
        snake_t *tail = s->next;
        while (tail != NULL) {
          if (i == tail->y_snake_pos && j == tail->x_snake_pos) {
            printf(BOLD_COLOR_WHITE "%c ", tail->head);
            printf(COLOR_RESET);
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

void moves_input (char *move, char *moves, int *row, int *col, int *score, snake_t *head, labyrinth_t *l, int mode) {
  if (mode == 1) {
    printf(BOLD_COLOR_WHITE "Enter a move (" BOLD_COLOR_GREEN "N" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "S" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "E" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "O" BOLD_COLOR_WHITE "): ");
    printf(COLOR_RESET);
  
    while (scanf("%c ", move) != 1) {
      int c;
      while((c=getchar()) != '\n' && c != EOF); //Clear the stdin
      printf("Invalid input. Try again\n");
      printf(BOLD_COLOR_WHITE "Enter a move (" BOLD_COLOR_GREEN "N" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "S" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "E" BOLD_COLOR_WHITE "/" BOLD_COLOR_GREEN "O" BOLD_COLOR_WHITE "): ");
      printf(COLOR_RESET);
    }
    *move = getchar();
  }

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

void obstacles_borders_check (labyrinth_t *l, snake_t *head, int *row, int *col) {
  
  if (*row < 0 || *row == l->N || *col < 0 || *col == l->M) {
    printf("Invalid move!\n");
    labyrinth_free(l, head);
    exit(1);
  }

  if (l->labyrinth_matrix[*row][*col] == '#') {
    if (l->drill <= 0) {
      printf("Game over! You hit a wall.\n");
      labyrinth_free(l, head);
      exit(1);
    } else {
      l->drill -= 1;
      l->labyrinth_matrix[*row][*col] = ' ';
    }
  }
  
  if (l->labyrinth_matrix[*row][*col] == '!') {
    l->labyrinth_matrix[*row][*col] = ' ';

    int length = 0;
    snake_t* temp = head;
    while (temp != NULL) {
      length++;
      temp = temp->next;
    }

    // Dimezza la lunghezza
    length /= 2;
    l->score = 1000 + ((l->score - 1000) / 2);

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
  if (!head->next)
    return;
  int row = head->y_snake_pos, col = head->x_snake_pos;
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
  }
  if (l->labyrinth_matrix[head->y_snake_pos -1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#' && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
  }
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos-1][head->x_snake_pos] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos+1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
  }
  if (l->labyrinth_matrix[head->y_snake_pos +1][head->x_snake_pos] == '#' && l->labyrinth_matrix[head->y_snake_pos-1][head->x_snake_pos] == '#'  && l->labyrinth_matrix[head->y_snake_pos][head->x_snake_pos-1] == '#') {
    head->next->next = NULL;
    int new_head_row = head->next->y_snake_pos;
    int new_head_col = head->next->x_snake_pos;
    head->next->y_snake_pos = row;
    head->next->x_snake_pos = col;
    head->y_snake_pos = new_head_row;
    head->x_snake_pos = new_head_col;
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
    labyrinth_print(l, s);

    int row = s->y_snake_pos, col = s->x_snake_pos;

    moves_input(&move, tmp++, &row, &col, &l->score, s, l, 1);
    obstacles_borders_check(l, s, &row, &col);
    
    if (l->labyrinth_matrix[row][col] == '_') {
      *(tmp++) = '\0';
      moves = realloc(moves, tmp - moves);
      system("clear");
      printf(COLOR_GREEN_HIGH_BACKGROUND BOLD_COLOR_BLACK "%s\n", moves);
      printf(COLOR_RESET);
      win = true; 
      free(moves);
    } else {
      check_dead_ends(l, s);  

      if (l->labyrinth_matrix[row][col] == '$') {
        l->score += 10;
        l->labyrinth_matrix[row][col] = ' ';
        add_tail(s); 
      }

      s->y_snake_pos = row;
      s->x_snake_pos = col;
    }
  }
  labyrinth_free(l, s);
  exit(0);
}
<<<<<<< HEAD

int checkXWest(labyrinth_t *l, int row, int col) {
  if(col-1< 0 || l->labyrinth_matrix[row][col-1] == '#')
    return 0;  
  else
    return 1;
}

int checkXEast(labyrinth_t *l, int row, int col) {
  if(col+1 >= l->M || l->labyrinth_matrix[row][col+1] == '#')
    return 0;
  else
    return 1;
}

int checkYNorth(labyrinth_t *l, int row, int col) {
  if(row-1 < 0 || l->labyrinth_matrix[row-1][col] == '#')
    return 0;
  else
    return 1;
}

int checkYSouth(labyrinth_t *l, int row, int col) {
  if(row+1 >= l->N || l->labyrinth_matrix[row+1][col] == '#')
    return 0;
  else
    return 1;
}

void labyrinth_AI_mode_run(int M, int N) {
  labyrinth_t *l = (labyrinth_t *) malloc(sizeof(labyrinth_t));
  snake_t *s = (snake_t *) malloc(sizeof(snake_t));
  char *moves = (char *) malloc(M * N + 1);
  char *tmp = moves; 
  labyrinth_init(l, M, N, s);

  find_initial_position(l, &s->x_snake_pos, &s->y_snake_pos);
  char move = 'S';
  char move_prec = move;
  bool win = false;

  while (!win) {
    system("clear");
    labyrinth_print(l, s);

    int row = s->y_snake_pos, col = s->x_snake_pos;

    if(move_prec == 'N') {
      if(checkXEast(l,row,col)) {
        move = 'E';
      } else if(checkYNorth(l,row,col)) {
        move = 'N';
      } else if(checkXWest(l,row,col)) {
        move = 'O';
      } else if(checkYSouth(l,row,col)) {
        move = 'S';
      }
    } else {
      if(move_prec == 'S') {
        if(checkXWest(l,row,col)) {
          move = 'O';
        } else if(checkYSouth(l,row,col)) {
          move = 'S';
        } else if(checkXEast(l,row,col)) {
          move = 'E';
        } else if(checkYNorth(l,row,col)) {
          move = 'N';
        }
      } else {
        if(move_prec=='E') {
          if(checkYSouth(l,row,col)) {
            move = 'S';
          } else if(checkXEast(l,row,col)) {
            move = 'E';
          } else if(checkYNorth(l,row,col)) {
            move = 'N';
          } else if(checkXWest(l,row,col)) {
            move = 'O';
          }
        } else if(move_prec=='O') {
          if(checkYNorth(l,row,col)) {
            move = 'N';
          } else if(checkXWest(l,row,col)) {
            move = 'O';
          } else if(checkYSouth(l,row,col)) {
            move = 'S';
          } else if(checkXEast(l,row,col)) {
            move = 'E';
          }
        }
      }
    }
    moves_input(&move, tmp++, &row, &col, &l->score, s, l, 0);
    
    if (l->labyrinth_matrix[row][col] == '_') {
      *(tmp++) = '\0';
      moves = realloc(moves, tmp - moves);
      system("clear");
      printf(COLOR_GREEN_HIGH_BACKGROUND BOLD_COLOR_BLACK "%s\n", moves);
      printf(COLOR_RESET);
      win = true; 
      free(moves);
    } else {
      if (l->labyrinth_matrix[row][col] == '$') {
        l->score += 10;
        l->labyrinth_matrix[row][col] = ' ';
        add_tail(s); 
      }

      s->y_snake_pos = row;
      s->x_snake_pos = col;
    }
    move_prec = move;
  }
  labyrinth_free(l, s);
  exit(0);
}
=======
>>>>>>> 1624ea31bd9a26a92ec598deea45db837e111bc9
