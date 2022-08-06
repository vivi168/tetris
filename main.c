#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "level.h"
#include "renderer.h"
#include "tetromino.h"

int quit;
Level level;

void process_input()
{
    if (iptm_quit_requested() || iptm_is_pressed(KEY_QUIT)) {
        printf("[INFO]: quit requested\n");
        quit = TRUE;
    }
}

void mainloop()
{
	uint32_t frame_start;
	quit = 0;

	while (!quit) {
		frame_start = rdr_getticks();

		iptm_poll_events();
		process_input();

		rdr_render(&level);

		rdr_delay(frame_start);
	}
}



int main(int argc, char** argv)
{
	Tetromino mino;

	printf("Tetris\n");

	rdr_init();
	iptm_init();

	lvl_init(&level);

	tetromino_spawn(&mino, I_MINO, &level);

	level.current_tetromino = &mino;

	mino.x -= 1;
	mino.y += 1;

	mainloop();

	rdr_cleanup();

	return 0;
}