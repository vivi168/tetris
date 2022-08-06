#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>

#define MINO_S 4

#define IMINO_N 2
#define OMINO_N 1
#define JMINO_N 4
#define LMINO_N 4
#define SMINO_N 2
#define TMINO_N 5
#define ZMINO_N 2

extern const uint8_t I_mino[IMINO_N][4][4];
extern const uint8_t O_Mino[OMINO_N][4][4];
extern const uint8_t J_Mino[JMINO_N][4][4];
extern const uint8_t L_Mino[LMINO_N][4][4];
extern const uint8_t S_Mino[SMINO_N][4][4];
extern const uint8_t T_Mino[TMINO_N][4][4];
extern const uint8_t Z_Mino[ZMINO_N][4][4];

#endif