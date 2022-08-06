#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include <SDL.h>

#include "level.h"

void rdr_init();
void rdr_render(const Level*);
void rdr_cleanup();

uint32_t rdr_getticks();
void rdr_delay();

#endif
