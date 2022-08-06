#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>

#include "tetromino.h"

#define LVL_W 16
#define LVL_H 23

typedef struct level_t {
	uint8_t board[LVL_H][LVL_W];
	Tetromino* current_tetromino;
	Tetromino* next_tetromino;
} Level;

void lvl_init(Level*);
void lvl_reset(Level*);

int lvl_add_tetromino(Level*);

void print_board(Level*);

#endif