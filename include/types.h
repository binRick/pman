#ifndef __KFC_TYPES_H__
#define __KFC_TYPES_H__
#include "../include/defines.h"

#define palette_iterator    void (*iterate_palettes)(**PALETTE_t)
#define PALETTE_PROPERTIES \
  char *filename;          \
  unsigned char *data;     \
  int           size;

typedef struct {
  const char *mode;
  const char *palette;
  bool       verbose;
} args_t;

struct mode_t {
  char *name;
  int  (*fxn)();
};

typedef struct PALETTE_t PALETTE_t;
struct PALETTE_t {
  PALETTE_PROPERTIES
};

#endif
