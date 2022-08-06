#ifndef _RANDOM_H
#define _RANDOM_H

#include <stdint.h>

uint32_t rng_seed(uint32_t);
uint32_t rng_rand32();
uint16_t rng_rand16();
uint16_t rng_randint(uint16_t, uint16_t);

#endif
