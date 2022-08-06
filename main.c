#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "level.h"
#include "renderer.h"

int main(int argc, char** argv)
{
	printf("Tetris\n");

	Level level;

	lvl_init(&level);

	print_board(&level);

	return 0;
}