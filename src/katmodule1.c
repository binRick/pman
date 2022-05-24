#pragma once
#include "../include/includes.h"
#include "../include/katmodule1.h"
////////////////////////////////////////////////////////////
#define katmodule1_MAX_CONTENT_BYTES    1024 * 1024
#define katmodule1_DEFAULT_MAX_WIDTH    40
#define katmodule1_MIN_WIDTH            40
#define KM1                             require(katmodule1)


////////////////////////////////////////////////////////////
static inline int katmodule1_srccontent(char *content) {
  fprintf(stdout, "src content: %s\n", content);
  return(0);
}


static inline int katmodule1_writepng() {
  int r;

  assert_nonnull(KM1->dst_filename);
  assert_ge(strlen(KM1->dst_filename), 3, %lu);
  assert_eq(fsio_file_exists(KM1->dst_filename), 0, %d);

  assert_ge(strlen(KM1->highlighted_content), 1, %lu);
  assert_ge(strlen(KM1->highlighted_content), strlen(KM1->content), %lu);

  //KM1->max_content_width;
  //(KM1->max_width >= katmodule1_MIN_WIDTH) ? KM1->max_width : KM1->max_content_width;
  //assert_ge(KM1->options.columns, katmodule1_MIN_WIDTH, %d);

  r = ansilove_init(KM1->ctx, &(KM1->options));
  assert_eq(r, 0, %d);

  //KM1->options.columns = 140;
  KM1->options.columns   = KM1->max_content_width + 2;
  KM1->options.mode      = katmodule1_default_options.mode;
  KM1->options.truecolor = katmodule1_default_options.truecolor;
  //KM1->options.scale_factor = 4;
  KM1->options.dos       = katmodule1_default_options.dos;
  KM1->options.diz       = katmodule1_default_options.diz;
  KM1->options.font      = katmodule1_default_options.font;
  KM1->options.icecolors = katmodule1_default_options.icecolors;


  KM1->ctx->maplen = KM1->ctx->length = strlen(KM1->highlighted_content);
  KM1->ctx->buffer = (uint8_t *)KM1->highlighted_content;
  assert_eq(strlen((char *)KM1->ctx->buffer), strlen(KM1->highlighted_content), %lu);

  r = ansilove_ansi(KM1->ctx, &(KM1->options));
  assert_eq(r, 0, %d);

  r = ansilove_savefile(KM1->ctx, KM1->dst_filename);
  assert_eq(r, 0, %d);

  size_t dst_file_size = fs_size(KM1->dst_filename);

  assert_ge(dst_file_size, 0, %lu);

  ansilove_clean(KM1->ctx);

  return(r);
} /* katmodule1_writepng */


static inline int katmodule1_highlightcontent() {
  int  r;
  char *line = highlight_alloc_line();

  assert_nonnull(line);
  assert_ge(KM1->lines.count, 0, %d);

  for (int i = 0; i < KM1->lines.count; i++) {
    if (strlen(KM1->lines.strings[i]) > KM1->max_content_width) {
      KM1->max_content_width = strlen(KM1->lines.strings[i]);
    }

    line = highlight_line(KM1->lines.strings[i], line, strlen(KM1->lines.strings[i]));
    stringbuffer_append_string(KM1->sb, line);
    if (i <= KM1->lines.count - 2) {
      stringbuffer_append_string(KM1->sb, "\n");
    }
  }
  //KM1->content_width = (KM1->max_width >= katmodule1_MIN_WIDTH) ? KM1->max_width : KM1->max_content_width;
  KM1->content_width = KM1->max_content_width;
  assert_ge(KM1->content_width, katmodule1_MIN_WIDTH, %lu);

  if (line) {
    highlight_free(line);
  }
  highlight_finish();

  KM1->highlighted_content = stringbuffer_to_string(KM1->sb);
  assert_ge(strlen(KM1->highlighted_content), strlen(KM1->content), %lu);

  KM1->highlighted_lines = stringfn_split_lines(KM1->content);
  assert_eq(KM1->highlighted_lines.count, KM1->lines.count, %d);

  return(0);
}


static inline int katmodule1_parsecontent() {
  int r;

  assert_nonnull(KM1->content);


  require(katmodule1)->lines = stringfn_split_lines(require(katmodule1)->content);
  assert_ge(KM1->lines.count, 0, %d);

  r = katmodule1_highlightcontent();
  assert_eq(r, 0, %d);

  return(r);
}


static inline int katmodule1_setcontent(char *content){
  assert_ge(strlen(content), 1, %lu);
  require(katmodule1)->content = strdup(content);
  assert_ge(strlen(require(katmodule1)->content), 1, %lu);
  return(0);
}


static inline int katmodule1_dstfile(char *path) {
  if (KM1->overwrite_dst_filename && fsio_file_exists(path)) {
    fprintf(stderr, AC_RESETALL AC_RED_BLACK AC_BOLD "Removing %s\n" AC_RESETALL, path);
    unlink(path);
  }
  assert_eq(fsio_file_exists(path), 0, %d);
  KM1->dst_filename = malloc(sizeof(path) + 1);
  sprintf(KM1->dst_filename, "%s", path);
  return(0);
}


static inline int katmodule1_srcfile(char *path) {
  int r;

  assert_eq(fsio_file_exists(path), 1, %d);

  require(katmodule1)->src_filename = strdup(path);
  require(katmodule1)->content      = fsio_read_text_file(path);
  assert_ge(strlen(require(katmodule1)->content), 10, %lu);


  return(0);
}


int katmodule1_init(module(katmodule1) *exports) {
  tq_start(NULL);
  fprintf(stderr, "katmodule1> init\n");
  clib_module_init(katmodule1, exports);

  exports->loggermode = katmodule1_DEFAULT_LOGGER_MODE;

  exports->content                = NULL;
  exports->highlighted_content    = NULL;
  exports->overwrite_dst_filename = false;

  exports->setcontent        = katmodule1_setcontent;
  exports->srccontent        = katmodule1_srccontent;
  exports->options           = katmodule1_default_options;
  exports->content           = malloc(katmodule1_MAX_CONTENT_BYTES);
  exports->sb                = stringbuffer_new_with_options(1024, true);
  exports->content_width     = 0;
  exports->max_width         = 0;
  exports->max_content_width = 0;
  exports->ctx               = malloc(sizeof(struct ansilove_ctx));

  exports->srcfile      = katmodule1_srcfile;
  exports->dstfile      = katmodule1_dstfile;
  exports->parsecontent = katmodule1_parsecontent;
  exports->writepng     = katmodule1_writepng;
  return(0);
}


void katmodule1_deinit(module(katmodule1) *exports) {
  fprintf(stderr, "katmodule1> deinit\n");

  stringbuffer_release(KM1->sb);

  if (KM1->ctx) {
    free(KM1->ctx);
  }

  if (KM1->content) {
    free(KM1->content);
  }

  clib_module_deinit(katmodule1);

  char *dur = tq_stop("katmodule1");

  dbg(dur, %s);
}

