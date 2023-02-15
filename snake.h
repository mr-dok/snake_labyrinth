#ifndef snake_h 
#define snake_h

typedef struct snake snake_t;

typedef struct labyrinth labyrinth_t;

void labyrinth_run(int M, int N);

void labyrinth_init (labyrinth_t *l, int M, int N);

#endif
