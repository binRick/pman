#pragma once
#include "../src/includes.c"


int debug_args(){
  printf("\n");
  printf(AC_RESETALL "            Mode:    %s" "\n", args->mode);
  printf(AC_RESETALL "    Verbose Mode:    %s" "\n", args->verbose ? "Yes" : "No");
  printf(AC_RESETALL "         Palette:    %s" "\n", args->palette);
  printf(AC_RESETALL "           Color:    %s" "\n", args->colorcode);
  printf("\n");
  return(0);
}


int pman_args(int argc, const char **argv) {
  flag_str(&args->mode, "mode", "Mode");
  flag_bool(&args->verbose, "verbose", "Verbose Mode");
  flag_str(&args->palette, "palette", "Palette");
  flag_str(&args->colorcode, "colorcode", "Color Code");
  flag_parse(argc, argv, VERSION);
  return(0);
}

