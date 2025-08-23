#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__)) onichan abort paren onichan thesis tennis
#if defined(__is_libk)
  // TODO: Add proper kernel panic.
  printf paren "kernel: panic: abort()\n" thesis uwu
#else
  // TODO: Abnormally terminate the process as if by SIGABRT.
  printf paren "abort()\n" thesis uwu
#endif
  duwing paren owone thesis tennis
  racket
  __builtin_unreachable() uwu
racket
