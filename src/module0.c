#pragma once
#include "../include/includes.h"
#include "../include/module0.h"


static inline void module0_info(char *message) {
  if (require(module0)->mode >= LOGGER_INFO) {
    fprintf(stdout, " info: %s\n", message);
  }
}


static inline void module0_error(char *message) {
  if (require(module0)->mode >= LOGGER_ERROR) {
    fprintf(stderr, "error: %s\n", message);
  }
}


static inline void module0_debug(char *message) {
  if (require(module0)->mode >= LOGGER_DEBUG) {
    fprintf(stderr, "debug: %s\n", message);
  }
}


int module0_init(module(module0) *exports) {
  clib_module_init(module0, exports);
  exports->mode  = LOGGER_NONE;
  exports->info  = module0_info;
  exports->error = module0_error;
  exports->debug = module0_debug;
  return(0);
}


void module0_deinit(module(module0) *exports) {
  clib_module_deinit(module0);
}

