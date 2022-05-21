#pragma once
#include <stdint.h>
////////////////////////////////////////////////
#include "../include/pman0-defines.h"
////////////////////////////////////////////////

typedef struct palette_t      palette_t;
typedef struct pman_mode_t    pman_mode_t;
typedef struct pman_args_t    pman_args_t;
///////////////////////////////////////////////////
#include "../include/includes.h"
////////////////////////////////////////////////
struct __pman_args_t {
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

#ifndef COLOR_NAME_STRUCT_DEFINED
#define COLOR_NAME_STRUCT_DEFINED 
typedef struct color_name_t {
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
} color_name_t;

typedef struct dev_color_name_t dev_color_name_t;
struct dev_color_name_t {
    unsigned long      id;
    uint32_t           red, green, blue, alpha;
    char               hex[7], name[32], path[256], encoded_path_contents[1024];
    bool               exists;
    size_t             path_size;
};
const size_t COLOR_NAMES_QTY = 0;
dev_color_name_t COLOR_NAMES[] = { };
#endif

void _change_terminal_color_fg(uint8_t r, uint8_t g, uint8_t b){
      wprintf(COLOR_FG_RGB, r, g, b);
}
void _change_terminal_color(uint8_t r, uint8_t g, uint8_t b){
      wprintf(COLOR_RGB, r, g, b);
}
void _reset_terminal_to_default_color() {
      wprintf(L"%ls", COLOR_RESET_TO_DEFAULT);
}
void _change_terminal_color_name_fg(color_name_t *cn){
    _change_terminal_color_fg(cn->red,cn->green,cn->blue);
}

void _change_terminal_color_name(color_name_t *cn){
    _change_terminal_color(cn->red,cn->green,cn->blue);
}
