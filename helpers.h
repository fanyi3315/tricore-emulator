#include <stdint.h>
#include "parson/parson.h"

int8_t parse_operand_as_int8_t(JSON_Object*, size_t, size_t);
int32_t parse_operand_as_int32_t(JSON_Object*, size_t, size_t);
uint32_t parse_operand_as_uint32_t(JSON_Object*, size_t, size_t);
const char*  parse_operand_as_string(JSON_Object*, size_t);
void progress_program_counter(JSON_Object*);
uint8_t extract_bit(uint32_t, size_t);
uint32_t set_bit(uint32_t, uint8_t);
uint32_t clear_bit(uint32_t, uint8_t);