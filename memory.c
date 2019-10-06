#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

static uint8_t *memory = NULL;

void set_memory_uint8_t(uint32_t address, uint8_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

void set_memory_uint16_t(uint32_t address, uint16_t value) {
  printf("set_memory_uint16_t: %08x %04x\n", address, value);
}

void set_memory_uint32_t(uint32_t address, uint32_t value) {
  printf("set_memory_uint32_t: %08x %08x\n", address, value);
}

uint8_t get_memory_uint8_t(uint32_t address) {
  printf("get_memory_uint8_t %08x\n", address);
  if (address >= 0x80000000 && address <= 0x80200000) {
    uint32_t offset = address - 0x80000000;
    return memory[offset];
    return 0;
  } else {
    fprintf(stderr, "TODO: %08x\n", address);
    exit(1);
  }
}

uint16_t get_memory_uint16_t(uint32_t address) {
  printf("get_memory_uint16_t %08x\n", address);
  if (address >= 0x80000000 && address <= 0x80200000) {
    uint32_t offset = address - 0x80000000;
    return (memory[offset + 1] << 8) + memory[offset];
    return 0;
  } else {
    fprintf(stderr, "TODO: %08x\n", address);
    exit(1);
  }
}

uint32_t get_memory_uint32_t(uint32_t address) {
  fprintf(stderr, "TODO: %08x\n", address);
  exit(1);
}

void init_memory() {
  int fd;
  struct stat s;
  size_t size;
  fd = open("firmware.bin", O_RDONLY);
  fstat(fd, &s);
  size = s.st_size;
  memory = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
}