#ifndef SRC_H
#define SRC_H

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
// GUI initializer
void genrate_GUI();

#endif // SRC_H
