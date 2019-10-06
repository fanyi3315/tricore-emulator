#include "parson/parson.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct save_area {
  uint32_t a10;
  uint32_t a11;
  uint32_t a12;
  uint32_t a13;
  uint32_t a14;
  uint32_t a15;
  uint32_t d8;
  uint32_t d9;
  uint32_t d10;
  uint32_t d11;
  uint32_t d12;
  uint32_t d13;
  uint32_t d14;
  uint32_t d15;
  uint32_t pc;
};

static struct save_area save_areas[16];
static size_t save_area_index = 0;

/* Address registers */
static uint32_t a0 = 0;
static uint32_t a1 = 0;
static uint32_t a2 = 0;
static uint32_t a3 = 0;
static uint32_t a4 = 0;
static uint32_t a5 = 0;
static uint32_t a6 = 0;
static uint32_t a7 = 0;
static uint32_t a8 = 0;
static uint32_t a9 = 0;
static uint32_t a10 = 0;
static uint32_t a11 = 0;
static uint32_t a12 = 0;
static uint32_t a13 = 0;
static uint32_t a14 = 0;
static uint32_t a15 = 0;
/* Data registers */
static uint32_t d0 = 0;
static uint32_t d1 = 0;
static uint32_t d2 = 0;
static uint32_t d3 = 0;
static uint32_t d4 = 0;
static uint32_t d5 = 0;
static uint32_t d6 = 0;
static uint32_t d7 = 0;
static uint32_t d8 = 0;
static uint32_t d9 = 0;
static uint32_t d10 = 0;
static uint32_t d11 = 0;
static uint32_t d12 = 0;
static uint32_t d13 = 0;
static uint32_t d14 = 0;
static uint32_t d15 = 0;
/* Program counter */
static uint32_t pc = 0;
/* Core registers */
static uint32_t core_register_fe08 = 0;
static uint32_t core_register_fe00 = 0;
static uint32_t core_register_fe3c = 0;
static uint32_t core_register_fe38 = 0;

uint32_t get_core_register(uint16_t name) {
  if (name == 0xfe08) {
    return core_register_fe08;
  } else if (name == 0xfe00) {
    return core_register_fe00;
  } else if (name == 0xfe3c) {
    return core_register_fe3c;
  } else if (name == 0xfe38) {
    return core_register_fe38;
  } else {
    fprintf(stderr, "unable to get unknown core register: %08x\n", name);
    exit(1);
  }
}

void set_core_register(uint16_t name, uint32_t value) {
  if (name == 0xfe08) {
    core_register_fe08 = value;
  } else if (name == 0xfe00) {
    core_register_fe00 = value;
  } else if (name == 0xfe3c) {
    core_register_fe3c = value;
  } else if (name == 0xfe38) {
    core_register_fe38 = value;
  } else {
    fprintf(stderr, "unable to set core register: %08x\n", name);
    exit(1);
  }
}

uint32_t get_register(const char *name) {
  if (strcmp(name, "a0") == 0) {
    return a0;
  } else if (strcmp(name, "a1") == 0) {
    return a1;
  } else if (strcmp(name, "a2") == 0) {
    return a2;
  } else if (strcmp(name, "a3") == 0) {
    return a3;
  } else if (strcmp(name, "a4") == 0) {
    return a4;
  } else if (strcmp(name, "a5") == 0) {
    return a5;
  } else if (strcmp(name, "a6") == 0) {
    return a6;
  } else if (strcmp(name, "a7") == 0) {
    return a7;
  } else if (strcmp(name, "a8") == 0) {
    return a8;
  } else if (strcmp(name, "a9") == 0) {
    return a9;
  } else if (strcmp(name, "a10") == 0 || strcmp(name, "sp") == 0) {
    return a10;
  } else if (strcmp(name, "a11") == 0) {
    return a11;
  } else if (strcmp(name, "a12") == 0) {
    return a12;
  } else if (strcmp(name, "a13") == 0) {
    return a13;
  } else if (strcmp(name, "a14") == 0) {
    return a14;
  } else if (strcmp(name, "a15") == 0) {
    return a15;
  } else if (strcmp(name, "d0") == 0) {
    return d0;
  } else if (strcmp(name, "d1") == 0) {
    return d1;
  } else if (strcmp(name, "d2") == 0) {
    return d2;
  } else if (strcmp(name, "d3") == 0) {
    return d3;
  } else if (strcmp(name, "d4") == 0) {
    return d4;
  } else if (strcmp(name, "d5") == 0) {
    return d5;
  } else if (strcmp(name, "d6") == 0) {
    return d6;
  } else if (strcmp(name, "d7") == 0) {
    return d7;
  } else if (strcmp(name, "d8") == 0) {
    return d8;
  } else if (strcmp(name, "d9") == 0) {
    return d9;
  } else if (strcmp(name, "d10") == 0) {
    return d10;
  } else if (strcmp(name, "d11") == 0) {
    return d11;
  } else if (strcmp(name, "d12") == 0) {
    return d12;
  } else if (strcmp(name, "d13") == 0) {
    return d13;
  } else if (strcmp(name, "d14") == 0) {
    return d14;
  } else if (strcmp(name, "d15") == 0) {
    return d15;
  } else if (strcmp(name, "pc") == 0) {
    return pc;
  } else {
    fprintf(stderr, "attempt to get unknown register: %s\n", name);
    exit(1);
  }
}

void set_register(const char *name, uint32_t value) {
  printf("set_register: %s = %08x\n", name, value);
  if (strcmp(name, "a0") == 0) {
    a0 = value;
  } else if (strcmp(name, "a1") == 0) {
    a1 = value;
  } else if (strcmp(name, "a2") == 0) {
    a2 = value;
  } else if (strcmp(name, "a3") == 0) {
    a3 = value;
  } else if (strcmp(name, "a4") == 0) {
    a4 = value;
  } else if (strcmp(name, "a5") == 0) {
    a5 = value;
  } else if (strcmp(name, "a6") == 0) {
    a6 = value;
  } else if (strcmp(name, "a7") == 0) {
    a7 = value;
  } else if (strcmp(name, "a8") == 0) {
    a8 = value;
  } else if (strcmp(name, "a9") == 0) {
    a9 = value;
  } else if (strcmp(name, "a10") == 0 || strcmp(name, "sp") == 0) {
    a10 = value;
  } else if (strcmp(name, "a11") == 0) {
    a11 = value;
  } else if (strcmp(name, "a12") == 0) {
    a12 = value;
  } else if (strcmp(name, "a13") == 0) {
    a13 = value;
  } else if (strcmp(name, "a14") == 0) {
    a14 = value;
  } else if (strcmp(name, "a15") == 0) {
    a15 = value;
  } else if (strcmp(name, "d0") == 0) {
    d0 = value;
  } else if (strcmp(name, "d1") == 0) {
    d1 = value;
  } else if (strcmp(name, "d2") == 0) {
    d2 = value;
  } else if (strcmp(name, "d3") == 0) {
    d3 = value;
  } else if (strcmp(name, "d4") == 0) {
    d4 = value;
  } else if (strcmp(name, "d5") == 0) {
    d5 = value;
  } else if (strcmp(name, "d6") == 0) {
    d6 = value;
  } else if (strcmp(name, "d7") == 0) {
    d7 = value;
  } else if (strcmp(name, "d8") == 0) {
    d8 = value;
  } else if (strcmp(name, "d9") == 0) {
    d9 = value;
  } else if (strcmp(name, "d10") == 0) {
    d10 = value;
  } else if (strcmp(name, "d11") == 0) {
    d11 = value;
  } else if (strcmp(name, "d12") == 0) {
    d12 = value;
  } else if (strcmp(name, "d13") == 0) {
    d13 = value;
  } else if (strcmp(name, "d14") == 0) {
    d14 = value;
  } else if (strcmp(name, "d15") == 0) {
    d15 = value;
  } else if (strcmp(name, "pc") == 0) {
    pc = value;
  } else {
    fprintf(stderr, "attempt to set unknown register: %s\n", name);
    exit(1);
  }
}

void restore_upper_context() {
  save_area_index--;
  printf("restore_upper_context: %02x\n", save_area_index);
  set_register("a10", save_areas[save_area_index].a10);
  set_register("a11", save_areas[save_area_index].a11);
  set_register("a12", save_areas[save_area_index].a12);
  set_register("a13", save_areas[save_area_index].a13);
  set_register("a14", save_areas[save_area_index].a14);
  set_register("a15", save_areas[save_area_index].a15);
  set_register("d8", save_areas[save_area_index].d8);
  set_register("d9", save_areas[save_area_index].d9);
  set_register("d10", save_areas[save_area_index].d10);
  set_register("d11", save_areas[save_area_index].d11);
  set_register("d12", save_areas[save_area_index].d12);
  set_register("d13", save_areas[save_area_index].d13);
  set_register("d14", save_areas[save_area_index].d14);
  set_register("d15", save_areas[save_area_index].d15);
  set_register("pc", save_areas[save_area_index].pc);
}

void save_upper_context(JSON_Object *instruction) {
  printf("save_upper_context: %02x\n", save_area_index);
  uint32_t instruction_size;
  uint32_t pc;
  pc = get_register("pc");
  instruction_size = json_object_get_number(instruction, "size");
  save_areas[save_area_index].a10 = get_register("a10");
  save_areas[save_area_index].a11 = get_register("a11");
  save_areas[save_area_index].a12 = get_register("a12");
  save_areas[save_area_index].a13 = get_register("a13");
  save_areas[save_area_index].a14 = get_register("a14");
  save_areas[save_area_index].a15 = get_register("a15");
  save_areas[save_area_index].d8 = get_register("d8");
  save_areas[save_area_index].d9 = get_register("d9");
  save_areas[save_area_index].d10 = get_register("d10");
  save_areas[save_area_index].d11 = get_register("d11");
  save_areas[save_area_index].d12 = get_register("d12");
  save_areas[save_area_index].d13 = get_register("d13");
  save_areas[save_area_index].d14 = get_register("d14");
  save_areas[save_area_index].d15 = get_register("d15");
  save_areas[save_area_index].pc = pc + instruction_size;
  save_area_index++;
}
