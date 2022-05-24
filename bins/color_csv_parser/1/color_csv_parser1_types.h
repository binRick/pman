#pragma once
#ifndef COLOR_PARSER_TYPES
#define COLOR_PARSER_TYPES
////////////////////////////////////////////////////////////////
#include "../include/includes.h"
////////////////////////////////////////////////////////////////
int colorcsvparser1_clean();
int colorcsvparser1_work();
int colorcsvparser1_logicinit();
int colorcsvparser1_modulemain(const int argc, const char **argv);
void colorcsvparser1_debug();
////////////////////////////////////////////////////////////////
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
////////////////////////////////////////////////////////////////
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
enum colorcsvparser1_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
  LOGGER_TRACE,
};
////////////////////////////////////////////////////////////////
#endif
