#pragma once
#include "../src/includes.c"


int test_hex1() {
  short   ok;
  int32_t val = rgba_from_string("#ff1e00", &ok);

  assert(ok);
  assert(0xff1e00ff == val);
  rgba_t r0  = rgba_new(val);
  char   *s0 = malloc(1024);

  rgba_to_string(r0, s0, 256);

  dbg(s0, % s);
  rgba_inspect(val);
  return(0);
}


bool initialize_args(){
  args          = malloc(sizeof(args_t));
  args->mode    = DEFAULT_MODE;
  args->verbose = DEFAULT_VERBOSE;
  args->palette = DEFAULT_PALETTE;
  return(true);
}


void pman_init() {
  tc_get_cols_rows(&cols, &rows);
  assert(initialize_args());
  assert(isatty(STDOUT_FILENO));


  //printf(" cols: %d | rows: %d\n", cols, rows);
  //printf("qty templates: %lu\n", TEMPLATES_QTY);
  //test_hex1();
  //list_palettes();
}

