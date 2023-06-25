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
#include <stdbool.h>

/**
 * @struct snake
 * @brief Represents the snake.
 */
typedef struct snake snake_t;

/**
 * @struct labyrinth
 * @brief Represents the labyrinth.
 */
typedef struct labyrinth labyrinth_t;

/**
 * @fn void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s)
 * @brief Initializes the data structures.
 *
 * @param l Pointer to the labyrinth_t structure to initialize.
 * @param M The width of the labyrinth.
 * @param N The height of the labyrinth.
 * @param s Pointer to the snake_t structure representing the snake.
 */
void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s);

/**
 * @fn void labyrinth_free (labyrinth_t *l, snake_t *s)
 * @brief Frees the occupied memory for the labyrinth and snake structures.
 *
 * @param l Pointer to the labyrinth_t structure to free.
 * @param s Pointer to the snake_t structure to free.
 */
void labyrinth_free (labyrinth_t *l, snake_t *s);

/**
 * @fn void labyrinth_print (labyrinth_t *l, snake_t *s)
 * @brief Prints the current state of the labyrinth game.
 *
 * @param l Pointer to the labyrinth_t structure.
 * @param s Pointer to the snake_t structure representing the snake.
 */
void labyrinth_print (labyrinth_t *l, snake_t *s);

/**
 * @fn void find_initial_position (labyrinth_t *l, int *x, int *y)
 * @brief Finds the initial position of the snake in the labyrinth.
 *
 * @param l Pointer to the labyrinth_t structure.
 * @param x Pointer to store the X-coordinate of the initial position.
 * @param y Pointer to store the Y-coordinate of the initial position.
 */
void find_initial_position (labyrinth_t *l, int *x, int *y);

/**
 * @fn void moves_input (char *move, char *moves, int *row, int *col, int *score, snake_t *head, labyrinth_t *l, int mode)
 * @brief Handles user input for moves and updates the game state accordingly.
 *
 * @param move Pointer to save the current move entered.
 * @param moves Pointer to save the total number of moves.
 * @param row Pointer to the current row of the labyrinth.
 * @param col Pointer to the current column of the labyrinth.
 * @param score Pointer to store the game's score.
 * @param head Pointer to the snake's head.
 * @param l Pointer to the labyrinth.
 * @param mode The mode of the game (1 for interactive, 0 default value (indicates the AI mode)).
 */
void moves_input (char *move, char *moves, int *row, int *col, int *score, snake_t *head, labyrinth_t *l, int mode);

/**
 * @fn void obstacles_borders_check (labyrinth_t *l, snake_t *head, int *row, int *col)
 * @brief Checks for obstacles, borders and bjects to collect and handles collisions. 
 *
 * @param l Pointer to the labyrinth.
 * @param head Pointer to the snake's head.
 * @param row Pointer to the current row position.
 * @param col Pointer to the current column position.
 */
void obstacles_borders_check (labyrinth_t *l, snake_t *head, int *row, int *col);

/**
 * @fn void add_tail (snake_t *head)
 * @brief Adds a new tail segment to the snake.
 *
 * @param head Pointer to the snake's head.
 */
void add_tail (snake_t *head); 

/**
 * @fn void check_dead_ends (labyrinth_t *l, snake_t *head)
 * @brief Checks for dead ends and moves the snake accordingly.
 *
 * @param l Pointer to the labyrinth.
 * @param head Pointer to the snake's head.
 */
void check_dead_ends (labyrinth_t *l, snake_t *head); 

/**
 * @fn void labyrinth_interactive_mode_run (int M, int N)
 * @brief Runs the labyrinth game in interactive mode.
 *
 * @param M The width of the labyrinth.
 * @param N The height of the labyrinth.
 */
void labyrinth_interactive_mode_run (int M, int N);

<<<<<<< HEAD
/**
 * @fn int checkXWest(labyrinth_t* l, int row, int col)
 * @brief Checks if it's safe to move to the west.
 *
 * @param l Pointer to the labyrinth.
 * @param row The current row position.
 * @param col The current column position.
 * @return 1 if it's safe to move, 0 otherwise.
 */
int checkXWest(labyrinth_t* l, int row, int col);

/**
 * @fn int checkXEast(labyrinth_t* l, int row, int col)
 * @brief Checks if it's safe to move to the east.
 *
 * @param l Pointer to the labyrinth.
 * @param row The current row position.
 * @param col The current column position.
 * @return 1 if it's safe to move, 0 otherwise.
 */
int checkXEast(labyrinth_t* l, int row, int col);

/**
 * @fn int checkYNorth(labyrinth_t* l, int row, int col)
 * @brief Checks if it's safe to move to the north.
 *
 * @param l Pointer to the labyrinth.
 * @param row The current row position.
 * @param col The current column position.
 * @return 1 if it's safe to move, 0 otherwise.
 */
int checkYNorth(labyrinth_t* l, int row, int col);

/**
 * @fn int checkYSouth(labyrinth_t* l, int row, int col)
 * @brief Checks if it's safe to move to the south.
 *
 * @param l Pointer to the labyrinth.
 * @param row The current row position.
 * @param col The current column position.
 * @return 1 if it's safe to move, 0 otherwise.
 */
int checkYSouth(labyrinth_t* l, int row, int col);

/**
 * @fn void labyrinth_AI_mode_run (int M, int N)
 * @brief Runs the labyrinth game in AI mode.
 *
 * @param M The width of the labyrinth.
 * @param N The height of the labyrinth.
 */
void labyrinth_AI_mode_run (int M, int N);

=======
>>>>>>> 1624ea31bd9a26a92ec598deea45db837e111bc9
#endif
