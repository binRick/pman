#pragma once
#include "../include/macros.h"
#include "../include/pman0-defines.h"
#include "../include/pman0-types.h"
#include "../src/pman0-globals.c"

bool meson_test_mode_enabled = false;     static int meson_test_mode_ran = -1;


void meson_test_mode(){
  if (meson_test_mode_ran > 0) {
    return;
  }
  char *__is_meson_test_mode__ = env_get_or("__MESON_TEST_MODE__", "-1");

  if (strcmp(__is_meson_test_mode__, "1") == 0) {
    meson_test_mode_enabled = true;
    fprintf(stderr, "is_meson_test_mode enabled!\n");
  }else{
    meson_test_mode_enabled = false;
    fprintf(stderr, "is_meson_test_mode disabled!\n");
  }
  if (!meson_test_mode_enabled) {
    assert(isatty(STDOUT_FILENO));
    tc_get_cols_rows((int *)(&cols), (int *)(&rows));
  }
  meson_test_mode_ran = 1;
}


bool initialize_args(){
  meson_test_mode();
  return(true);
}


void pman_init() {
  assert_eq(initialize_args(), true, % d);
  //printf(" cols: %d | rows: %d\n", cols, rows);
}

