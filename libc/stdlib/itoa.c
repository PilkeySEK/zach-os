#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

static const char alphanumerics[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char* itoa(int value, char* str, int base) {
    if (base < 2 || base > 36) return NULL;
    if (value < 0) value = -value;
    int length = ilen(value, base);
    int i;
    for (i = length - 1; i != -1; i--) {
        str[i] = alphanumerics[value % base];
        value /= base;
    }
    str[length] = '\0';
    return str;
}