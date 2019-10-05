#include "helpers.h"
#include "log.h"
#include "memory.h"
#include "parson/parson.h"
#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_add_instruction(JSON_Object *instruction) {
  const char *register_name;
  uint8_t value;
  register_name = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(register_name, get_register(register_name) + value);
  progress_program_counter(instruction);
}

void handle_addi_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  value = parse_operand_as_uint32_t(instruction, 2, 10);
  set_register(destination_register, get_register(source_register) + value);
  progress_program_counter(instruction);
}

void handle_addih_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  uint16_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  value = parse_operand_as_uint32_t(instruction, 2, 10);
  set_register(destination_register,
               get_register(source_register) + (value << 16));
  progress_program_counter(instruction);
}

void handle_addsca_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  const char *data_register;
  uint8_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  data_register = parse_operand_as_string(instruction, 2);
  set_register(destination_register,
               get_register(source_register) +
                   (get_register(data_register) << value));
  progress_program_counter(instruction);
}

void handle_and_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_andne_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_call_instruction(JSON_Object *instruction) {
  uint32_t address;
  // save the caller’s registers upper context in a dynamically-allocated save
  // area.
  save_upper_context(instruction);
  address = parse_operand_as_uint32_t(instruction, 0, 16);
  // move to operand
  set_register("pc", address);
}

void handle_calla_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_calli_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_dsync_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_extru_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_isync_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_j_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jeq_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jge_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jgeu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jltu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jne_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jnz_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jz_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jza_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jzt_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_lda_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ldbu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ldhu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ldw_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_lea_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "d9fff4ef") == 0) {
    set_register("a15", get_register("a15") - 0x4c);
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_loop_instruction(JSON_Object *instruction) {
  const char *register_name;
  uint32_t address;
  register_name = parse_operand_as_string(instruction, 0);
  address = parse_operand_as_uint32_t(instruction, 1, 16);
  if (get_register(register_name) != 0) {
    set_register("pc", address);
  } else {
    progress_program_counter(instruction);
  }
  set_register(register_name, get_register(register_name) - 1);
}

void handle_mfcr_instruction(JSON_Object *instruction) {
  const char *data_register_name;
  uint16_t core_register_name;
  data_register_name = parse_operand_as_string(instruction, 0);
  core_register_name = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(data_register_name, get_core_register(core_register_name));
  progress_program_counter(instruction);
}

void handle_mov_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (instruction_hex[0] == '0') {
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(source_register));
  } else {
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register, value);
  }
  progress_program_counter(instruction);
}

void handle_mova_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  const char *destination_register;
  const char *source_register;
  uint8_t value;
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
  progress_program_counter(instruction);
}

void handle_movaa_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_movd_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_movu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_movh_instruction(JSON_Object *instruction) {
  const char *destination_register;
  uint16_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(destination_register, value << 16);
  progress_program_counter(instruction);
}

void handle_movha_instruction(JSON_Object *instruction) {
  const char *destination_register;
  uint16_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  value = parse_operand_as_uint32_t(instruction, 1, 10);
  set_register(destination_register, value << 16);
  progress_program_counter(instruction);
}

void handle_mtcr_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ne_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_nop_instruction(JSON_Object *instruction) {
  progress_program_counter(instruction);
}

void handle_or_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_orne_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ret_instruction(JSON_Object *instruction) {
  // Restore upper context
  restore_upper_context();
}

void handle_sel_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_sh_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_sha_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_sta_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_stb_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "2801") == 0) {
    set_memory_uint8_t(get_register("a15"), get_register("d1"));
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_stw_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_sub_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_suba_instruction(JSON_Object *instruction) {
  const char *register_name;
  uint32_t amount;
  register_name = parse_operand_as_string(instruction, 0);
  amount = parse_operand_as_uint32_t(instruction, 1, 16);
  set_register(register_name, get_register(register_name) - amount);
  progress_program_counter(instruction);
}
