#pragma once
#ifndef COLOR_PARSER_MODULE_SETUP
#define COLOR_PARSER_MODULE_SETUP
////////////////////////////////////////////////////////////
#include "./color_csv_parser0_module.h"
////////////////////////////////////////////////////////////
#define M    require(colorcsvparser0)
////////////////////////////////////////////////////////////


int colorcsvparser0_init(module(colorcsvparser0) *exports) {
  tq_start(NULL);
  fprintf(stderr, "colorcsvparser0> init\n");
  clib_module_init(colorcsvparser0, exports);
  exports->loggermode = colorcsvparser0_DEFAULT_LOGGER_MODE;
  return(0);
}


void colorcsvparser0_deinit(module(colorcsvparser0) *exports) {
  fprintf(stderr, "colorcsvparser0> deinit\n");
  clib_module_deinit(colorcsvparser0);
  char *dur = tq_stop("colorcsvparser0");

  dbg(dur, %s);
}


#endif
