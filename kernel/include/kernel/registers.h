#ifndef INCLUDES_REGISTERS_H_
#define INCLUDES_REGISTERS_H_

/// @brief Form of the registers passed to the interrupt handler by the CPU.
struct intr_regs_s {
  unsigned int gs, fs, es, ds;                         // pushed last.
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
  unsigned int intr_num, err_code; // pushed by the stub (and sometimes the
                                   // error code pushed by the interrupt)
  unsigned int epi, cs, eflags, useresp, ss; // pushed by the interrupt itself.
};

#endif // INCLUDES_REGISTERS_H_