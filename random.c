#include "random.h"

static uint32_t next;

uint32_t rng_seed(uint32_t s)
{
    uint32_t prev = next;
    next = s;

    return prev;
}

uint32_t rng_rand32()
{
    next = (1103515245 * next + 12345) % 0x80000000;
    return next;
}

uint16_t rng_rand16()
{
    return rng_rand32() >> 16;
}

uint16_t rng_randint(uint16_t min, uint16_t max)
{
    return rng_rand16() % (max - min + 1) + min;
}
