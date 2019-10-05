#include <stdint.h>
#include <stdio.h>

void set_memory_uint8_t(uint32_t address, uint8_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

void set_memory_uint16_t(uint32_t address, uint16_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}

void set_memory_uint32_t(uint32_t address, uint32_t value) {
  printf("set_memory_uint8_t: %08x %02x\n", address, value);
}
