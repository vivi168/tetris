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
void render_level(const Level*);
void render_current_tetromino(const Tetromino*);
void render_square(int x, int y, int c);

static const SDL_Color Colors[8] = {
    { 0x33, 0x33, 0x33 },
    { 255, 0, 0, 1},
    { 0, 255, 0, 1},
    { 0, 0, 255, 1},
    { 255, 255, 0, 1},
    { 0, 255, 255, 1},
    { 128, 0, 128, 1},
    { 255, 0, 255, 1},
};

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

    const char* title = "Tetris";
    // TODO: True size is for board + next tetromino + score board
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

void rdr_render(const Level* level)
{
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(sdl_renderer);

    render_level(level);

    SDL_RenderPresent(sdl_renderer);
}

void render_level(const Level* level)
{
    for (size_t i = 0; i < LVL_H; i++) {
        for (size_t j = 0; j < LVL_W; j++) {
            if (level->board[i][j] > 0) {
                // TODO: don't draw padding/spawning area
                render_square(j, i, level->board[i][j]);
            }
        }
    }

    render_current_tetromino(level->current_tetromino);
}

void render_current_tetromino(const Tetromino* t)
{
    uint8_t data[4][4];

    tetromino_data(t, data);

    for (size_t i = 0; i < MINO_SIZ; i++) {
        for (size_t j = 0; j < MINO_SIZ; j++) {
            if (data[i][j] > 0) {
                render_square(j + t->x, i + t->y, data[i][j]);
            }
        }
    }
}

void render_square(int x, int y, int c)
{
    int hoff = 0; // offset level draw area on screen
    int voff = 0;

    SDL_Rect dst = { TILE_SIZE * x + hoff,
                     TILE_SIZE * y + voff,
                     TILE_SIZE, TILE_SIZE };

    SDL_Color color = Colors[c - 1];

    SDL_SetRenderDrawColor(sdl_renderer, 
        color.r, color.g, color.b,
        SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(sdl_renderer, &dst);
}

void rdr_cleanup()
{
    printf("cleanup\n");

    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);

    SDL_Quit();
}

uint32_t rdr_getticks()
{
    return SDL_GetTicks();
}

void rdr_delay(int frame_start)
{
    uint32_t frame_time;

    frame_time = rdr_getticks() - frame_start;
    if (TICKS_PER_FRAME > frame_time) {
        SDL_Delay(TICKS_PER_FRAME - frame_time);
    }
}
