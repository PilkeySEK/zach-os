#include <kernel/interrupts.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Handles any interrupt
 * @param regs The state of the registers
 */
void interrupts_handler(struct intr_regs_s *regs) {
  if (regs->intr_num <= 0x1F) {
    printf("Exception no: %d\n", regs->intr_num);
    __asm__ volatile("cli; hlt");
    while (1) {
    }
  } else {
    // Recognized interrupt 42
    if (regs->intr_num == 42) {

    } else {
      printf("Unrecognized interrupt %d\n", regs->intr_num);
    }
  }
}