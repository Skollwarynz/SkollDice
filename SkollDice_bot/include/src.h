#ifndef SRC_H
#define SRC_H

#include <stdio.h>
#include <stdint.h>
#include "discord.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

// Definition of dices types
typedef enum {
  D4 = 4,
  D6 = 6,
  D8 = 8,
  D10 = 10,
  D12 = 12,
  D20 = 20,
  D100 = 100
} DiceType;

// Struct that contains dice infos
typedef struct {
  int n;               // Number of dices
  DiceType dices_type; // dice type
} Dices;

uint8_t simple_discard_method(int divisor, FILE *rand_reader);

#endif // SRC_H
