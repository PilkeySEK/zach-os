#include <stdint.h>
#include <stdio.h>

#include <kernel/heap.h>
#include <kernel/tty.h>

extern uint32_t kernel_end;

void kernel_main(void) {
  terminal_initialize();
  uint32_t pfree = (uint32_t)&kernel_end;
  KHeap heap;
  // initialize 4MB heap (TODO: base heap size on free memory (get free memory
  // from bootloader))
  k_heapInit(&heap, (uintptr_t)pfree, 4000000);

  printf("Initialized heap at %p with size %d bytes\n", heap.start, heap.size);
  printf("Initializing kernel\n");
}
