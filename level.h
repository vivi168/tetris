#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>

#include "tetromino.h"

#define LVL_W 12
#define LVL_H 18

typedef struct level_t {
	uint8_t board[LVL_H][LVL_W];
	Tetromino* next_minos;
} Level;

void lvl_init(Level*);
void lvl_reset(Level*);

//int add_tetromino(Level*, const Tetromino*);

void print_board(Level*);

#endif