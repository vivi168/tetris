#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "level.h"
#include "renderer.h"
#include "tetromino.h"

int main(int argc, char** argv)
{
	Level level;
	Tetromino mino;

	printf("Tetris\n");

	tetromino_set(&mino, S_MINO, 2);
	print_tetromino(&mino);
	tetromino_rotate(&mino);
	print_tetromino(&mino);
	tetromino_rotate(&mino);
	print_tetromino(&mino);
	tetromino_rotate(&mino);
	print_tetromino(&mino);

	add_tetromino(&level, &mino);

	lvl_init(&level);
	print_board(&level);

	return 0;
}