#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "level.h"

#define PADDING_TOP 3
#define PADDING_BOT 2
#define PADDING_SIDE 3
#define LINE_LEN 10

#define SPEED_CEIL 1000
#define FALL_SPEED 300

static const uint8_t BLANK_LINE[LVL_W] = {
	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
};

static const uint8_t INITIAL_BOARD[LVL_H][LVL_W] = {
	// spawn area
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
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

int clear_lines(Level*, int, int);

void lvl_init(Level* level)
{
	level->score = 0;
	level->speed = FALL_SPEED;

	lvl_reset(level);
}

void lvl_reset(Level* level)
{
	memcpy(level->board, INITIAL_BOARD, LVL_H * LVL_W);
}

void print_board(const Level* level)
{
	for (size_t i = 0; i < LVL_H; i++) {
		for (size_t j = 0; j < LVL_W; j++) {
			printf("%3d ", level->board[i][j]);
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

	return fits;
}

int lvl_add_tetromino(Level* level)
{
	uint8_t data[4][4];

	tetromino_data(level->current_tetromino, data);

	size_t x = level->current_tetromino->x;
	size_t y = level->current_tetromino->y;

	for (size_t i = 0; i < MINO_SIZ; i++) {
		for (size_t j = 0; j < MINO_SIZ; j++) {

			if (data[i][j] > 0)
				level->board[i + y][j + x] = data[i][j];
		}
	}

	return 0;
}

int lvl_flag_lines(Level* level)
{
	int line_sum;
	int flagged = 0;
	int start = -1;

	for (size_t i = PADDING_TOP; i < LVL_H - PADDING_BOT; i++) {
		line_sum = 0;

		for (size_t j = PADDING_SIDE; j < LVL_W - PADDING_SIDE; j++) {
			if (level->board[i][j] > 0)
				line_sum++;
		}

		if (line_sum == LINE_LEN) {
			printf("LINE COMPLETED ! %zd\n", i);
			level->board[i][0] = -1;

			flagged++;
			if (start < 0) start = i;
		}
	}

	if (flagged > 0) {
		clear_lines(level, flagged, start);

		level->score += flagged * (SPEED_CEIL - level->speed);
		printf("score: %d\n", level->score);
	}

	return flagged;
}

int clear_lines(Level* level, int line_count, int start)
{
	int copy_count = LVL_W * start;

	memcpy(level->board[line_count], level->board[0], copy_count);

	// clear beginning of board
	for (size_t i = 0; i < line_count; i++) {
		memcpy(level->board[i], BLANK_LINE, LVL_W);
	}
}