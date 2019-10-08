#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

static uint8_t *pmu0 = NULL;
static uint8_t *pmu1 = NULL;
static uint8_t *external_flash = NULL;
static uint8_t *c00000000 = NULL;
static uint8_t *d00000000 = NULL;

void set_memory_uint8_t(uint32_t address, uint8_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
  bool valid_d0000000_range = address >= 0xd0000000 && address <= 0xd000ffff;
  bool valid_c0000000_range = address >= 0xc0000000 && address <= 0xc00fffff;
  if (valid_d0000000_range) {
    uint32_t offset = address - 0xd0000000;
    d00000000[offset] = value;
  } else if (valid_c0000000_range) {
    uint32_t offset = address - 0xc0000000;
    c00000000[offset] = value;
  } else {
    fprintf(stderr, "set_memory_uint8_t: TODO: %08x\n", address);
    exit(1);
  }
}

void set_memory_uint16_t(uint32_t address, uint16_t value) {
  printf("set_memory_uint16_t: %08x %04x\n", address, value);
  bool valid_d0000000_range = address >= 0xd0000000 && address <= 0xd000ffff;
  bool valid_c0000000_range = address >= 0xc0000000 && address <= 0xc00fffff;
  if (valid_d0000000_range) {
    uint32_t offset = address - 0xd0000000;
    d00000000[offset] = value & 0xFF;
    d00000000[offset + 1] = (value >> 8) & 0xFF;
  } else if (valid_c0000000_range) {
    uint32_t offset = address - 0xc0000000;
    c00000000[offset] = value & 0xFF;
    c00000000[offset + 1] = (value >> 8) & 0xFF;
  } else {
    fprintf(stderr, "set_memory_uint16_t: TODO: %08x\n", address);
    exit(1);
  }
}

void set_memory_uint32_t(uint32_t address, uint32_t value) {
  printf("set_memory_uint32_t: %08x %08x\n", address, value);
  bool valid_d0000000_range = address >= 0xd0000000 && address <= 0xd000ffff;
  bool valid_c0000000_range = address >= 0xc0000000 && address <= 0xc00fffff;
  if (valid_d0000000_range) {
    uint32_t offset = address - 0xd0000000;
    d00000000[offset] = value & 0xFF;
    d00000000[offset + 1] = (value >> 8) & 0xFF;
    d00000000[offset + 2] = (value >> 16) & 0xFF;
    d00000000[offset + 3] = (value >> 24) & 0xFF;
  } else if (valid_c0000000_range) {
    uint32_t offset = address - 0xc0000000;
    c00000000[offset] = value & 0xFF;
    c00000000[offset + 1] = (value >> 8) & 0xFF;
    c00000000[offset + 2] = (value >> 16) & 0xFF;
    c00000000[offset + 3] = (value >> 24) & 0xFF;
  } else {
    fprintf(stderr, "set_memory_uint32_t: TODO: %08x\n", address);
    exit(1);
  }
}

uint8_t get_memory_uint8_t(uint32_t address) {
  if (address >= 0x80000000 && address <= 0x801FFFFF) {
    uint32_t offset = address - 0x80000000;
    printf("get_memory_uint8_t pmu0 %08x %08x\n", address, offset);
    return pmu0[offset];
  } else if (address >= 0x80800000 && address <= 0x809FFFFF) {
    uint32_t offset = address - 0x80800000;
    printf("get_memory_uint8_t pmu1 %08x %08x\n", address, offset);
    return pmu1[offset];
  } else if (address >= 0x84000000 && address <= 0x843FFFFF) {
    uint32_t offset = address - 0x84000000;
    printf("get_memory_uint8_t external_flash %08x %08x\n", address, offset);
    return external_flash[offset];
  } else {
    fprintf(stderr, "get_memory_uint8_t: TODO: %08x\n", address);
    exit(1);
  }
}

uint16_t get_memory_uint16_t(uint32_t address) {
  printf("get_memory_uint16_t %08x\n", address);
  if (address >= 0x80000000 && address <= 0x801FFFFF) {
    uint32_t offset = address - 0x80000000;
    return (pmu0[offset + 1] << 8) + pmu0[offset];
  } else {
    fprintf(stderr, "get_memory_uint16_t: TODO: %08x\n", address);
    exit(1);
  }
}

uint32_t get_memory_uint32_t(uint32_t address) {
  fprintf(stderr, "get_memory_uint32_t: %08x\n", address);
  if (address >= 0x80000000 && address <= 0x801FFFFF) {
    uint32_t offset = address - 0x80000000;
    return (pmu0[offset + 3] << 24) + (pmu0[offset + 2] << 16) +
           (pmu0[offset + 1] << 8) + pmu0[offset];
  } else {
    fprintf(stderr, "get_memory_uint32_t: TODO: %08x\n", address);
    exit(1);
  }
}

void init_memory() {
  int pmu0_fd;
  int pmu1_fd;
  int external_flash_fd;
  struct stat pmu0_s;
  struct stat pmu1_s;
  struct stat external_flash_s;
  pmu0_fd = open("pmu0.bin", O_RDONLY);
  pmu1_fd = open("pmu1.bin", O_RDONLY);
  external_flash_fd = open("external_flash.bin", O_RDONLY);
  fstat(pmu0_fd, &pmu0_s);
  fstat(pmu1_fd, &pmu1_s);
  fstat(external_flash_fd, &external_flash_s);
  pmu0 = mmap(0, pmu0_s.st_size, PROT_READ, MAP_PRIVATE, pmu0_fd, 0);
  pmu1 = mmap(0, pmu1_s.st_size, PROT_READ, MAP_PRIVATE, pmu1_fd, 0);
  external_flash = mmap(0, external_flash_s.st_size, PROT_READ, MAP_PRIVATE,
                        external_flash_fd, 0);
  c00000000 = malloc(0xFFFF);
  d00000000 = malloc(0xFFFF);
}
