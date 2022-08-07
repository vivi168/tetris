#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "renderer.h"

#define TILE_SIZE 48
#define FPS 144
#define TICKS_PER_FRAME (1000 / FPS)

#define BORDER_WIDTH 4
#define INNER_OFFSET (BORDER_WIDTH / 2)

SDL_Window* sdl_window;
SDL_Renderer* sdl_renderer;

void create_window();
void render_level(const Level*);
void render_current_tetromino(const Tetromino*);
void render_square(int x, int y, int c);

// TODO: define better colors
// Draw square borders, or better yet, textured square ?
static const SDL_Color Colors[8] = {
    { 0x9E, 0x9E, 0x9E }, //   WALL gray    #9E9E9E
    { 0x00, 0xBC, 0xD4 }, // I_MINO cyan    #00BCD4
    { 0xFF, 0xEB, 0x3B }, // O_MINO yellow  #FFEB3B
    { 0x3F, 0x51, 0xB5 }, // J_MINO blue    #3F51B5
    { 0xFF, 0x98, 0x00 }, // L_MINO orange  #FF9800
    { 0x4C, 0xAF, 0x50 }, // S_MINO green   #4CAF50
    { 0x9C, 0x27, 0xB0 }, // T_MINO magenta #9C27B0
    { 0xF4, 0x43, 0x36 }, // Z_MINO red     #F44336
};

static const SDL_Color BorderColors[8] = {
    { 0x42, 0x42, 0x42 }, //   WALL gray    #424242
    { 0x00, 0x60, 0x64 }, // I_MINO cyan    #006064
    { 0xF5, 0x7F, 0x17 }, // O_MINO yellow  #F57F17
    { 0x1A, 0x23, 0x7E }, // J_MINO blue    #1A237E
    { 0xE6, 0x51, 0x00 }, // L_MINO orange  #E65100
    { 0x1B, 0x5E, 0x20 }, // S_MINO green   #1B5E20
    { 0x4A, 0x14, 0x8C }, // T_MINO magenta #4A148C
    { 0xB7, 0x1C, 0x1C }, // Z_MINO red     #B71C1C
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
    int inner_size = TILE_SIZE - BORDER_WIDTH;

    // Outer
    SDL_Rect dst = { TILE_SIZE * x + hoff,
                     TILE_SIZE * y + voff,
                     TILE_SIZE, TILE_SIZE };

    SDL_Color color = BorderColors[c - 1];

    SDL_SetRenderDrawColor(sdl_renderer, 
        color.r, color.g, color.b,
        SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(sdl_renderer, &dst);

    // Inner
    dst = (SDL_Rect){ TILE_SIZE * x + hoff + INNER_OFFSET,
                      TILE_SIZE * y + voff + INNER_OFFSET,
                      inner_size, inner_size };

    color = Colors[c - 1];
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
