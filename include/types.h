#pragma once
#include "../include/defines.h"
#include "../include/includes.h"

typedef struct palette_t      palette_t;
typedef struct color_name_t   color_name_t;
typedef struct pman_mode_t    pman_mode_t;
typedef struct pman_args_t    pman_args_t;

struct pman_args_t {
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
  char     *name;
  char     *rgb;
  char     *hex;
  uint32_t red;
  uint32_t green;
  uint32_t blue;
  uint32_t alpha;
  uint32_t rgba;
  char     *encoded_log;
  size_t   encoded_log_bytes;
};
