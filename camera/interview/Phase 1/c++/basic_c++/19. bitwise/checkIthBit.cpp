#include <iostream>
using namespace std;

bool checkIthBit(int n, int i) {
  // Check if the i-th bit is set using bitwise AND operation
  return (n & (1 << i)) !=
         0; // If the i-th bit is 1, the result will be non-zero
}

int main() {

  int num = 5;      // Binary: 101
  int bitIndex = 1; // Check the 2nd bit (0-based index)

  if (checkIthBit(num, bitIndex)) {
    cout << "The " << bitIndex << "-th bit of " << num << " is set (1)."
         << endl;
  } else {
    cout << "The " << bitIndex << "-th bit of " << num
         << " is not set (0)." // Not able to understand this

         /* 5 = 101
         n = 5
         i = 1
         1 << i = 1 << 1 = 2
         n & (1 << i) = 5 & 2 = 0
         0 is false so it will go to else block means the 1st bit is not set
       (0). but first is 0 only na like 101 means 0 at the first position and 1
         means at the second position then why it is not set at second position?


         the first means 1 is in first positin and it's set to 0 like 101
         so 1 is at second position right?


         0 1 2
         1 0 1
         means at the second position it is 0 right?

       0 is false so it will go to else block means the 1st bit is not set (0).
       so we have to check bit from left to right or right to left?


       we are going from right to left means from the last position not from the
       first position   we have to check from the last position means from the
       right most position
       */
         << endl;
  }
}