/**
 * @file main.c
 * @author Mattia Forlin, Matteo Toffoli
 * @brief Project's main file.
 * @date 2023-02-03
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
  int M = 0, N = 0;
  
  printf("Enter the number of columns: ");
  scanf("%d", &M);
  getchar();
  printf("Enter the number of rows: ");
  scanf("%d", &N);
  getchar();
  labyrinth_run(M, N);
  return 0;
}
