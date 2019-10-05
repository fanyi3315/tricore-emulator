#include <stdint.h>
#include <stdlib.h>
#include "parson/parson.h"

uint32_t parse_first_opperand_as_address(JSON_Object *instruction) {
  JSON_Array *operands;
  const char *operand;
  operands = json_object_get_array(instruction, "operands");
  operand = json_array_get_string(operands, 0);
  return strtol(operand, NULL, 16);
}
