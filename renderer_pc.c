#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "renderer.h"

#define TILE_SIZE 48
#define FPS 144
#define TICKS_PER_FRAME (1000 / FPS)

SDL_Window* sdl_window;
SDL_Renderer* sdl_renderer;

void create_window();
void render_level(Level*);

void rdr_init()
{
    printf("init\n");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Unable to init SDL\n");
        exit(EXIT_FAILURE);
    }

    create_window();
}

void create_window()
{
    printf("create window\n");

    const char* title = "Sokoban";
    const int width = LVL_W * TILE_SIZE;
    const int height = LVL_H * TILE_SIZE;

    sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (sdl_window == NULL) {
        fprintf(stderr, "Error while create SDL_Window\n");
        exit(EXIT_FAILURE);
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

    if (sdl_renderer == NULL) {
        fprintf(stderr, "Error while creating SDL_Renderer\n");
        exit(EXIT_FAILURE);
    }
}

void rdr_render(Level* level)
{
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(sdl_renderer);

    render_level(level);

    SDL_RenderPresent(sdl_renderer);
}

void render_level(Level* level)
{
    
}

void rdr_cleanup()
{
    printf("cleanup\n");

    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);

    SDL_Quit();
}

unsigned int rdr_getticks()
{
    return SDL_GetTicks();
}

void rdr_delay(int frame_start)
{
    unsigned int frame_time;

    frame_time = rdr_getticks() - frame_start;
    if (TICKS_PER_FRAME > frame_time) {
        SDL_Delay(TICKS_PER_FRAME - frame_time);
    }
}
