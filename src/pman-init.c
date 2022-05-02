#pragma once
#include "../include/macros.h"
#include "../include/pman0-defines.h"
#include "../include/pman0-types.h"
#include "../src/pman0-globals.c"
#define VERBOSE_INIT_MODE false

bool meson_test_mode_enabled = false;     static int meson_test_mode_ran = -1;
void meson_test_mode(){
  if (meson_test_mode_ran > 0) {
    return;
  }
  char *__is_meson_test_mode__ = env_get_or("__MESON_TEST_MODE__", "-1");

  if (strcmp(__is_meson_test_mode__, "1") == 0) {
    meson_test_mode_enabled = true;
    if(VERBOSE_INIT_MODE)
        fprintf(stderr, "is_meson_test_mode enabled!\n");
  }else{
    meson_test_mode_enabled = false;
    if(VERBOSE_INIT_MODE)
        fprintf(stderr, "is_meson_test_mode disabled!\n");
  }
  if (!meson_test_mode_enabled) {
    int is_tty = isatty(STDOUT_FILENO);
    if(is_tty){
        tc_get_cols_rows((int *)(&cols), (int *)(&rows));
    }else{
        cols = 80; rows = 120;
    }
  }
  meson_test_mode_ran = 1;
}


bool initialize_args(){
  meson_test_mode();
  return(true);
}

void pman_init() {
  assert_eq(initialize_args(), true, % d);
  if(VERBOSE_INIT_MODE)
      fprintf(stderr, " cols: %d | rows: %d\n", cols, rows);
}

