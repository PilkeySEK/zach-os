#include <stdint.h>
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

int uint64_len(uint64_t value, int base) {
  if (base < 2)
    return -1;
  int len = 1;
  while (value > ((uint64_t)(base - 1))) {
    len++;
    value /= (uint64_t)base;
  }
  return len;
}