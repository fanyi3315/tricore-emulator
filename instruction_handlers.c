#include "helpers.h"
#include "parson/parson.h"
#include "registers.h"
#include <stdio.h>
#include <stdlib.h>

void handle_add_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *register_name;
  uint8_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  register_name = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(register_name, get_register(register_name) + value);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_addi_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  value = parse_operand_as_uint32_t(instruction, 2, 10);
  set_register(destination_register, get_register(source_register) + value);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_addih_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *destination_register;
  const char *source_register;
  uint16_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  value = parse_operand_as_uint32_t(instruction, 2, 10);
  set_register(destination_register,
               get_register(source_register) + (value << 16));
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_addsca_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *destination_register;
  const char *source_register;
  const char *data_register;
  uint8_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  data_register = parse_operand_as_string(instruction, 2);
  set_register(destination_register,
               get_register(source_register) +
                   (get_register(data_register) << value));
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_and_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_andne_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_call_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t address;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // save the caller’s registers upper context in a dynamically-allocated save
  // area.
  save_upper_context(instruction);
  address = parse_operand_as_uint32_t(instruction, 0, 16);
  // move to operand
  set_register("pc", address);
}

void handle_calla_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_calli_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_dsync_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_extru_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_isync_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_j_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jeq_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jge_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jgeu_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jltu_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jne_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jnz_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jz_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jza_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_jzt_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_lda_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_ldbu_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_ldhu_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_ldw_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_lea_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_loop_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_mfcr_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *data_register_name;
  uint16_t core_register_name;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  data_register_name = parse_operand_as_string(instruction, 0);
  core_register_name = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(data_register_name, get_core_register(core_register_name));
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_mov_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *instruction_hex;
  const char *destination_register;
  uint8_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  instruction_hex = json_object_get_string(instruction, "hex");
  if (instruction_hex[0] == '8') {
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register, value);
  } else {
    fprintf(stderr, "TODO %c\n", instruction_hex[0]);
    exit(1);
  }
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_mova_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *instruction_hex;
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  instruction_hex = json_object_get_string(instruction, "hex");
  if (instruction_hex[0] == 'a') {
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register, value);
  } else if (instruction_hex[0] == '6') {
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    value = get_register(source_register);
    set_register(destination_register, value);
  } else {
    fprintf(stderr, "TODO %c\n", instruction_hex[0]);
    exit(1);
  }
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_movaa_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_movd_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_movu_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_movh_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *destination_register;
  uint16_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  destination_register = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(destination_register, value << 16);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_movha_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *destination_register;
  uint16_t value;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  destination_register = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(destination_register, value << 16);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_mtcr_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_ne_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_nop_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_or_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_orne_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_ret_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Restore upper context
  restore_upper_context();
}

void handle_sel_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_sh_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_sha_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_sta_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_stb_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_stw_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_sub_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  fprintf(stderr, "TODO\n");
  exit(1);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}

void handle_suba_instruction(JSON_Object *instruction) {
  // Declare variables
  uint32_t pc;
  uint32_t instruction_size;
  const char *register_name;
  uint32_t amount;
  // Get program counter
  pc = get_register("pc");
  printf("%08x: %s\n", pc, __func__);
  // Perform operation
  register_name = parse_operand_as_string(instruction, 0);
  amount = parse_operand_as_uint32_t(instruction, 1, 16);
  set_register(register_name, get_register(register_name) - amount);
  // Move on to next instruction
  instruction_size = json_object_get_number(instruction, "size");
  set_register("pc", pc + instruction_size);
}
