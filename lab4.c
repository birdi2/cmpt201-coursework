#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define _DEFAULT_SOURCE
#define BLOCK_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

int main(void) {
  // Step 1: Grow heap by 256 bytes
  void *heap = sbrk(256);
  if (heap == (void *)-1) {
    perror("sbrk failed");
    return 1;
  }

  // Step 2: Make two equal blocks
  struct header *block_one = (struct header *)heap;
  struct header *block_two = (struct header *)((char *)heap + BLOCK_SIZE);

  block_one->size = BLOCK_SIZE;
  block_one->next = NULL;
  block_two->size = BLOCK_SIZE;
  block_two->next = block_one;

  size_t data_size = BLOCK_SIZE - sizeof(struct header); // 112 (amt of available on each block

  uint8_t *block_one_data_ptr = (uint8_t *)(block_one + 1);

  for (size_t i = 0; i < data_size; i++) {
    block_one_data_ptr[i] = 0;
  }

  uint8_t *block_two_data_ptr = (uint8_t *)(block_two + 1);
  for (size_t i = 0; i < data_size; i++) {
    block_two_data_ptr[i] = 1;
  }

  // Step 3: print the info
  //
  printf("first block:       %p\n", (void *)block_one);
  printf("second block:      %p\n", (void *)block_two);
  printf("first block size:  %lu\n", (unsigned long)block_one->size);
  printf("first block next:  %p\n", (void *)block_one->next);
  printf("second block size: %lu\n", (unsigned long)block_two->size);
  printf("second block next: %p\n", (void *)block_two->next);

  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", block_one_data_ptr[i]);
  }
  for (size_t i = 0; i < data_size; i++) {
    printf("%d\n", block_two_data_ptr[i]);
  }

  return 0;
}
