#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "level.h"

static const uint8_t INITIAL_BOARD[LVL_H][LVL_W] = {
	// spawn area
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	// playing field
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	// padding
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void lvl_init(Level* level)
{
	lvl_reset(level);
}

void lvl_reset(Level* level)
{
	memcpy(level->board, INITIAL_BOARD, LVL_H * LVL_W);
}

void print_board(Level* level)
{
	for (size_t i = 0; i < LVL_H; i++) {
		for (size_t j = 0; j < LVL_W; j++) {
			printf("%d ", level->board[i][j]);
		}
		printf("\n");
	}
}

int lvl_move_current(const Level* l, int x, int y)
{
	int fits;
	size_t prev_x = l->current_tetromino->x;
	size_t prev_y = l->current_tetromino->y;

	l->current_tetromino->x += x;
	l->current_tetromino->y += y;

	fits = tetromino_fits(l->current_tetromino, l);

	if (fits > 0) {
		l->current_tetromino->x = prev_x;
		l->current_tetromino->y = prev_y;
	}

	printf("%d, %d\n",
		l->current_tetromino->x,
		l->current_tetromino->y
	);

	return fits;
}

int lvl_add_tetromino(Level* level)
{
	uint8_t data[4][4];

	tetromino_data(level->current_tetromino, data);

	size_t x = level->current_tetromino->x;
	size_t y = level->current_tetromino->y;

	printf("issou\n");
	for (size_t i = 0; i < MINO_SIZ; i++) {
		for (size_t j = 0; j < MINO_SIZ; j++) {

			if (data[i][j] > 0)
				level->board[i + y][j + x] = data[i][j];
		}
	}

	return 0;
}