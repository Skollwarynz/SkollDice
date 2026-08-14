#ifndef SRC_H
#define SRC_H

#if defined(_WIN32) || defined(_WIN64)
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
  #endif
  #include <windows.h>
  #include <ntsecapi.h>
#else
  #include <fcntl.h>
  #include <unistd.h>
#endif

#include "lvgl/lvgl.h"

#if defined(__ANDROID__)
  struct android_app;
#else
  #define SDL_MAIN_HANDLED /* Evita che SDL2 sovrascriva il main() su Windows */
  #include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdint.h>

#if defined(_WIN32) || defined(_WIN64)
  uint8_t windows_random(int divisor);
#else
  uint8_t simple_discard_method(int divisor, FILE *rand_reader);
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

#endif // SRC_H
