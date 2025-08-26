#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool print(const char *data, size_t length) {
  const unsigned char *bytes = (const unsigned char *)data;
  for (size_t i = 0; i < length; i++)
    if (putchar(bytes[i]) == EOF)
      return false;
  return true;
}

int printf(const char *restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != 0) {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {

        return -1;
      }
      if (!print(format, amount))
        return -1;
      format += amount;
      written += amount;
      continue;
    }

    const char *format_begun_at = format++;

    if (*format == 'c') {
      format++;
      char c = (char)va_arg(parameters, int);
      if (!maxrem) {

        return -1;
      }
      if (!print(&c, sizeof(c)))
        return -1;
      written++;
    } else if (*format == 's') {
      format++;
      const char *str = va_arg(parameters, const char *);
      size_t len = strlen(str);
      if (maxrem < len) {

        return -1;
      }
      if (!print(str, len))
        return -1;
      written += len;
    } else if (*format == 'd') {
      format++;
      int num = va_arg(parameters, int);
      if (!maxrem) {

        return -1;
      }
      int num_len = ilen(num, 10);
      char num_str[num_len + 1];
      if (!print(itoa(num, num_str, 10), num_len))
        return -1;
      written += num_len;
    } else if (*format == 'p') {
      format++;
      int num = va_arg(parameters, int);
      if (!maxrem) {

        return -1;
      }
      int num_len = ilen(num, 16);
      char num_str[num_len + 1];
      if (!print("0x", 2))
        return -1;
      if (!print(itoa(num, num_str, 16), num_len))
        return -1;
      written += num_len + 2;
    } else if (*format == 'b') {
      format++;
      int num = va_arg(parameters, int);
      if (!maxrem) {

        return -1;
      }
      int num_len = ilen(num, 2);
      char num_str[num_len + 1];
      if (!print(itoa(num, num_str, 2), num_len))
        return -1;
      written += num_len;
    } else if (*format == 'u') {
      format++;
      if (*format == 'l') {
        format++;
        int base = 10;
        if (*format == 'd') {
          base = 10;
        } else if (*format == 'p') {
          base = 16;
        } else if (*format == 'b') {
          base = 2;
        }
        format++;
        uint64_t num = va_arg(parameters, uint64_t);
        if (!maxrem) {

          return -1;
        }
        int num_len = uint64_len(num, base);
        char num_str[num_len + 1];
        if (base == 16) {
          if (!print("0x", 2))
            return -1;
        }
        if (!print(uint64_to_string(num, num_str, base), num_len))
          return -1;
        written += num_len + (base == 16 ? 2 : 0);
      } else if (*format == 'p') {
        format++;
        unsigned int num = va_arg(parameters, unsigned int);
        if (!maxrem) {

          return -1;
        }
        int num_len = uint64_len((uint64_t)num, 16);
        char num_str[num_len + 1];
        if (!print("0x", 2))
          return -1;
        if (!print(uint64_to_string(num, num_str, 16), num_len))
          return -1;
        written += num_len + 2;
      } else if (*format == 'd') {
        format++;
        unsigned int num = va_arg(parameters, unsigned int);
        if (!maxrem) {

          return -1;
        }
        int num_len = uint64_len((uint64_t)num, 10);
        char num_str[num_len + 1];
        if (!print(uint64_to_string(num, num_str, 10), num_len))
          return -1;
        written += num_len;
      }
    } else {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len) {

        return -1;
      }
      if (!print(format, len))
        return -1;
      written += len;
      format += len;
    }
  }

  va_end(parameters);
  return written;
}