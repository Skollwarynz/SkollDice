#include "../include/src.h"
// specifics about the code inside README and /include/src.h
// Why the function is normally distrubuted explained inside the README
// Inside /include/src.h is contained the Enum explanation
#if !_WIN32
#define RtlGenRandom(b,n) fread(b, n, 1, rand_reader)
#endif
uint8_t windows_random(int divisor){
  int limit = (256 / divisor) * divisor;
  uint8_t random_byte;
  do {
    RtlGenRandom(&random_byte, sizeof(random_byte));
  } while (random_byte >= limit);
  int result = (random_byte % divisor) + 1;
  return result;
}
