#include <stdint.h>
#include "parson/parson.h"

uint32_t get_register(const char*);
void set_register(const char *, uint32_t);
void restore_upper_context();
void save_upper_context(JSON_Object*);
uint32_t get_core_register(uint16_t);
void set_core_register(uint16_t, uint32_t);