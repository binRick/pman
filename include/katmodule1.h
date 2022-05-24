#pragma once
#include "../include/includes.h"

struct ansilove_options katmodule1_default_options = {
  .dos       = false,
  .diz       = false,
  .truecolor = true,
  .icecolors = true,
};

enum katmodule1_mode {
  LOGGER_NONE,
  LOGGER_INFO,
  LOGGER_ERROR,
  LOGGER_DEBUG,
  LOGGER_TRACE,
};

#define katmodule1_DEFAULT_LOGGER_MODE    LOGGER_DEBUG

module(katmodule1) {
  define(katmodule1, CLIB_MODULE);

  enum katmodule1_mode    loggermode;
  long unsigned           max_width, max_content_width, content_width;

  char                    *src_dirname, *src_basename, *src_filename, *dst_filename;
  char                    *content, *highlighted_content;

  struct StringFNStrings  lines, highlighted_lines;
  struct StringBuffer     *sb;
  struct ansilove_options options;
  struct ansilove_ctx     *ctx;
  bool                    overwrite_dst_filename;

  int                     (*srcfile)(char *);
  int                     (*srccontent)(char *);
  int                     (*setcontent)(char *);
  int                     (*dstfile)(char *);
  int                     (*parsecontent)();
  int                     (*writepng)();
};

int  katmodule1_init(module(katmodule1) * exports);
void katmodule1_deinit(module(katmodule1) * exports);
exports(katmodule1) {
  .loggermode = katmodule1_DEFAULT_LOGGER_MODE,
  .init       = katmodule1_init,
  .deinit     = katmodule1_deinit,
};
