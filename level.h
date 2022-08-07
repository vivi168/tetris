#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>

#include "tetromino.h"

#define LVL_W 16
#define LVL_H 23

typedef struct level_t {
	int8_t board[LVL_H][LVL_W];
	uint32_t score;
	uint32_t speed;

	Tetromino* current_tetromino;
	Tetromino* next_tetromino;
} Level;

void lvl_init(Level*);
void lvl_reset(Level*);

int lvl_move_current(const Level*, int, int);
int lvl_add_tetromino(Level*);

int lvl_flag_lines(Level*);

void print_board(const Level*);

#endif