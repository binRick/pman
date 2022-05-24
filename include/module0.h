#pragma once
#include "../include/includes.h"

enum module0_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
};

module(module0) {
  define(module0, CLIB_MODULE);

  enum module0_mode mode;

  void              (*info)(char *);
  void              (*debug)(char *);
  void              (*error)(char *);
};

int  module0_init(module(module0) * exports);

void module0_deinit(module(module0) * exports);

exports(module0) {
  .mode   = LOGGER_NONE,
  .init   = module0_init,
  .deinit = module0_deinit,
};
