#pragma once
#ifndef COLOR_PARSER_DEFINES
#define COLOR_PARSER_DEFINES
////////////////////////////////////////////////////////////////
#include "../include/includes.h"
////////////////////////////////////////////////////////////////
#define colorcsvparser1_DEFAULT_LOGGER_MODE    LOGGER_DEBUG
#define VERBOSE             true
////////////////////////////////////////////////////////////////
#define DEFAULT_QTY_LIMIT             10
#define DEFAULT_VERBOSE_MODE          false
#define DEFAULT_TEST_MODE             false
#define DEFAULT_COLORS_QTY            10
#define DEFAULT_BUFFER_SIZE           1024
#define DEFAULT_INPUT_FILE            "../etc/colornames.csv"
#define DEFAULT_OUTPUT_FILE           "/dev/null"
////////////////////////////////////////////////////////////////
#define COLOR_IMAGE_PATH_TEMPLATE     "../ansi/pngs/color-resized-%u-%u-%u-40x20.png"
#define DEBUG_ARGUMENTS               false
#define PARSER_VERSION                "0.0.1"
////////////////////////////////////////////////////////////////
#define MAX_COLORS_QTY                100000
////////////////////////////////////////////////////////////////
#define RGB_MIN_VAL                   0
#define RGB_MAX_VAL                   256
////////////////////////////////////////////////////////////////
#define ANSI_TEMPLATE                 "38;2;%u;%u;%u"
#define ANSI_TEMPLATE_PREFIX          "\033"
#define ANSI_TEMPLATE_SUFFIX          "m"
////////////////////////////////////////////////////////////////
#define PREVIEW_COLOR_FG_RED          0
#define PREVIEW_COLOR_FG_GREEN        0
#define PREVIEW_COLOR_FG_BLUE         0
////////////////////////////////////////////////////////////////
#define CSV_HEX_FIELD_OFFSET          1
#define CSV_NAME_FIELD_OFFSET         1
#define CSV_INPUT_FIELDS_QTY     2
////////////////////////////////////////////////////////////////
#define MAX_INPUT_FILE_NAME_LEN       128
#define MIN_INPUT_FILE_SIZE           10
#define MIN_INPUT_FILE_LINES          1
////////////////////////////////////////////////////////////////
#define MAX_OUTPUT_COLOR_ITEM_SIZE    1024 * 2
////////////////////////////////////////////////////////////////
/***********************/
#ifdef HEX_LEN
#undef HEX_LEN
#endif
#define HEX_LEN                          7
#define MIN_COLOR_NAME_LEN               3
////////////////////////////////////////////////////////////////
#define COLOR_NAME_T_STRUCT_TEST_MAIN    "\
int test_color_sizes(const int argc, const char **argv) {\n\
    printf(\"|%zu Colors|%zu Color Content Bytes|\\n\"\n\
    ¦   ¦   , COLOR_NAMES_QTY\n\
    ¦   ¦   , COLOR_NAMES_PATH_SIZES\n\
    ¦   ¦ );\n\
    return(0);\n\
}\n\
" 
#define COLOR_NAME_T_STRUCT_PREFIX       "\
#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <stdbool.h>\n\n\
" 
#define COLOR_NAME_T_STRUCT              "\
typedef struct color_name_t {\n\
  unsigned long      id;\n\
  char               hex[8], name[64];\n\
  uint32_t           red, green, blue, alpha;\n\
  bool               exists;\n\
  size_t             path_size;\n\
  char               path[256], encoded_path_contents[1024];\n\
} color_name_t;\n\n"
////////////////////////////////////////////////////////////////
#endif
