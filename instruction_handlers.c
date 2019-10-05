#include <stdio.h>
#include <stdlib.h>
#include "parson/parson.h"
#include "registers.h"
#include "helpers.h"

void handle_add_instruction(JSON_Object *instruction) {
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

void handle_addi_instruction(JSON_Object *instruction) {
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

void handle_addih_instruction(JSON_Object *instruction) {
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

void handle_addsca_instruction(JSON_Object *instruction) {
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
  // save the caller’s registers upper context in a dynamically-allocated save area.
  save_upper_context(instruction);
  address = parse_first_opperand_as_address(instruction);
  printf("\t\t%08x\n", address);
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

void handle_mov_instruction(JSON_Object *instruction) {
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

void handle_mova_instruction(JSON_Object *instruction) {
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

void handle_movha_instruction(JSON_Object *instruction) {
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
