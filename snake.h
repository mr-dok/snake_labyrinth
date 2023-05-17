/**
 * @file snake.h
 * @author Mattia Forlin, Matteo Toffoli
 * @brief Project's header file.
 * @date 2023-04-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef snake_h 
#define snake_h

/**
 * @brief Data structure to represent the snake.
 */
typedef struct snake snake_t;

/**
 * @brief Data structure to represent the labyrinth.
 */
typedef struct labyrinth labyrinth_t;

/**
 * @brief Function to initialize the data structures.
 *
 * @param l Data structure of labyrinth type.
 * @param M Number of labyrinth columns.
 * @param N Number of labyrinth rows.
 * @param s Data structure of snake type.
 */
void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s);

/**
 * @brief Function to free the occupied memory.
 *
 * @param l Data structure of labyrinth type.
 * @param s Data structure of snake type.
 */
void labyrinth_free (labyrinth_t *l, snake_t *s);

/**
 * @brief Function to print the labyrinth
 *
 * @param l Data structure of labyrinth type.
 * @param M Number of labyrinth columns.
 * @param N Number of labyrinth rows.
 * @param s Data structure of snake type.
 */
void labyrinth_print (labyrinth_t *l, int M, int N, snake_t *s);

/**
 * @brief Function to find the initial position of the snake.
 *
 * @param l Data structure of labyrinth type.
 * @param x Pointer variable to the x axis of the labyrinth.
 * @param y Pointer variable to the y axis of the labyrinth.
 */
void find_initial_position (labyrinth_t *l, int *x, int *y);

/**
 * @brief Function to receive input from the user and change the position of the snake. 
 *
 * @param move Pointer variable to save the current move entered.
 * @param moves Char array to save the total number of moves.
 * @param row Pointer variable to the row of the labyrinth.
 * @param col Pointer variable to the column of the labyrinth.
 * @param score Variable for storing the game's score.
 * @param s Data structure of snake type.
 */

void moves_input (char *move, char *moves, int *row, int *col, int *score, snake_t *s, labyrinth_t *l);

/**
 * @brief Function to receive input from the user and change the position of the snake. 
 *
 * @param l Data structure of labyrinth type.
 * @param row Pointer variable to the row of the labyrinth.
 * @param col Pointer variable to the column of the labyrinth.
 * @param N Number of labyrinth rows.
 * @param M Number of labyrinth columns.
 */

void obstacles_borders_check (labyrinth_t *l, snake_t *head, int *row, int *col, int *N, int *M);

/**
 * @brief Main function for interactive mode.
 *
 * @param M Number of labyrinth columns.
 * @param N Number of labyrinth rows.
 */
void labyrinth_interactive_mode_run (int M, int N);

#endif
