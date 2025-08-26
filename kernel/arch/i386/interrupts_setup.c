#include <kernel/interrupts.h>
#include <stdint.h>

struct idt_entry_s {
  uint16_t addr_low;
  uint16_t selector; // GDT selector (which code segment)
  uint8_t empty;
  uint8_t flags;
  uint16_t addr_high;
} __attribute__((packed));

struct idt_ptr_s {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt_entry_s idt_table[0x40];
struct idt_ptr_s idt_ptr;

void intrs_disable_intrs(void) { __asm__ volatile("cli"); }

void intrs_enable_intrs(void) { __asm__ volatile("sti"); }

void intrs_init(void) {
  intrs_install_empty_idt();
  intrs_init_isrs();
}

void intrs_install_empty_idt() {
  /*
  SYNOPSIS:    Clears the IDT, and installs it ready to use.
  INPUTS:        None.
  OUTPUT:        None.
  NOTES:        None.
  */

  unsigned char *temp;
  unsigned int count = 0;

  // Create the pointer.
  idt_ptr.limit = (sizeof(struct idt_entry_s) * 0x40) - 1;
  idt_ptr.base = (unsigned int)&idt_table;

  // Empty the IDT. THis is a hack of a code.
  temp = (void *)&idt_table;
  while (count < (sizeof(struct idt_entry_s) * 0x40)) {
    *temp = 0x00;
    temp++;
    count++;
  }

  // Do the install.
  __asm__ __volatile__("lidt %0" ::"m"(idt_ptr));
}

void intrs_init_isrs() {
  intrs_set_gate(0x00, (unsigned)interrupts_ISR_00, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x01, (unsigned)interrupts_ISR_01, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x02, (unsigned)interrupts_ISR_02, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x03, (unsigned)interrupts_ISR_03, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x04, (unsigned)interrupts_ISR_04, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x05, (unsigned)interrupts_ISR_05, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x06, (unsigned)interrupts_ISR_06, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x07, (unsigned)interrupts_ISR_07, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x08, (unsigned)interrupts_ISR_08, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x09, (unsigned)interrupts_ISR_09, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0A, (unsigned)interrupts_ISR_0A, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0B, (unsigned)interrupts_ISR_0B, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0C, (unsigned)interrupts_ISR_0C, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0D, (unsigned)interrupts_ISR_0D, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0E, (unsigned)interrupts_ISR_0E, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x0F, (unsigned)interrupts_ISR_0F, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x10, (unsigned)interrupts_ISR_10, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x11, (unsigned)interrupts_ISR_11, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x12, (unsigned)interrupts_ISR_12, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x13, (unsigned)interrupts_ISR_13, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x14, (unsigned)interrupts_ISR_14, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x15, (unsigned)interrupts_ISR_15, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x16, (unsigned)interrupts_ISR_16, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x17, (unsigned)interrupts_ISR_17, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x18, (unsigned)interrupts_ISR_18, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x19, (unsigned)interrupts_ISR_19, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1A, (unsigned)interrupts_ISR_1A, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1B, (unsigned)interrupts_ISR_1B, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1C, (unsigned)interrupts_ISR_1C, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1D, (unsigned)interrupts_ISR_1D, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1E, (unsigned)interrupts_ISR_1E, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x1F, (unsigned)interrupts_ISR_1F, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_TRAPGATE32);
  intrs_set_gate(0x20, (unsigned)interrupts_ISR_20, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x21, (unsigned)interrupts_ISR_21, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x22, (unsigned)interrupts_ISR_22, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x23, (unsigned)interrupts_ISR_23, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x24, (unsigned)interrupts_ISR_24, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x25, (unsigned)interrupts_ISR_25, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x26, (unsigned)interrupts_ISR_26, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x27, (unsigned)interrupts_ISR_27, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x28, (unsigned)interrupts_ISR_28, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x29, (unsigned)interrupts_ISR_29, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2A, (unsigned)interrupts_ISR_2A, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2B, (unsigned)interrupts_ISR_2B, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2C, (unsigned)interrupts_ISR_2C, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2D, (unsigned)interrupts_ISR_2D, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2E, (unsigned)interrupts_ISR_2E, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x2F, (unsigned)interrupts_ISR_2F, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x30, (unsigned)interrupts_ISR_30, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x31, (unsigned)interrupts_ISR_31, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x32, (unsigned)interrupts_ISR_32, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x33, (unsigned)interrupts_ISR_33, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x34, (unsigned)interrupts_ISR_34, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x35, (unsigned)interrupts_ISR_35, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x36, (unsigned)interrupts_ISR_36, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x37, (unsigned)interrupts_ISR_37, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x38, (unsigned)interrupts_ISR_38, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x39, (unsigned)interrupts_ISR_39, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3A, (unsigned)interrupts_ISR_3A, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3B, (unsigned)interrupts_ISR_3B, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3C, (unsigned)interrupts_ISR_3C, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3D, (unsigned)interrupts_ISR_3D, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3E, (unsigned)interrupts_ISR_3E, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
  intrs_set_gate(0x3F, (unsigned)interrupts_ISR_3F, 0x08,
                 IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_INTGATE32);
}

void intrs_set_gate(uint8_t num, uint32_t addr, uint16_t selector,
                    uint8_t flags) {
  idt_table[num].addr_low = (addr & 0xFFFF);
  idt_table[num].addr_high = (addr >> 16) & 0xFFFF;

  idt_table[num].selector = selector;
  idt_table[num].empty = 0x00;
  idt_table[num].flags = flags;
}