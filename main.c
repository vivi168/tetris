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

	lvl_init(&level);
	print_board(&level);

	tetromino_set(&mino, S_MINO, &level);
	print_tetromino(&mino);
	tetromino_rotate(&mino, &level);
	print_tetromino(&mino);
	tetromino_rotate(&mino, &level);
	print_tetromino(&mino);
	tetromino_rotate(&mino, &level);
	print_tetromino(&mino);


	//add_tetromino(&level, &mino);

	print_board(&level);

	return 0;
}