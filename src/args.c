#ifndef __KFC_ARGS_C
#define __KFC_ARGS_C

#include "../include/includes.h"
#include "../src/globals.c"


int debug_args(){
  printf("\n");
  printf(AC_RESETALL "            Mode:    %s" "\n", args->mode);
  printf(AC_RESETALL "    Verbose Mode:    %s" "\n", args->verbose ? "Yes" : "No");
  printf(AC_RESETALL "         Palette:    %s" "\n", args->palette);
  printf("\n");
  return(0);
}


int pman_args(int argc, const char **argv) {
  flag_str(&args->mode, "mode", "Mode");
  flag_bool(&args->verbose, "verbose", "Verbose Mode");
  flag_str(&args->palette, "palette", "Palette");
  flag_parse(argc, argv, VERSION);

  return(0);
}


#endif
