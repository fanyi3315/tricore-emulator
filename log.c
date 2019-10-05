#include "parson/parson.h"
#include <stdio.h>

void log_instruction(const char *name, JSON_Object *instruction) {
  char *serialized_instruction;
  serialized_instruction =
      json_serialize_to_string(json_object_get_wrapping_value(instruction));
  printf("%s %s\n", name, serialized_instruction);
  json_free_serialized_string(serialized_instruction);
}