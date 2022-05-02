#pragma once
#include <stdint.h>
////////////////////////////////////////////////
#include "../include/pman0-defines.h"
////////////////////////////////////////////////

typedef struct palette_t      palette_t;
typedef struct color_name_t   color_name_t;
typedef struct pman_mode_t    pman_mode_t;
typedef struct pman_args_t    pman_args_t;
///////////////////////////////////////////////////
#include "../include/includes.h"
////////////////////////////////////////////////
struct _pman_args_t {
  const char *mode;
  const char *palette;
  const char *colorcode;
  bool       verbose;
};

struct pman_mode_t {
  char *name;
  int  (*fxn)();
};

struct palette_t {
  char          *filename;
  unsigned char *data;
  int           size;
};

struct color_name_t {
  char               *name;
  char               *rgb;
  char               *hex;
  uint32_t           red;
  uint32_t           green;
  uint32_t           blue;
  uint32_t           alpha;
  unsigned long long rgba;
  char               *encoded_log;
  size_t             encoded_log_bytes;
  char               *unique;
  char               *ansi;
  char               *encoded_ansi_code;
};

#ifndef DEV_COLOR_NAME_STRUCT_DEFINED
#define DEV_COLOR_NAME_STRUCT_DEFINED
typedef struct _dev_color_name_t _dev_color_name_t;
struct _dev_color_name_t {
    unsigned long      id;
    char               hex[7];
    uint32_t           red, green, blue, alpha;
    char               name[32];
};
#endif

void _change_terminal_color(uint8_t r, uint8_t g, uint8_t b){
      wprintf(COLOR_RGB, r, g, b);
}
void _reset_terminal_to_default_color() {
      wprintf(L"%ls", COLOR_RESET_TO_DEFAULT);
}
void _change_terminal_color_name(_dev_color_name_t *cn){
    _change_terminal_color(cn->red,cn->green,cn->blue);
}
