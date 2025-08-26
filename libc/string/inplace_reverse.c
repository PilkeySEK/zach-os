#include <string.h>

// https://stackoverflow.com/questions/784417/reversing-a-string-in-c

char *inplace_reverse(char *str) {
  if (str) {
    char *end = str + strlen(str) - 1;

    // swap the values in the two given variables
    // XXX: fails when a and b refer to same memory location
#define XOR_SWAP(a, b)                                                         \
  do {                                                                         \
    a ^= b;                                                                    \
    b ^= a;                                                                    \
    a ^= b;                                                                    \
  } while (0)

    // walk inwards from both ends of the string,
    // swapping until we get to the middle
    while (str < end) {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#undef XOR_SWAP
  }
  return str;
}