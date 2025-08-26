#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const char alphanumerics[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char *itoa(int value, char *str, int base) {
  if (base < 2 || base > 36)
    return NULL;
  if (value < 0)
    value = -value;
  int length = ilen(value, base);
  int i;
  for (i = length - 1; i != -1; i--) {
    str[i] = alphanumerics[value % base];
    value /= base;
  }
  str[length] = 0;
  return str;
}

char *uint64_to_string(uint64_t value, char *str, int base) {
  if (base < 2 || base > 36)
    return NULL;
  int length = uint64_len(value, base);
  int i;
  for (i = length - 1; i != -1; i--) {
    str[i] = alphanumerics[value % ((uint64_t)base)];
    value /= (uint64_t)base;
  }
  str[length] = 0;
  return str;
}