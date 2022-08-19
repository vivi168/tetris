#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>

#define MINO_DEF_N 7
#define MINO_DEF_SIZ 2

typedef enum mino_type_t {
	I_MINO = 0,
	O_MINO,
	J_MINO,
	L_MINO,
	S_MINO,
	T_MINO,
	Z_MINO,
} MinoType;

#define MINO_N 19
#define MINO_SIZ 4

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE (-1)

#define DIR_DOWN 1
#define DIR_LEFT (-1)
#define DIR_RIGHT 1

typedef struct tetromino_t {
	int type;
	int rotation;
	int x, y;
} Tetromino;

typedef struct level_t Level;

int tetromino_spawn(Tetromino* t, int type, const Level* l);
int tetromino_rotate(Tetromino* t, const Level* l, int direction);

int tetromino_fits(const Tetromino* t, const Level* l);
void tetromino_data(const Tetromino* t, uint8_t data[4][4]);

void print_tetromino(const Tetromino* t);

#endif