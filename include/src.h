#define SRC
#ifdef SRC

/*
The program saves the different dices into an array that uses the struct Dices
to quicly calculate the right number of results for each type of dice
*/

// Dice list
typedef struct {
  // number of dice
  int n;
  // types od dices
  enum {
    D4 = 4,
    D6 = 6,
    D8 = 8,
    D10 = 10,
    D12 = 12,
    D20 = 20,
    D100 = 100
  } dices_type;
} Dices;

#endif // SRC
