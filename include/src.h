#ifndef SRC_H
#define SRC_H

#include "lvgl/lvgl.h"
#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#if defined(_WIN32) || defined(_WIN64)
  #include <windows.h>
  #include <ntsecapi.h> 
  #ifndef SystemFunction036
    #define SystemFunction036 RtlGenRandom
    BOOLEAN WINAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);
  #endif
#else
  #include <fcntl.h>
  #include <unistd.h>
#endif
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

// simple discard
uint8_t simple_discard_method(int divisor, FILE *rand_reader);

#endif // SRC_H
