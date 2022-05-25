#pragma once
#ifndef COLOR_PARSER_MODULE_H
#define COLOR_PARSER_MODULE_H
#include "../include/includes.h"
#include "../module/def.h"
#include "../module/module.h"
#include "../module/require.h"
#include "./color_csv_parser0_includes.c"

enum colorcsvparser0_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
  LOGGER_TRACE,
};

#define colorcsvparser0_DEFAULT_LOGGER_MODE    LOGGER_DEBUG

module(colorcsvparser0) {
  define(colorcsvparser0, CLIB_MODULE);
  enum colorcsvparser0_mode    loggermode;
  struct djbhash *djb__hash;
 // int                     (*srcfile)(char *);
};

int  colorcsvparser0_init(module(colorcsvparser0) * exports);

void colorcsvparser0_deinit(module(colorcsvparser0) * exports);
exports(colorcsvparser0) {
  .loggermode = colorcsvparser0_DEFAULT_LOGGER_MODE,
  .init       = colorcsvparser0_init,
  .deinit     = colorcsvparser0_deinit,
};

#endif
