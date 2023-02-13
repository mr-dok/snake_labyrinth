//FUNZIONANTE
#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLUMNS 30

char labyrinth[ROWS][COLUMNS] = {
  "#############################",
  "     $     !                #",
  "# #### #### #### #### ##### #",
  "# #  #   #   #   #  #    #  #",
  "# ##### #### #### ### #### ##",
  "_        #     #     #      #",
  "####### #### #### ######$## #",
  "#      #   # #  # #    #    #",
  "# #### ##### #### #### #### #",
  "#############################"
};

int snake_x = 0;
int snake_y = 1;
int score = 0;
int moves = 0;

void move_snake(int x, int y) {
  char current_square = labyrinth[y][x];

  if (current_square == '#') {
    printf("Snake ran into a wall! Game over.\n");
    exit(0);
  } else if (current_square == '_') {
    printf("Snake found the exit in %d moves! Final score: %d\n", moves, score);
    exit(0);
  } else if (current_square == '$') {
    score++;
  } else if (current_square == '!') {
    score--;
  }

  labyrinth[snake_y][snake_x] = ' ';
  snake_x = x;
  snake_y = y;
  labyrinth[y][x] = 'o';
  moves++;
}

void draw_labyrinth() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      printf("%c ", labyrinth[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("Current score: %d\n", score);
  printf("Moves: %d\n", moves);
}

int main() {
  while (1) {
    draw_labyrinth();

    char input;
    printf("Enter move (N/S/E/O): ");
    scanf(" %c", &input);

    switch (input) {
      case 'N':
        move_snake(snake_x, snake_y - 1);
        break;
      case 'O':
        move_snake(snake_x - 1, snake_y);
        break;
      case 'S':
        move_snake(snake_x, snake_y + 1);
        break;
      case 'E':
        move_snake(snake_x + 1, snake_y);
        break;
      default:
        printf("Invalid move.\n");
        break;
    }
  }

  return 0;
}
