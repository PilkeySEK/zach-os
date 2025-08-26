#include <kernel/heap.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define K_HEAP_BLOCK_HEADER_FROM_UINTPTR(ptr)                                  \
  ((KHeapBlockHeader *)(void *)(ptr))
#define UINTPTR_FROM_K_HEAP_BLOCK_HEADER(ptr) ((uintptr_t)(void *)(ptr))
// #define K_HEAP_BLOCK_HEADER_IS_USED(header) ((header & KHEAP_FLAG_USED) != 0)

static KHeapBlockHeader k_heapCreateBlockHeader(size_t size, bool used) {
  KHeapBlockHeader header = size;
  header = header << 1;
  if (used)
    header = header | KHEAP_FLAG_USED;
  return header;
}

static bool k_heapBlockHeaderIsUsed(KHeapBlockHeader header) {
  return (header & KHEAP_FLAG_USED) != 0;
}

static KHeapBlockHeader k_heapBlockHeaderSetFree(KHeapBlockHeader header) {
  return (header & (~KHEAP_FLAG_USED));
}

static size_t k_heapBlockSize(KHeapBlockHeader header) {
  return (size_t)(header >> 1);
}

// Join the block with all free blocks after it until the function meets a used
// block. Returns a pointer to the original header (same as `header` parameter).
static KHeapBlockHeader *k_heapJoinBlocks(KHeap *heap,
                                          KHeapBlockHeader *header) {
  size_t new_header_size = k_heapBlockSize(*header);
  uintptr_t original_ptr = UINTPTR_FROM_K_HEAP_BLOCK_HEADER(header);
  // size_t header_used = k_heapBlockHeaderIsUsed(*header);
  KHeapBlockHeader *current_header = header;
  while (UINTPTR_FROM_K_HEAP_BLOCK_HEADER(current_header) <
         ((uintptr_t)(void *)heap->start) + ((uintptr_t)heap->size)) {
    size_t block_size = k_heapBlockSize(*current_header);
    uintptr_t next_header_ptr =
        UINTPTR_FROM_K_HEAP_BLOCK_HEADER(current_header);
    next_header_ptr += sizeof(KHeapBlockHeader);
    next_header_ptr += (uintptr_t)block_size;
    uint8_t offset = (uint8_t)(next_header_ptr % 4);
    next_header_ptr += offset;
    if (next_header_ptr >
        ((uintptr_t)(void *)heap->start) + ((uintptr_t)heap->size))
      break;
    if (k_heapBlockHeaderIsUsed(*current_header))
      break;
    new_header_size =
        (size_t)(next_header_ptr - original_ptr -
                 ((uintptr_t)sizeof(
                     KHeapBlockHeader))); // k_heapBlockSize(*current_header);
    // new_header_size += (size_t) sizeof(KHeapBlockHeader);
    current_header = K_HEAP_BLOCK_HEADER_FROM_UINTPTR(next_header_ptr);
  }
  *header = k_heapCreateBlockHeader(new_header_size,
                                    k_heapBlockHeaderIsUsed(*header));
  return header;
}

KHeap *k_heapInit(KHeap *heap, uintptr_t start, size_t size) {
  heap->start = K_HEAP_BLOCK_HEADER_FROM_UINTPTR(start);
  heap->size = size;
  heap->used = 0;
  KHeapBlockHeader *first_block_header = (KHeapBlockHeader *)(void *)start;
  *first_block_header =
      k_heapCreateBlockHeader(size - sizeof(KHeapBlockHeader), false);
  return heap;
}

static KHeapBlockHeader *
k_heapFindNextHeader(const KHeap *heap,
                     const KHeapBlockHeader *current_header) {
  size_t block_size = k_heapBlockSize(*current_header);
  uintptr_t next_header_ptr = UINTPTR_FROM_K_HEAP_BLOCK_HEADER(current_header);
  next_header_ptr += sizeof(KHeapBlockHeader);
  next_header_ptr += (uintptr_t)block_size;
  uint8_t offset = (uint8_t)(next_header_ptr % 4);
  next_header_ptr += offset;
  if (next_header_ptr >
      ((uintptr_t)(void *)heap->start) + ((uintptr_t)heap->size))
    return NULL;
  return (KHeapBlockHeader *)(void *)next_header_ptr;
}

// This function assumes the size is not bigger than the block size specified by
// the header
static KHeapBlockHeader *k_heapSplitBlockToFitSize(KHeapBlockHeader *header,
                                                   size_t size) {
  uintptr_t next_header_ptr = UINTPTR_FROM_K_HEAP_BLOCK_HEADER(header) +
                              ((uintptr_t)size) +
                              ((uintptr_t)sizeof(KHeapBlockHeader));
  uint8_t offset = next_header_ptr % 4;
  next_header_ptr += (uintptr_t)offset;
  uintptr_t ptr_diff =
      next_header_ptr - UINTPTR_FROM_K_HEAP_BLOCK_HEADER(header);
  size_t remaining_size = k_heapBlockSize(*header) - ((size_t)ptr_diff);
  *header = k_heapCreateBlockHeader(k_heapBlockSize(*header) - remaining_size -
                                        ((size_t)sizeof(KHeapBlockHeader)),
                                    true);
  remaining_size -= (size_t)sizeof(KHeapBlockHeader);
  *K_HEAP_BLOCK_HEADER_FROM_UINTPTR(next_header_ptr) =
      k_heapCreateBlockHeader(remaining_size, false);
  return header;
}

void *k_heapMalloc(KHeap *heap, size_t size) {
  uintptr_t current_header_ptr = UINTPTR_FROM_K_HEAP_BLOCK_HEADER(heap->start);
  // Search for free block header that has enough size
  while (current_header_ptr <
         ((uintptr_t)heap->size) +
             UINTPTR_FROM_K_HEAP_BLOCK_HEADER(heap->start)) {
    if (k_heapBlockHeaderIsUsed(
            *K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr))) {
      current_header_ptr =
          UINTPTR_FROM_K_HEAP_BLOCK_HEADER(k_heapFindNextHeader(
              heap, K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr)));
      if (current_header_ptr == 0) {
        return NULL;
      }
      continue;
    }
    k_heapJoinBlocks(heap,
                     K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr));
    if (k_heapBlockSize(*K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr)) <
        size) {
      current_header_ptr =
          UINTPTR_FROM_K_HEAP_BLOCK_HEADER(k_heapFindNextHeader(
              heap, K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr)));
      if (current_header_ptr == 0) {
        return NULL;
      }
    } else {
      current_header_ptr =
          UINTPTR_FROM_K_HEAP_BLOCK_HEADER(k_heapSplitBlockToFitSize(
              K_HEAP_BLOCK_HEADER_FROM_UINTPTR(current_header_ptr), size));
      current_header_ptr += sizeof(KHeapBlockHeader);
      heap->used += size;
      heap->used += (size_t)sizeof(KHeapBlockHeader);
      return (void *)current_header_ptr;
    }
  }

  return NULL;
}

void k_heapFree(KHeap *heap, void *ptr) {
  KHeapBlockHeader *header = K_HEAP_BLOCK_HEADER_FROM_UINTPTR(
      ((uintptr_t)ptr) - ((uintptr_t)sizeof(KHeapBlockHeader)));
  *header = k_heapBlockHeaderSetFree(*header);
  heap->used -= k_heapBlockSize(*header) + ((size_t)sizeof(KHeapBlockHeader));
}
