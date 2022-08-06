#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>

#include "tetromino.h"

#define LVL_W 12
#define LVL_H 18

typedef struct tetromino_t {
	uint8_t shape[4][4];
	size_t x, y;
} Tetromino;


typedef struct level_t {
	uint8_t board[LVL_H][LVL_W];
	Tetromino* next_minos;
} Level;

void lvl_init(Level*);
void lvl_reset(Level*);

void print_board(Level*);

#endif