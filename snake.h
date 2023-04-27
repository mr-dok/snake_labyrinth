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
 * @brief Main function for interactive mode.
 *
 * @param M Number of labyrinth columns.
 * @param N Number of labyrinth rows.
 */
void labyrinth_run (int M, int N);

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
 * @brief Function to print the labyrinth
 *
 * @param l Data structure of labyrinth type.
 * @param M Number of labyrinth columns.
 * @param N Number of labyrinth rows.
 * @param s Data structure of snake type.
 */
void labyrinth_print (labyrinth_t *l, int M, int N, snake_t *s);

/**
 * @brief Function to free the occupied memory.
 *
 * @param l Data structure of labyrinth type.
 * @param s Data structure of snake type.
 */
void labyrinth_free (labyrinth_t *l, snake_t *s);

/**
 * @brief Function to find the initial position of the snake.
 *
 * @param l Data structure of labyrinth type.
 * @param x Pointer variable to the x axis of the labyrinth.
 * @param y Pointer variable to the y axis of the labyrinth.
 */
void find_initial_position (labyrinth_t *l, int *x, int *y);

#endif
