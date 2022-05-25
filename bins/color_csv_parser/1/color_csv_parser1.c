#ifndef COLOR_PARSER_MAIN
#define COLOR_PARSER_MAIN
////////////////////////////////////////////////////////////////////////
#include "../module/def.h"
#include "../module/module.h"
#include "../module/require.h"
#include "./color_csv_parser1_includes.c"


////////////////////////////////////////////////////////////////////////


int main(const int argc, const char **argv) {
  int r;

  r = init_parser_args(argc, argv);
  assert_eq(r, 0, %d);
  return(0);
  return(colorcsvparser1_modulemain(argc, argv));
}
#endif
