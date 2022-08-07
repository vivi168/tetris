#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tetromino.h"
#include "level.h"

static const uint8_t TETROMINOS_DEF[MINO_DEF_N][MINO_DEF_SIZ] =
{
	// offset, rotation count
	{ 0, 2 },
	{ 2, 1 },
	{ 3, 4 },
	{ 7, 4 },
	{ 11, 2 },
	{ 13, 4 },
	{ 17, 2 }
};

static const uint8_t TETROMINOS[MINO_N][MINO_SIZ][MINO_SIZ] =
{
	// I_MINO
	{
		{0, 0, 0 ,0},
		{0, 0, 0 ,0},
		{2, 2, 2 ,2},
		{0, 0, 0 ,0},
	},
	{
		{0, 2, 0 ,0},
		{0, 2, 0 ,0},
		{0, 2, 0 ,0},
		{0, 2, 0 ,0},
	},
	// O_MINO
	{
		{0, 0, 0 ,0},
		{0, 3, 3 ,0},
		{0, 3, 3 ,0},
		{0, 0, 0 ,0}
	},
	// J_MINO
	{
		{0, 0, 0, 0},
		{4, 4, 4, 0},
		{0, 0, 4, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 4, 0, 0},
		{0, 4, 0, 0},
		{4, 4, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{4, 0, 0, 0},
		{4, 4, 4, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 4, 4, 0},
		{0, 4, 0, 0},
		{0, 4, 0, 0},
		{0, 0, 0 ,0}
	},
	// L_MINO
	{
		{0, 0, 0, 0},
		{5, 5, 5, 0},
		{5, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{5, 5, 0, 0},
		{0, 5, 0, 0},
		{0, 5, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 0, 5, 0},
		{5, 5, 5, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 5, 0, 0},
		{0, 5, 0, 0},
		{0, 5, 5, 0},
		{0, 0, 0 ,0}
	},
	// S_MINO
	{
		{0, 0, 0, 0},
		{0, 6, 6, 0},
		{6, 6, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{6, 0, 0, 0},
		{6, 6, 0, 0},
		{0, 6, 0, 0},
		{0, 0, 0 ,0}
	},
	// T_MINO
	{
		{0, 0, 0, 0},
		{7, 7, 7, 0},
		{0, 7, 0, 0},
		{0, 0, 0 ,0}
	},

	{
		{0, 7, 0, 0},
		{7, 7, 0, 0},
		{0, 7, 0, 0},
		{0, 0, 0 ,0}
	},

	{
		{0, 7, 0, 0},
		{7, 7, 7, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 7, 0, 0},
		{0, 7, 7, 0},
		{0, 7, 0, 0},
		{0, 0, 0 ,0}
	},
	// Z_MINO
	{
		{0, 0, 0, 0},
		{8, 8, 0, 0},
		{0, 8, 8, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 8, 0, 0},
		{8, 8, 0, 0},
		{8, 0, 0, 0},
		{0, 0, 0 ,0}
	}
};

#define TETROMINO_OFFSET(type) ((TETROMINOS_DEF)[type][0])
#define TETROMINO_ROTATION(type) ((TETROMINOS_DEF)[type][1])

#define START_X 6 // 4 + 2 (padding)

int tetromino_spawn(Tetromino* t, size_t type, const Level* l)
{
	size_t offset = TETROMINO_OFFSET(type);

	t->type = type;
	t->rotation = 0;

	t->x = START_X;
	t->y = 0;

	return tetromino_fits(t, l);
}

int tetromino_rotate(Tetromino* t, const Level* l)
{
	size_t offset = TETROMINO_OFFSET(t->type);
	size_t rotation_n = TETROMINO_ROTATION(t->type);
	int fits;
	
	size_t prev_rotation = t->rotation;

	t->rotation++;

	if (t->rotation >= rotation_n)
		t->rotation = 0;

	fits = tetromino_fits(t, l);

	if (fits > 0)
		t->rotation = prev_rotation;

	return fits;
}

int tetromino_fits(const Tetromino* t, const Level* l)
{
	uint8_t data[4][4];
	size_t x = t->x;
	size_t y = t->y;

	tetromino_data(t, data);

	for (size_t i = 0; i < MINO_SIZ; i++) {
		for (size_t j = 0; j < MINO_SIZ; j++) {
			if (data[i][j] > 0 && l->board[i + y][j + x] > 0) {
				return l->board[i + y][j + x];

			}
		}
	}
	
	return 0;
}

void tetromino_data(const Tetromino* t, uint8_t data[4][4])
{
	size_t offset = TETROMINO_OFFSET(t->type);

	memcpy(data, TETROMINOS[offset + t->rotation], MINO_SIZ * MINO_SIZ);
}

void print_tetromino(const Tetromino* t)
{
	size_t offset = TETROMINO_OFFSET(t->type);

	for (size_t i = 0; i < MINO_SIZ; i++) {
		for (size_t j = 0; j < MINO_SIZ; j++) {
			printf("%d ", TETROMINOS[offset + t->rotation][i][j]);
		}
		printf("\n");
	}
	printf("\n");
}