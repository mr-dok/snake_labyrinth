#ifndef snake_h 
#define snake_h

typedef struct snake snake_t;

typedef struct labyrinth labyrinth_t;

void labyrinth_run (int M, int N);

void labyrinth_init (labyrinth_t *l, int M, int N, snake_t *s);

void labyrinth_print (labyrinth_t *l, int M, int N, snake_t *s);

void labyrinth_free (labyrinth_t *l, snake_t *s);

void find_initial_position (labyrinth_t *l, int *x, int *y);

#endif
