/*
 * MIT License
 *
 * Copyright (c) 2026 SKollwarynz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
#include <SDL2/SDL.h>

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
