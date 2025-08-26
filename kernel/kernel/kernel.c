#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/heap.h>
#include <kernel/idt.h>
#include <kernel/multiboot.h>
#include <kernel/tty.h>

extern uint32_t kernel_end;
extern uint32_t kernel_start;

void kernel_main(multiboot_info_t *mbd, uint32_t magic) {
  terminal_initialize();
  idt_init();
  volatile int x = 50 / 0;

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    printf("Failed to boot: Multiboot magic number is invalid!");
    return;
  }

  if (!(mbd->flags >> 6 & 0x1)) {
    printf("Failed to boot: Invalid memory map provided by bootloader.");
    return;
  }

  uint64_t total_memory_usable = 0;
  multiboot_memory_map_t *biggest_mmmt = NULL;
  bool biggest_mmmt_was_set = false;
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
      if (biggest_mmmt_was_set == false || mmmt->len > biggest_mmmt->len) {
        biggest_mmmt_was_set = true;
        biggest_mmmt = mmmt;
      }
    }
  }
  uint64_t total_memory_usable_mb = total_memory_usable / 1000000;
  printf("Total memory usable: %uld bytes or %uld MB\n", total_memory_usable,
         total_memory_usable_mb);
  if (!biggest_mmmt_was_set) {
    printf("Did not find any usable memory. Cannot boot.\n");
    return;
  }
  printf("Biggest memory map at %ulp has %uld bytes (approximately %uld MB) of "
         "memory usable.\n",
         biggest_mmmt->addr, biggest_mmmt->len, biggest_mmmt->len / 1000000);

  uintptr_t kernel_end_addr = (uintptr_t)&kernel_end;
  uintptr_t kernel_start_addr = (uintptr_t)&kernel_start;

  uint32_t heap_addr = (uintptr_t)biggest_mmmt->addr;
  size_t heap_size = (size_t)biggest_mmmt->len;
  // shift the address to the kernel end address if bootloader included the
  // kernel in the usable memory (i know this check is flawed but it works for
  // now)
  if (heap_addr == kernel_start_addr) {
    heap_size -= (size_t)(kernel_end_addr - kernel_start_addr);
    heap_addr = kernel_end_addr;
  }

  KHeap heap;
  k_heapInit(&heap, heap_addr, heap_size);
  printf("Initialized heap at %p with size %d bytes (approximately %d MB)",
         heap_addr, heap_size, heap_size / 1000000);

  printf("Initializing kernel\n");
}
