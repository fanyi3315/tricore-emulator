#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void set_memory_uint8_t(uint32_t address, uint8_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

void set_memory_uint16_t(uint32_t address, uint16_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

void set_memory_uint32_t(uint32_t address, uint32_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

uint8_t get_memory_uint8_t(uint32_t address) {
  printf("get_memory_uint8_t %08x\n", address);
  if (address == 0x80018000) {
    return 0x10;
  } else if (address == 0x80018008) {
    return 0x00;
  } else if (address == 0x80018009) {
    return 0x40;
  } else if (address == 0x8001800A) {
    return 0x01;
  } else if (address == 0x8001800B) {
    return 0x80;
  } else {
    fprintf(stderr, "TODO: %08x\n", address);
    exit(1);
  }
}

uint16_t get_memory_uint16_t(uint32_t address) {
  fprintf(stderr, "TODO: %08x\n", address);
  exit(1);
}

uint32_t get_memory_uint32_t(uint32_t address) {
  fprintf(stderr, "TODO: %08x\n", address);
  exit(1);
}
