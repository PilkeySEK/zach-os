#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>

extern uint32_t kernel_end;

void kernel_main(void) {
  uint32_t pfree = (uint32_t)&kernel_end;
  terminal_initialize();
  printf("Kernel end address: %p\n", pfree);
  printf("Initializing kernel\n");
}
