#include <stdint.h>
#include "parson/parson.h"

uint32_t get_register(const char *name);
void set_register(const char *name, uint32_t value);
void restore_upper_context();
void save_upper_context(JSON_Object*);
uint32_t get_core_register(uint16_t name);