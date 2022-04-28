#pragma once
#include "../include/includes.h"


int list_color_names_and_rgbs() {
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW "%s" AC_RESETALL
      " "
      AC_RESETALL AC_BRIGHT_GREEN  "%s" AC_RESETALL
      "\n",
      COLOR_NAMES[i].name,
      COLOR_NAMES[i].rgb
      );
  }
  return(0);
}


int list_color_names() {
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf(
      AC_RESETALL "%s" AC_RESETALL
      "\n",
      COLOR_NAMES[i].name
      );
  }
  return(0);
}


int test_hex1() {
  short   ok;
  int32_t val  = rgba_from_string("#ff1e00", &ok);
  int32_t val1 = rgba_from_string("#ffffff", &ok);

  assert(ok);
  assert(0xff1e00ff == val);
  rgba_t r0  = rgba_new(val);
  rgba_t r1  = rgba_new(val1);
  char   *s0 = malloc(1024);
  char   *s1 = malloc(1024);

  rgba_to_string(r0, s0, 256);
  rgba_to_string(r1, s1, 256);

  dbg(s0, % s);
  rgba_inspect(val);

  dbg(s1, % s);
  rgba_inspect(val1);

  return(0);
}


int debug_error(){
  DO_ERR("some error"); return(0);
}


int debug_msg(){
  DO_MSG("some message"); return(0);
}


int debug_die(){
  DO_DIE("critical error"); return(0);
}


static char *__basename(const char *path){
  const char *slash = strrchr(path, '/');

  if (slash) {
    path = slash + 1;
  }
  return((char *)path);
}
