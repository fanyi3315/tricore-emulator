#include <stdint.h>
#include "parson/parson.h"

uint32_t parse_operand_as_uint32_t(JSON_Object*, size_t, size_t);
const char*  parse_operand_as_string(JSON_Object*, size_t);
void progress_program_counter(JSON_Object*);
