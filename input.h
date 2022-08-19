#ifndef INPUT_H
#define INPUT_H

#define TRUE 1
#define FALSE 0

// keep aligned with PSX PAD specs
#define KEY_UP        4
#define KEY_RIGHT     5
#define KEY_DOWN      6
#define KEY_LEFT      7
#define KEY_TRIANGLE 12
#define KEY_CIRCLE   13
#define KEY_CROSS    14
#define KEY_SQUARE   15

typedef struct input_manager_t {
    int quit;
    unsigned int new_keystate, old_keystate;
    unsigned int keys_pressed, keys_held, keys_released;
} InputManager;

void inpmgr_init();
void inpmgr_update();
void inpmgr_poll_events();
int inpmgr_quit_requested();
int inpmgr_is_held(int);
int inpmgr_is_pressed(int);
int inpmgr_is_released(int);

#endif
