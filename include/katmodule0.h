#pragma once
#include "../include/includes.h"

enum katmodule0_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
};

module(katmodule0) {
  define(katmodule0, CLIB_MODULE);

  enum katmodule0_mode mode;

  void              (*info)(char *);
  void              (*debug)(char *);
  void              (*error)(char *);
};

int  katmodule0_init(module(katmodule0) * exports);

void katmodule0_deinit(module(katmodule0) * exports);

exports(katmodule0) {
  .mode   = LOGGER_NONE,
  .init   = katmodule0_init,
  .deinit = katmodule0_deinit,
};
