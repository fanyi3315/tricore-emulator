#include "parson/parson.h"
#include "registers.h"
#include <stdint.h>
#include <stdio.h>
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

void progress_program_counter(JSON_Object *instruction) {
  uint32_t instruction_size;
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", get_register("pc") + instruction_size);
}

uint8_t extract_bit(uint32_t value, uint8_t start, uint8_t width) {
  if (start == 0x00 && width == 0x01) {
    return (value & (1 << 1)) >> 1;
  } else {
    fprintf(stderr, "TODO %02x %02x\n", start, width);
    exit(1);
  }
}