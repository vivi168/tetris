#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "level.h"

static const uint8_t INITIAL_BOARD[LVL_H][LVL_W] = {
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
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

//int add_tetromino(Level* level, Tetromino* tetromino)
//{
//	uint8_t data[4][4];
//
//	tetromino_data(tetromino, data);
//
//	size_t x = tetromino->x;
//	size_t y = tetromino->y;
//
//	printf("issou\n");
//	for (size_t i = 0; i < MINO_SIZ; i++) {
//		for (size_t j = 0; j < MINO_SIZ; j++) {
//
//			// here check not out of bound
//			level->board[i + y][j + x] = data[i][j];
//		}
//	}
//
//	return 0;
//}