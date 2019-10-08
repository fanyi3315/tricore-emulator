#include <stdint.h>

void set_memory_uint8_t(uint32_t, uint8_t);
void set_memory_uint16_t(uint32_t, uint16_t);
void set_memory_uint32_t(uint32_t, uint32_t);

uint8_t get_memory_uint8_t(uint32_t);
uint16_t get_memory_uint16_t(uint32_t);
uint32_t get_memory_uint32_t(uint32_t);

void init_memory();
void flush_memory();
