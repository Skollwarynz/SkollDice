#ifndef GLOBALS_H
#define GLOBALS_H

#include "src.h" 

// Backend gloabls
// reader for /urandom
extern FILE* rand_reader;
//Array of requests
extern Dices types_and_number_of_dices[7];

// GUI gloabls 
extern lv_obj_t *text_D4;
extern lv_obj_t *text_D6;
extern lv_obj_t *text_D8;
extern lv_obj_t *text_D10;
extern lv_obj_t *text_D12;
extern lv_obj_t *text_D20;
extern lv_obj_t *text_D100;
extern lv_obj_t *label_output;
extern lv_obj_t *screen;

#endif // GLOBALS_H
