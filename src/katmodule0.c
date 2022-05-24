#pragma once
#include "../include/includes.h"
#include "../include/katmodule0.h"


static inline void katmodule0_info(char *message) {
  if (require(katmodule0)->mode >= LOGGER_INFO) {
    fprintf(stdout, " info: %s\n", message);
  }
}


static inline void katmodule0_error(char *message) {
  if (require(katmodule0)->mode >= LOGGER_ERROR) {
    fprintf(stderr, "error: %s\n", message);
  }
}


static inline void katmodule0_debug(char *message) {
  if (require(katmodule0)->mode >= LOGGER_DEBUG) {
    fprintf(stderr, "debug: %s\n", message);
  }
}


int katmodule0_init(module(katmodule0) *exports) {
  clib_module_init(katmodule0, exports);
  exports->mode  = LOGGER_NONE;
  exports->info  = katmodule0_info;
  exports->error = katmodule0_error;
  exports->debug = katmodule0_debug;
  return(0);
}


void katmodule0_deinit(module(katmodule0) *exports) {
  clib_module_deinit(katmodule0);
}

