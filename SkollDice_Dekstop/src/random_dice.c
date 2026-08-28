#include "../include/src.h"
// specifics about the code inside README and /include/src.h
// Why the function is normally distrubuted explained inside the README
// Inside /include/src.h is contained the Enum explanation
#if defined(_WIN32) || defined(_WIN64)
  uint8_t windows_random(int divisor){
#else
  uint8_t simple_discard_method(int divisor, FILE* rand_reader){
#endif
  int limit = (256 / divisor) * divisor;
    uint8_t random_byte;
    do {
#if defined (_WIN32) || defined (_WIN64)
      RtlGenRandom(&random_byte, sizeof(random_byte));
#else 
      fread(&random_byte, sizeof(uint8_t), 1, rand_reader);
#endif
    } while (random_byte >= limit);
    int result = (random_byte % divisor) + 1;
    return result;
}
