#pragma once
#include "../include/defines.h"

#define PALETTE_ITERATOR    void (*iterate_palettes)(**PALETTE_t)
#define PALETTE_PROPERTIES \
  char *filename;          \
  unsigned char *data;     \
  int           size;

typedef struct {
  const char *mode;
  const char *palette;
  const char *colorcode;
  bool       verbose;
} args_t;

typedef struct             mode_t {
  char *name;
  int (*fxn)();
};

typedef struct palette_t   palette_t;
struct palette_t {
  PALETTE_PROPERTIES
};

