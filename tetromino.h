#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>

#define MINO_DEF_N 7
#define MINO_DEF_SIZ 2

#define I_MINO 0
#define O_MINO 1
#define J_MINO 2
#define L_MINO 3
#define S_MINO 4
#define T_MINO 5
#define Z_MINO 6

#define MINO_N 19
#define MINO_SIZ 4

typedef struct tetromino_t {
	//uint8_t shape[4][4];
	size_t type;
	size_t rotation;
	size_t x, y;
} Tetromino;

typedef struct level_t Level;

int tetromino_set(Tetromino* t, size_t type, const Level* l);
int tetromino_rotate(Tetromino* t, const Level* l);

int tetromino_fits(const Tetromino* t, const Level* l);
void tetromino_data(const Tetromino* t, uint8_t** data);

void print_tetromino(const Tetromino* t);

#endif