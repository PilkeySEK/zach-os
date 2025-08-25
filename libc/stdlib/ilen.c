#include <stdlib.h>

int ilen(int value, int base) {
  if (base < 2)
    return -1;
  if (value < 0)
    value = -value;
  int len = 1;
  while (value > base - 1) {
    len++;
    value /= base;
  }
  return len;
}