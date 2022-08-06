#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "level.h"
#include "renderer.h"
#include "tetromino.h"

int quit;
Level level;

// should be level props -> level.difficulty
#define FALL_SPEED 500

void process_input()
{
    if (iptm_quit_requested() || iptm_is_pressed(KEY_QUIT)) {
        printf("[INFO]: quit requested\n");
        quit = TRUE;
    }

	if (iptm_is_pressed(KEY_DOWN)) {
		tetromino_rotate(level.current_tetromino, &level);
	}
	else if (iptm_is_pressed(KEY_LEFT)) {
		lvl_move_current(&level, -1, 0);
	}
	else if (iptm_is_pressed(KEY_RIGHT)) {
		lvl_move_current(&level, 1, 0);
	}
}

void mainloop()
{
	uint32_t frame_start;
	uint32_t last_fall_tick;
	Tetromino mino;
	Tetromino next_mino;

	tetromino_spawn(&mino, J_MINO, &level);

	level.current_tetromino = &mino;

	quit = 0;
	last_fall_tick = 0;

	while (!quit) {
		frame_start = rdr_getticks();

		iptm_poll_events();
		process_input();

		if (frame_start > last_fall_tick + FALL_SPEED) {
			if (lvl_move_current(&level, 0, 1)) {
				lvl_add_tetromino(&level);
				tetromino_spawn(&mino, J_MINO, &level);
				level.current_tetromino = &mino;
			}

			last_fall_tick = frame_start;
		}

		rdr_render(&level);

		rdr_delay(frame_start);
	}
}

int main(int argc, char** argv)
{
	printf("Tetris\n");

	rdr_init();
	iptm_init();

	lvl_init(&level);

	mainloop();

	rdr_cleanup();

	return 0;
}