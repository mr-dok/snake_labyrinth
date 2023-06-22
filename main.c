/**
 * @file main.c
 * @author Mattia Forlin, Matteo Toffoli
 * @brief Project's main file.
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "snake.h"
#include "colors.h"

int main (void) {
  int M = 0, N = 0, game_mode = 0; 

  system("clear");

  printf(BOLD_COLOR_WHITE "1. Interactive mode\n" COLOR_RESET);
  printf(BOLD_COLOR_WHITE "2. AI mode\n" COLOR_RESET); 
  printf(BOLD_COLOR_WHITE "Select the game mode: " COLOR_RESET); 
  
  while (scanf("%d", &game_mode) == 0) {
    int c;
    while((c=getchar())!='\n' && c!=EOF); //Clear the stdin
    printf("Invalid input. Try again\n");
    printf(BOLD_COLOR_WHITE "1. Interactive mode\n" COLOR_RESET);
    printf(BOLD_COLOR_WHITE "2. AI mode\n" COLOR_RESET); 
    printf(BOLD_COLOR_WHITE "Select the game mode: " COLOR_RESET); 
  }
  getchar();

  system("clear");

  printf(BOLD_COLOR_WHITE "Enter the number of columns: " COLOR_RESET);  
  while (scanf("%d", &M) == 0) {
    int c;
    while((c=getchar())!='\n' && c!=EOF); //Clear the stdin
    printf("Invalid input. Try again\n");
    printf(BOLD_COLOR_WHITE "Enter the number of columns: " COLOR_RESET);
  }
  getchar();
  
  printf(BOLD_COLOR_WHITE "Enter the number of rows: " COLOR_RESET);
  while (scanf("%d", &N) == 0) {
    int c;
    while((c=getchar())!='\n' && c!=EOF); //Clear the stdin
    printf("Invalid input. Try again\n");
    printf(BOLD_COLOR_WHITE "Enter the number of rows: " COLOR_RESET);
  }
  getchar();
  
  system("clear");

  if (game_mode == 1) labyrinth_interactive_mode_run(M, N);
  else labyrinth_AI_mode_run(M, N);

  return 0;
}
