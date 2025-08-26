#ifndef _KERNEL_HEAP_H
#define _KERNEL_HEAP_H 1

#include <stddef.h>
#include <stdint.h>

/*
typedef struct _KHEAPBLOCKBM {
  struct _KHEAPBLOCKBM *next;
  uint32_t size;
  uint32_t used;
  uint32_t bsize;
  uint32_t lfb;
} KHEAPBLOCKBM;

typedef struct _KHEAPBM {
  KHEAPBLOCKBM *fblock;
} KHEAPBM;

void k_heapBMInit(KHEAPBM *heap);
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32_t size,
                     uint32_t bsize);
// static uint8_t k_heapBMGetNID(uint8_t a, uint8_t b);
void *k_heapBMAlloc(KHEAPBM *heap, uint32_t size);
void k_heapBMFree(KHEAPBM *heap, void *ptr);
*/

enum KHeapBlockHeaderFlagsBits {
  KHEAP_FLAG_USED = 0b00000000000000000000000000000001,
  KHEAP_SIZE_FLAG_SPACE = 0b11111111111111111111111111111110,
};

// typedef struct _KHeapBlockHeader {
//   KHeapBlockHeaderFlags flags;
//   size_t size;
// } KHeapBlockHeader;

typedef uint32_t KHeapBlockHeader;

/*
typedef struct _KHeapBlockHeaderWithSize {
  uint8_t flags;
  size_t size;
} KHeapBlockHeaderWithSize;
*/

typedef struct _KHeap {
  KHeapBlockHeader *start;
  size_t size;
  size_t used;
} KHeap;

KHeap *k_heapInit(KHeap *kheap, uintptr_t start, size_t size);
// KHeapBlock *k_heapAddBlock(KHeap *heap, uintptr_t addr, size_t size, size_t
// block_size);

void *k_heapMalloc(KHeap *heap, size_t size);
void k_heapFree(KHeap *heap, void *ptr);

#endif