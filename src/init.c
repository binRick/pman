#pragma once
#include "../src/includes.c"


bool initialize_args(){
  args = malloc(sizeof(pman_args_t));
  assert(args != NULL);
  args->mode      = DEFAULT_MODE;
  args->verbose   = DEFAULT_VERBOSE;
  args->palette   = DEFAULT_PALETTE;
  args->colorcode = DEFAULT_COLORCODE;


  return(true);
}


void pman_init() {
  tc_get_cols_rows(&cols, &rows);
  assert(initialize_args());
  assert(isatty(STDOUT_FILENO));
  //printf(" cols: %d | rows: %d\n", cols, rows);
}

