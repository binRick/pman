#pragma once
#ifndef COLOR_PARSER_MODULE_SETUP
#define COLOR_PARSER_MODULE_SETUP
////////////////////////////////////////////////////////////
#include "./color_csv_parser1_module.h"
////////////////////////////////////////////////////////////
#ifdef M
#undef M
#endif
#define M    require(colorcsvparser1)
////////////////////////////////////////////////////////////


int colorcsvparser1_init(module(colorcsvparser1) *exports) {
  tq_start(NULL);
  fprintf(stderr, "colorcsvparser1> init\n");
  clib_module_init(colorcsvparser1, exports);
  exports->loggermode             = colorcsvparser1_DEFAULT_LOGGER_MODE;
  exports->dur_msg                = malloc(DEFAULT_BUFFER_SIZE);
  exports->split_csv_buffer_lines = malloc(DEFAULT_BUFFER_SIZE);
  exports->ro                     = malloc(sizeof(struct render_t));
  exports->parser_args            = malloc(sizeof(pman_args_t));
  return(0);
}


void colorcsvparser1_deinit(module(colorcsvparser1) *exports) {
  fprintf(stderr, "colorcsvparser1> deinit\n");
  clib_module_deinit(colorcsvparser1);
  char *dur = tq_stop("colorcsvparser1");

  dbg(dur, %s);
}


#undef M
#endif
