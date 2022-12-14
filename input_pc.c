#include <SDL.h>

#include "input.h"

InputManager input_manager;

void inpmgr_update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            input_manager.quit = TRUE;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    input_manager.new_keystate |= (1 << KEY_UP);
                    break;
                case SDLK_RIGHT:
                    input_manager.new_keystate |= (1 << KEY_RIGHT);
                    break;
                case SDLK_DOWN:
                    input_manager.new_keystate |= (1 << KEY_DOWN);
                    break;
                case SDLK_LEFT:
                    input_manager.new_keystate |= (1 << KEY_LEFT);
                    break;
                case SDLK_w:
                    input_manager.new_keystate |= (1 << KEY_TRIANGLE);
                    break;
                case SDLK_a:
                    input_manager.new_keystate |= (1 << KEY_SQUARE);
                    break;
                case SDLK_s:
                    input_manager.new_keystate |= (1 << KEY_CROSS);
                    break;
                case SDLK_d:
                    input_manager.new_keystate |= (1 << KEY_CIRCLE);
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
                case SDLK_UP:
                    input_manager.new_keystate &= ~(1 << KEY_UP);
                    break;
                case SDLK_RIGHT:
                    input_manager.new_keystate &= ~(1 << KEY_RIGHT);
                    break;
                case SDLK_DOWN:
                    input_manager.new_keystate &= ~(1 << KEY_DOWN);
                    break;
                case SDLK_LEFT:
                    input_manager.new_keystate &= ~(1 << KEY_LEFT);
                    break;
                case SDLK_w:
                    input_manager.new_keystate &= ~(1 << KEY_TRIANGLE);
                    break;
                case SDLK_a:
                    input_manager.new_keystate &= ~(1 << KEY_SQUARE);
                    break;
                case SDLK_s:
                    input_manager.new_keystate &= ~(1 << KEY_CROSS);
                    break;
                case SDLK_d:
                    input_manager.new_keystate &= ~(1 << KEY_CIRCLE);
                    break;
            }
            break;
        default:
            break;
        }
    }

    input_manager.keys_released = (input_manager.old_keystate ^ input_manager.new_keystate) ^ input_manager.new_keystate;
    input_manager.keys_pressed =  (input_manager.old_keystate ^ input_manager.new_keystate) & input_manager.new_keystate;
    input_manager.keys_held = input_manager.old_keystate & input_manager.new_keystate;

    input_manager.old_keystate = input_manager.new_keystate;
}

void inpmgr_init()
{
    input_manager.quit = FALSE;
    input_manager.new_keystate = 0;
    input_manager.old_keystate = 0;
}

void inpmgr_poll_events()
{
    inpmgr_update();
}

int inpmgr_quit_requested() {
    return input_manager.quit;
}

int inpmgr_is_held(int k) {
    return (1 << k) & input_manager.keys_held;
}

int inpmgr_is_pressed(int k) {
    return (1 << k) & input_manager.keys_pressed;
}

int inpmgr_is_released(int k) {
    return (1 << k) & input_manager.keys_released;
}
