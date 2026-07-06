#include <iostream>
using namespace std;

// Write down bitwise set, clear, etc progream here.

void setBit(int &n, int pos) { n = n | (1 << pos); }

void clearBit(int &n, int pos) {
  int mask = ~(1 << pos);
  n = n & mask;

  // can we write it as also n = n & ~(1<<pos)
  // Yes, it can be written as:
  // n &= ~(1 << pos);
  // how it written n = n & ~(1<<pos) ?
  // 1. (1 << pos) creates a value with only the bit at 'pos' set to 1.
  // 2. ~(1 << pos) flips all bits (bitwise NOT), making the bit at 'pos' 0 and
  // all others 1.
  // 3. n & ... performs bitwise AND, which keeps all other bits of 'n' the same
  // but forces the bit at 'pos' to 0.
  // n = n & ~(1 << pos);
}

void toggleBit(int &n, int pos) { n = n ^ (1 << pos); }

bool getBit(int n, int pos) { return (n & (1 << pos)) != 0; }

// Define marco also
#define SET_BIT(n, pos) (n |= (1 << pos))
#define CLEAR_BIT(n, pos) (n &= ~(1 << pos))
#define TOGGLE_BIT(n, pos) (n ^= (1 << pos))
#define GET_BIT(n, pos) ((n >> pos) & 1)

int main() {

  // How to use macro
  int num = 5; // Binary: 0101

  // Set the 1st bit (0-indexed)
  SET_BIT(num, 1); // num becomes 7 (0111)

  // if SET_BIT(num, 0); -> 5
  // why? becuase num = 5 (0101)
  // num = 5(0101)
  //  0001
  //  0101
  // ------
  //  0101
  // num | (1 << 0) = 5 | 1 = 5 (0101)
  // ans is 5.

  // Clear the 2nd bit
  CLEAR_BIT(num, 2); // num becomes 3 (0011)
  /* Dry run

Original n : 101
Bit to clear (pos=2)
            ↑

Mask       : 011
Result     : 001

So CLEAR_BIT(n, 2) changes 101 to 001 by clearing bit position 2.

  */

  // Toggle the 0th bit
  TOGGLE_BIT(num, 0); // output is 1 ??
  // num = 3 (0011)
  // 1 << 0 = 1 (0001)
  // num ^ (1 << 0) = 3 ^ 1 = 2 (0010)
  // output is 2

  // Get the 1st bit
  bool bit = GET_BIT(num, 1); // bit will be 1
}