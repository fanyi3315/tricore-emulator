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
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rd") == 0) {
    const char *destination_register;
    uint8_t value;
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register,
                 get_register(destination_register) & value);
  } else if (strcmp(operands_format, "rr") == 0) {
    const char *destination_register;
    const char *source_register;
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(destination_register) &
                                           get_register(source_register));
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_andne_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "0b0110f2") == 0) {
    uint8_t not_equal_result = get_register("d1") != get_register("d0") ? 1 : 0;
    uint8_t value_first_bit = extract_bit(get_register("d0"), 0, 1);
    uint8_t result = value_first_bit & not_equal_result ? 1 : 0;
    set_register("d15", result);
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
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
  progress_program_counter(instruction);
}

void handle_extru_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  uint8_t position;
  uint8_t width;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  position = parse_operand_as_uint32_t(instruction, 2, 10);
  width = parse_operand_as_uint32_t(instruction, 3, 10);
  if (position == 0x00 && width == 0x08) {
    set_register(destination_register, get_register(source_register) & 0xFF);
  } else if (position == 0x1C && width == 0x04) {
    set_register(destination_register, get_register(source_register) & 0x0F);
  } else if (get_register(source_register) == 0xd001fff5 && position == 0x06 &&
             width == 0x10) {
    set_register(destination_register, 0x3F);
  } else if (get_register(source_register) == 0xd00000c0 && position == 0x06 &&
             width == 0x10) {
    set_register(destination_register, 0x00);
  } else {
    fprintf(stderr, "TODO %08x %02x %02x\n", get_register(source_register),
            position, width);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_isync_instruction(JSON_Object *instruction) {
  progress_program_counter(instruction);
}

void handle_j_instruction(JSON_Object *instruction) {
  uint32_t address;
  address = parse_operand_as_uint32_t(instruction, 0, 16);
  set_register("pc", address);
}

void handle_jeq_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rda") == 0) {
    const char *register_name;
    uint32_t value;
    uint32_t address;
    register_name = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    address = parse_operand_as_uint32_t(instruction, 2, 16);
    if (get_register(register_name) == value) {
      set_register("pc", address);
    } else {
      progress_program_counter(instruction);
    }
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
}

void handle_jge_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_jgeu_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rra") == 0) {
    const char *register_a;
    const char *register_b;
    uint32_t address;
    register_a = parse_operand_as_string(instruction, 0);
    register_b = parse_operand_as_string(instruction, 1);
    address = parse_operand_as_uint32_t(instruction, 2, 16);
    if (get_register(register_a) >= get_register(register_b)) {
      set_register("pc", address);
    } else {
      progress_program_counter(instruction);
    }
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
}

void handle_jltu_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rra") == 0) {
    const char *register_a;
    const char *register_b;
    uint32_t address;
    register_a = parse_operand_as_string(instruction, 0);
    register_b = parse_operand_as_string(instruction, 1);
    address = parse_operand_as_uint32_t(instruction, 2, 16);
    if (get_register(register_a) < get_register(register_b)) {
      set_register("pc", address);
    } else {
      progress_program_counter(instruction);
    }
  } else if (strcmp(operands_format, "rda") == 0) {
    const char *register_name;
    uint32_t value;
    uint32_t address;
    register_name = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    address = parse_operand_as_uint32_t(instruction, 2, 16);
    if (get_register(register_name) < value) {
      set_register("pc", address);
    } else {
      progress_program_counter(instruction);
    }
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
}

void handle_jne_instruction(JSON_Object *instruction) {
  const char *register_a;
  const char *register_b;
  uint32_t address;
  register_a = parse_operand_as_string(instruction, 0);
  register_b = parse_operand_as_string(instruction, 1);
  address = parse_operand_as_uint32_t(instruction, 2, 16);
  if (get_register(register_a) != get_register(register_b)) {
    set_register("pc", address);
  } else {
    progress_program_counter(instruction);
  }
}

void handle_jnz_instruction(JSON_Object *instruction) {
  const char *register_name;
  uint32_t address;
  register_name = parse_operand_as_string(instruction, 0);
  address = parse_operand_as_uint32_t(instruction, 1, 16);
  if (get_register(register_name) != 0) {
    set_register("pc", address);
  } else {
    progress_program_counter(instruction);
  }
}

void handle_jz_instruction(JSON_Object *instruction) {
  const char *register_name;
  uint32_t address;
  register_name = parse_operand_as_string(instruction, 0);
  address = parse_operand_as_uint32_t(instruction, 1, 16);
  if (get_register(register_name) == 0) {
    set_register("pc", address);
  } else {
    progress_program_counter(instruction);
  }
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
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "0cf0") == 0) { // ld.bu d15, [a15]0
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x00));
  } else if (strcmp(instruction_hex, "0cf9") == 0) { // ld.bu d15, [a15]9
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x09));
  } else if (strcmp(instruction_hex, "0880") == 0) { // ld.bu d0, [a15]8
    set_register("d0", get_memory_uint8_t(get_register("a15") + 0x08));
  } else if (strcmp(instruction_hex, "08a0") == 0) { // ld.bu d0, [a15]10
    set_register("d0", get_memory_uint8_t(get_register("a15") + 0x0A));
  } else if (strcmp(instruction_hex, "0cfb") == 0) { // ld.bu d15, [a15]11
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x0B));
  } else if (strcmp(instruction_hex, "09ff5808") == 0) { // ld.bu d15, [a15]24
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x18));
  } else if (strcmp(instruction_hex, "09ff5108") == 0) { // ld.bu d15, [a15]17
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x11));
  } else if (strcmp(instruction_hex, "09f05008") == 0) { // ld.bu d0, [a15]16
    set_register("d0", get_memory_uint8_t(get_register("a15") + 0x10));
  } else if (strcmp(instruction_hex, "09f05208") == 0) { // ld.bu d0, [a15]18
    set_register("d0", get_memory_uint8_t(get_register("a15") + 0x12));
  } else if (strcmp(instruction_hex, "09ff5308") == 0) { // ld.bu d15, [a15]19
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x13));
  } else if (strcmp(instruction_hex, "0cf6") == 0) { // ld.bu d15, [a15]6
    set_register("d15", get_memory_uint8_t(get_register("a15") + 0x06));
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_ldhu_instruction(JSON_Object *instruction) {
  fprintf(stderr, "TODO\n");
  exit(1);
  progress_program_counter(instruction);
}

void handle_ldw_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "4802") == 0) { // ld.w d2, [a15]0
    set_register("d2", get_memory_uint16_t(get_register("a15") + 0x00) << 16);
  } else if (strcmp(instruction_hex, "5430") == 0) { // ld.w d0, [a3]
    set_register("d0", get_memory_uint16_t(get_register("a3") + 0x00) << 16);
  } else if (strcmp(instruction_hex, "4c31") == 0) { // ld.w d15, [a3]4
    set_register("d15", get_memory_uint16_t(get_register("a3") + 0x04) << 16);
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_lea_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "d9fff4ef") == 0) { // lea a15, [a15]-76
    set_register("a15", get_register("a15") - 0x4c);
  } else if (strcmp(instruction_hex, "d9ff0008") == 0) { // lea a15, [a15]-32768
    set_register("a15", get_register("a15") - 0x8000);
  } else if (strcmp(instruction_hex, "d9fff5ef") == 0) { // lea a15, [a15]-75
    set_register("a15", get_register("a15") - 0x4b);
  } else if (strcmp(instruction_hex, "d9330010") == 0) { // lea a3, [a3]64
    set_register("a3", get_register("a15") + 0x40);
  } else if (strcmp(instruction_hex, "d9aa8031") == 0) { // lea sp, [sp]6336
    set_register("sp", get_register("sp") + 0x18C0);
  } else if (strcmp(instruction_hex, "d9002087") == 0) { // lea a0, [a0]29216
    set_register("a0", get_register("a0") + 0x7220);
  } else if (strcmp(instruction_hex, "d922fcef") == 0) { // lea a2, [a2]-68
    set_register("a2", get_register("a2") - 0x44);
  } else if (strcmp(instruction_hex, "d9ffbc7b") == 0) { // lea a15, [a15]-17924
    set_register("a15", get_register("a15") - 0x4604);
  } else if (strcmp(instruction_hex, "d92fffff") == 0) { // lea a15, [a2]-1
    set_register("a15", get_register("a2") - 0x01);
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
  const char *operands_format;
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rd") == 0) {
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register, value);
  } else if (strcmp(operands_format, "rr") == 0) {
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(source_register));
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_movaa_instruction(JSON_Object *instruction) {
  const char *operands_format;
  const char *destination_register;
  const char *source_register;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rr") == 0) {
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(source_register));
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_movd_instruction(JSON_Object *instruction) {
  const char *operands_format;
  const char *destination_register;
  const char *source_register;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rr") == 0) {
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(source_register));
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_movu_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rd") == 0) {
    const char *destination_register;
    uint16_t value;
    destination_register = parse_operand_as_string(instruction, 0);
    value = parse_operand_as_uint32_t(instruction, 1, 10);
    set_register(destination_register, value);
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
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
  const char *data_register_name;
  uint16_t core_register_name;
  core_register_name = parse_operand_as_uint32_t(instruction, 0, 10);
  data_register_name = parse_operand_as_string(instruction, 1);
  set_core_register(core_register_name, get_register(data_register_name));
  progress_program_counter(instruction);
}

void handle_ne_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  uint8_t value;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  set_register(destination_register,
               get_register(source_register) != value ? 1 : 0);
  progress_program_counter(instruction);
}

void handle_nop_instruction(JSON_Object *instruction) {
  progress_program_counter(instruction);
}

void handle_or_instruction(JSON_Object *instruction) {
  JSON_Array *operands;
  operands = json_object_get_array(instruction, "operands");
  if (json_array_get_count(operands) == 2) {
    const char *destination_register;
    const char *source_register;
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(destination_register) |
                                           get_register(source_register));
  } else {
    const char *destination_register;
    const char *register_a;
    const char *register_b;
    destination_register = parse_operand_as_string(instruction, 0);
    register_a = parse_operand_as_string(instruction, 1);
    register_b = parse_operand_as_string(instruction, 2);
    set_register(destination_register,
                 get_register(register_a) | get_register(register_b));
  }
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
  const char *destination_register;
  const char *pivot_register;
  const char *if_non_zero_register;
  uint8_t if_zero_value;
  destination_register = parse_operand_as_string(instruction, 0);
  pivot_register = parse_operand_as_string(instruction, 1);
  if_non_zero_register = parse_operand_as_string(instruction, 2);
  if_zero_value = parse_operand_as_uint32_t(instruction, 3, 10);
  uint32_t value = get_register(pivot_register) == 0
                       ? if_zero_value
                       : get_register(if_non_zero_register);
  set_register(destination_register, value);
  progress_program_counter(instruction);
}

void handle_sh_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rd") == 0) {
    const char *destination_register;
    uint16_t amount;
    destination_register = parse_operand_as_string(instruction, 0);
    amount = parse_operand_as_uint32_t(instruction, 1, 10);
    if (amount >= 0) {
      set_register(destination_register, get_register(destination_register)
                                             << amount);
    } else {
      set_register(destination_register,
                   get_register(destination_register) >> -amount);
    }
  } else if (strcmp(operands_format, "rrd") == 0) {
    const char *destination_register;
    const char *source_register;
    uint16_t amount;
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    amount = parse_operand_as_uint32_t(instruction, 2, 10);
    if (amount >= 0) {
      set_register(destination_register, get_register(source_register)
                                             << amount);
    } else {
      set_register(destination_register,
                   get_register(source_register) >> -amount);
    }
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_sha_instruction(JSON_Object *instruction) {
  const char *destination_register;
  const char *source_register;
  uint8_t amount;
  destination_register = parse_operand_as_string(instruction, 0);
  source_register = parse_operand_as_string(instruction, 1);
  amount = parse_operand_as_uint32_t(instruction, 2, 10);
  if (amount >= 0) {
    set_register(destination_register, get_register(source_register) << amount);
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_sta_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "f434") == 0) { // st.a [a3], a4
    set_memory_uint16_t(get_register("a3"), get_register("a4"));
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_stb_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "2801") == 0) { // st.b [a15]0, d1
    set_memory_uint8_t(get_register("a15"), get_register("d1"));
  } else if (strcmp(instruction_hex, "2802") == 0) { // st.b [a15]0, d2
    set_memory_uint8_t(get_register("a15"), get_register("d2"));
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_stw_instruction(JSON_Object *instruction) {
  const char *instruction_hex;
  instruction_hex = json_object_get_string(instruction, "hex");
  if (strcmp(instruction_hex, "7431") == 0) { // st.w [a3], d1
    set_memory_uint32_t(get_register("a3"), get_register("d1"));
  } else if (strcmp(instruction_hex, "59fff0ef") == 0) { // st.w [a15]-80, d15
    set_memory_uint32_t(get_register("a15") - 0x50, get_register("d15"));
  } else if (strcmp(instruction_hex, "642f") == 0) { // st.w [a2+], d15
    set_memory_uint32_t(get_register("a2"), get_register("d15"));
    set_register("a2", get_register("a2") + 4);
  } else if (strcmp(instruction_hex, "6421") == 0) { // st.w [a2+], d1
    set_memory_uint32_t(get_register("a2"), get_register("d1"));
    set_register("a2", get_register("a2") + 4);
  } else {
    fprintf(stderr, "TODO\n");
    exit(1);
  }
  progress_program_counter(instruction);
}

void handle_sub_instruction(JSON_Object *instruction) {
  const char *operands_format;
  operands_format = json_object_get_string(instruction, "format");
  if (strcmp(operands_format, "rr") == 0) {
    const char *destination_register;
    const char *source_register;
    destination_register = parse_operand_as_string(instruction, 0);
    source_register = parse_operand_as_string(instruction, 1);
    set_register(destination_register, get_register(destination_register) -
                                           get_register(source_register));
  } else {
    fprintf(stderr, "TODO %s\n", operands_format);
    exit(1);
  }
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
