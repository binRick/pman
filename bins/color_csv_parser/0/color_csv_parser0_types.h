#pragma once
#ifndef COLOR_PARSER_TYPES
#define COLOR_PARSER_TYPES
////////////////////////////////////////////////////////////////
int colorcsvparser0_clean();
int colorcsvparser0_work();
int colorcsvparser0_logicinit();
int colorcsvparser0_modulemain(const int argc, const char **argv);
void colorcsvparser0_debug();
////////////////////////////////////////////////////////////////
#include "../include/includes-pman.h"
#include "../src/pman-init.c"
#include "./color_csv_parser0_types.h"
////////////////////////////////////////////////////////////////
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
/***********************/
struct pman_args_t { 
  char   *input_file, *output_file;
  bool   verbose_mode, test_mode;
  size_t max_colors_qty;
};
typedef struct render_t { 
  StringBuffer *OutputBuffer;
  StringBuffer *InputBuffer;
  Strings      InputLines;
  size_t       processed_colors_qty;
  size_t       input_buffer_bytes;
  int          input_file_exists;
  size_t       path_size_sum;
} render_t;
////////////////////////////////////////////////////////////////
#endif
