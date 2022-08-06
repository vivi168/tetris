#include <stdlib.h>
#include <string.h>

#include "tetromino.h"

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
		{1, 1, 1 ,1},
		{0, 0, 0 ,0},
	},
	{
		{0, 1, 0 ,0},
		{0, 1, 0 ,0},
		{0, 1, 0 ,0},
		{0, 1, 0 ,0},
	},
	// O_MINO
	{
		{0, 0, 0 ,0},
		{0, 1, 1 ,0},
		{0, 1, 1 ,0},
		{0, 0, 0 ,0}
	},
	// J_MINO
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{1, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	// L_MINO
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{1, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0 ,0}
	},
	// S_MINO
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{1, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	// T_MINO
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},

	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},

	{
		{0, 1, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0},
		{0, 0, 0 ,0}
	},
	// Z_MINO
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0 ,0}
	},
	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 0, 0 ,0}
	}
};

#define TETROMINO_OFFSET(type) ((TETROMINOS_DEF)[type][0])
#define TETROMINO_ROTATION(type) ((TETROMINOS_DEF)[type][1])

void tetromino_set(Tetromino* t, size_t type, size_t rot)
{
	size_t offset = TETROMINO_OFFSET(type);
	size_t rotation = TETROMINO_ROTATION(type);

	if (rot >= rotation)
		rot = 0;

	t->type = type;
	t->rotation = rot;

	t->x = 0;
	t->y = 0;
}

void tetromino_rotate(Tetromino* t)
{
	size_t offset = TETROMINO_OFFSET(t->type);
	size_t rotation_n = TETROMINO_ROTATION(t->type);

	t->rotation++;

	if (t->rotation >= rotation_n)
		t->rotation = 0;
}

uint8_t** tetromino_data(Tetromino* t, uint8_t** data)
{
	size_t offset = TETROMINO_OFFSET(t->type);
	
	memcpy(data, TETROMINOS[offset + t->rotation], MINO_SIZ * MINO_SIZ);
	
	return data;
}

void print_tetromino(Tetromino* t)
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