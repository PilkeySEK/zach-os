#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/heap.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>

extern uint32_t kernel_end;

void kernel_main(multiboot_info_t *mbd, uint32_t magic) {
  terminal_initialize();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    printf("Failed to boot: Multiboot magic number is invalid!");
    return;
  }

  if (!(mbd->flags >> 6 & 0x1)) {
    printf("Failed to boot: Invalid memory map provided by bootloader.");
    return;
  }

  uint64_t total_memory_usable = 0;
  multiboot_uint32_t i;
  for (i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
    multiboot_memory_map_t *mmmt =
        (multiboot_memory_map_t *)(mbd->mmap_addr + i);

    int mem_available = mmmt->type == MULTIBOOT_MEMORY_AVAILABLE;

    // printf(
    //     "Start addr: %ulp | Length: %ulp | Size: %up | Type: %ud | Available:
    //     "
    //     "%s\n",
    //     mmmt->addr, mmmt->len, mmmt->size, mmmt->type,
    //     mem_available ? available_true : available_false);
    if (mem_available) {
      total_memory_usable += mmmt->len;
    }
  }
  uint64_t total_memory_usable_mb = total_memory_usable / 1000000;
  printf("Total memory usable: %uld bytes or %uld MB\n", total_memory_usable,
         total_memory_usable_mb);

  uint32_t pfree = (uint32_t)&kernel_end;
  KHeap heap;
  // initialize 4MB heap (TODO: base heap size on free memory (get free memory
  // from bootloader))
  k_heapInit(&heap, (uintptr_t)pfree, 4000000);

  printf("Initialized heap at %p with size %d bytes\n", heap.start, heap.size);
  printf("Initializing kernel\n");
}
