#include "parson/parson.h"
#include "registers.h"
#include <stdio.h>

void log_instruction(JSON_Object *instruction) {
  char *serialized_instruction;
  serialized_instruction =
      json_serialize_to_string(json_object_get_wrapping_value(instruction));
  printf("instruction: %s\n", serialized_instruction);
  json_free_serialized_string(serialized_instruction);
}

void log_registers() {
  printf("registers: a0  = %08x a1  = %08x a2  = %08x a3  = %08x\n",
         get_register("a0"), get_register("a1"), get_register("a2"),
         get_register("a3"));
  printf("registers: a4  = %08x a5  = %08x a6  = %08x a7  = %08x\n",
         get_register("a4"), get_register("a5"), get_register("a6"),
         get_register("a7"));
  printf("registers: a8  = %08x a9  = %08x a10 = %08x a11 = %08x\n",
         get_register("a8"), get_register("a9"), get_register("a10"),
         get_register("a11"));
  printf("registers: a12 = %08x a13 = %08x a14 = %08x a15 = %08x\n",
         get_register("a12"), get_register("a13"), get_register("a14"),
         get_register("a15"));
  printf("registers: d0  = %08x d1  = %08x d2  = %08x d3  = %08x\n",
         get_register("d0"), get_register("d1"), get_register("d2"),
         get_register("d3"));
  printf("registers: d4  = %08x d5  = %08x d6  = %08x d7  = %08x\n",
         get_register("d4"), get_register("d5"), get_register("d6"),
         get_register("d7"));
  printf("registers: d8  = %08x d9  = %08x d10 = %08x d11 = %08x\n",
         get_register("d8"), get_register("d9"), get_register("d10"),
         get_register("d11"));
  printf("registers: d12 = %08x d13 = %08x d14 = %08x d15 = %08x\n",
         get_register("d12"), get_register("d13"), get_register("d14"),
         get_register("d15"));
}
