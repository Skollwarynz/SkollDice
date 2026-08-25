#include "../include/src.h"
// specifics about the code inside README and /include/src.h
// Why the function is normally distrubuted explained inside the README
// Inside /include/src.h is contained the Enum explanation
#if defined(_WIN32) || defined(_WIN64)
  uint8_t windows_random(int divisor){
    int limit = (256 / divisor) * divisor;
    uint8_t random_byte;
    do {
      RtlGenRandom(&random_byte, sizeof(random_byte));
    } while (random_byte >= limit);
    int result = (random_byte % divisor) + 1;
    return result;
  }
#else
  uint8_t simple_discard_method(int divisor, FILE *rand_reader) {
    int limit = (256 / divisor) * divisor;
    uint8_t random_byte;
    do {
      fread(&random_byte, sizeof(uint8_t), 1, rand_reader);
    } while (random_byte >= limit);
    int result = (random_byte % divisor) + 1;
    return result;
  }
#endif
