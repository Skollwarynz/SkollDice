#include "../include/src.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// specifics about the code inside README and /include/src.h
// Why the function is normally distrubuted explained inside the README
// Inside /include/src.h is contained the Enum explanation

uint8_t simple_discard_method(int divisor, FILE *rand_reader) {
  int limit = (256 / divisor) * divisor;
  uint8_t random_byte;
  do {
    fread(&random_byte, sizeof(uint8_t), 1, rand_reader);
  } while (random_byte >= limit);
  int result = (random_byte % divisor) + 1;
  return result;
}

int main() {
  FILE *rand_reader = fopen("/dev/urandom", "rb");
  // number of dices trhown
  int number_of_dice = 0;

  genrate_GUI();

  // array with the number of each type of dice
  Dices types_and_number_of_dices[7] = {
      {100000, D4},  {100000, D6},  {100000, D8},  {100000, D10},
      {100000, D12}, {100000, D20}, {100000, D100}};
  int index_dices = 0;
  // while infinito per il gioco che funzioni piu di una volta prob su raylib
  while (index_dices < 7) {
    // printf("Inizio %d\n", index_dices);
    int number_of_generations = types_and_number_of_dices[index_dices].n;
    printf("D%d: ", types_and_number_of_dices[index_dices].dices_type);
    for (int i = 0; i < number_of_generations; i++) {
      int value = simple_discard_method(
          types_and_number_of_dices[index_dices].dices_type, rand_reader);
      printf("%d ", value);
    }
    printf("\n");
    index_dices++;
  }

  return 0;
}
