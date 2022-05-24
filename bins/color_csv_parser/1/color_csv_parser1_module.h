#pragma once
#ifndef COLOR_PARSER_MODULE_H
#define COLOR_PARSER_MODULE_H
///////////////////////////////////////////
#include "./color_csv_parser1_includes.c"
///////////////////////////////////////////
module(colorcsvparser1) {
  define(colorcsvparser1, CLIB_MODULE);
  enum colorcsvparser1_mode    loggermode;
  struct djbhash *djb__hash;
  char *dur_msg;
  char **split_csv_buffer_lines;
  command_t cmd;
  render_t    *ro;
  pman_args_t *parser_args;
  char *test_main;
};
///////////////////////////////////////////
int  colorcsvparser1_init(module(colorcsvparser1) * exports);
///////////////////////////////////////////
void colorcsvparser1_deinit(module(colorcsvparser1) * exports);
exports(colorcsvparser1) {
  .loggermode = colorcsvparser1_DEFAULT_LOGGER_MODE,
  .init       = colorcsvparser1_init,
  .deinit     = colorcsvparser1_deinit,
};
///////////////////////////////////////////

#endif
