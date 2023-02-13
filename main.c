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

int main(void) {
  printf("Enter ");
  scanf("");


  int M = 0, N = 0;
  
  scanf("%d", &M);
  scanf("%d", &N);
   
  for (int i = 0; i < N; i++) {
    char *s = (char *) malloc(M + 1);
    scanf("%[^\n]s", s);
    sleep(1);    
    printf("%s\n", s);
  }
  return 0;
}
