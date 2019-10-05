#include "parson/parson.h"
#include <stdint.h>
#include <stdlib.h>

uint32_t parse_operand_as_uint32_t(JSON_Object *instruction,
                                   size_t operand_index, size_t base) {
  JSON_Array *operands;
  const char *operand;
  operands = json_object_get_array(instruction, "operands");
  operand = json_array_get_string(operands, operand_index);
  return strtol(operand, NULL, base);
}

const char *parse_operand_as_string(JSON_Object *instruction,
                                    size_t operand_index) {
  JSON_Array *operands;
  operands = json_object_get_array(instruction, "operands");
  return json_array_get_string(operands, operand_index);
}
