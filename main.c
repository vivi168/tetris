#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "level.h"
#include "renderer.h"
#include "tetromino.h"
#include "random.h"

int quit;
Level level;

#define MOVE_SPEED 100
#define ACCEL_FALL_SPEED 75

uint32_t last_moved;
int fall_speed;

void process_input(uint32_t frame_start)
{
	if (inpmgr_quit_requested() || inpmgr_is_pressed(KEY_TRIANGLE)) {
		printf("[INFO]: quit requested\n");
		quit = TRUE;
	}

	if (inpmgr_is_held(KEY_DOWN)) {
		fall_speed = ACCEL_FALL_SPEED;
	}
	else {
		fall_speed = level.speed;
	}

	if (inpmgr_is_pressed(KEY_CIRCLE) || inpmgr_is_pressed(KEY_UP)) {
		tetromino_rotate(level.current_tetromino, &level, CLOCKWISE);
	}
	else if (inpmgr_is_pressed(KEY_CROSS)) {
		tetromino_rotate(level.current_tetromino, &level, COUNTER_CLOCKWISE);
	}

	if (inpmgr_is_pressed(KEY_LEFT)) {
		lvl_move_current(&level, -1, 0);
		last_moved = frame_start;
	}
	else if (inpmgr_is_pressed(KEY_RIGHT)) {
		lvl_move_current(&level, 1, 0);
		last_moved = frame_start;
	}

	if (inpmgr_is_held(KEY_LEFT) && (frame_start > last_moved + MOVE_SPEED)) {
		lvl_move_current(&level, -1, 0);
		last_moved = frame_start;
	}
	else if (inpmgr_is_held(KEY_RIGHT) && (frame_start > last_moved + MOVE_SPEED)) {
		lvl_move_current(&level, 1, 0);
		last_moved = frame_start;
	}
}

void mainloop()
{
	uint32_t frame_start;
	uint32_t last_fall_tick;
	Tetromino mino;
	Tetromino next_mino;

	uint16_t next = rng_randint(0, 6);

	tetromino_spawn(&mino, next, &level);

	level.current_tetromino = &mino;

	quit = 0;
	last_fall_tick = 0;
	last_moved = 0;

	fall_speed = level.speed;

	while (!quit) {
		frame_start = rdr_getticks();

		inpmgr_poll_events();
		process_input(frame_start);

		if (frame_start > last_fall_tick + fall_speed) {
			if (lvl_move_current(&level, 0, 1)) {
				lvl_add_tetromino(&level);

				next = rng_randint(0, 6);
				if (tetromino_spawn(&mino, next, &level) > 0) {
					quit = 1;
				}

				level.current_tetromino = &mino;
			}
			else {
				level.score++;
			}

			lvl_flag_lines(&level);

			last_fall_tick = frame_start;
		}

		rdr_render(&level);

		rdr_delay(frame_start);
	}
}

int main(int argc, char** argv)
{
	printf("Tetris\n");

	rng_seed(1);

	rdr_init();
	inpmgr_init();

	lvl_init(&level);

	mainloop();

	rdr_cleanup();

	return 0;
}