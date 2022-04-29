#pragma once
#include "../include/includes.h"

struct color_names_t *get_color_code_t_by_name(const char *rgb){
  struct color_names_t *cc;
  bool                 found = false;

  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    if (strcmp(rgb, COLOR_NAMES[i].rgb) == 0) {
      found = true;
      cc    = &(COLOR_NAMES[i]);
      return(cc);
    }
  }
  if (!found) {
    char *err = malloc(1024);
    sprintf(err, "Colorcode with rgb '%s' not found!", rgb);
    DO_DIE(err);
    exit(1);
  }
  return(cc);
}


char *get_color_code_log(const char *rgb){
  struct color_names_t *cc = get_color_code_t_by_name(rgb);

  assert(cc->encoded_log_bytes > 0);
  assert(cc->encoded_log);
  char *cclog = (char *)b64_decode(cc->encoded_log, cc->encoded_log_bytes);

  free(cclog);
  assert(strlen(cclog) > 0);
  return(cclog);
}


char *get_color_code_yourcolor(const char *rgb){
  struct StringBuffer *sb    = stringbuffer_new_with_options(1024, true);
  int                 added  = 0;
  char                *cclog = get_color_code_log(rgb);

  assert(cclog);
  assert(strlen(cclog) > 0);
  char **lines = malloc(1024 * 32);
  int  qty     = strsplit(cclog, lines, "\n");

  assert(qty > 0);
  for (int i = 0; i < qty; i++) {
    if (strlen(lines[i]) < 5) {
      continue;
    }
    size_t _colons = occurrences("<", lines[i]);
    size_t _pipes  = occurrences("=", lines[i]);
    if (_colons != 1 || _pipes != 2) {
      continue;
    }
    char **L = malloc(1024);
    int  lq  = strsplit(lines[i], L, "<");
    assert(lq > 0);
    stringbuffer_append_string(sb, L[0]);
  }
  assert(stringbuffer_is_empty(sb) != true);
  char *ret = trim(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}


char *get_color_code_attributes(const char *rgb){
  struct StringBuffer *sb    = stringbuffer_new_with_options(1024, true);
  int                 added  = 0;
  char                *cclog = get_color_code_log(rgb);

  assert(cclog);
  assert(strlen(cclog) > 0);
  char **lines = malloc(1024 * 32);
  int  qty     = strsplit(cclog, lines, "\n");

  assert(qty > 0);
  for (int i = 0; i < qty; i++) {
    if (strlen(lines[i]) < 5) {
      continue;
    }
    size_t _colons = occurrences(":", lines[i]);
    size_t _pipes  = occurrences("|", lines[i]);
    if (_colons != 1 || _pipes != 1) {
      continue;
    }
    stringbuffer_append_string(sb, lines[i]);
    stringbuffer_append_string(sb, "\n");
  }
  assert(stringbuffer_is_empty(sb) != true);
  char *ret = trim(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}


char *get_color_code_rgb_table(const char *rgb){
  struct StringBuffer *sb    = stringbuffer_new_with_options(1024, true);
  int                 added  = 0;
  char                *cclog = get_color_code_log(rgb);

  assert(cclog);
  assert(strlen(cclog) > 0);
  char **lines = malloc(1024 * 32);
  int  qty     = strsplit(cclog, lines, "\n");

  assert(qty > 0);
  for (int i = 0; i < qty; i++) {
    if (strlen(lines[i]) < 5) {
      continue;
    }
    size_t _colons = occurrences(":", lines[i]);
    size_t _pipes  = occurrences("|", lines[i]);
    if (_colons != 1 || _pipes != 2) {
      continue;
    }
    stringbuffer_append_string(sb, lines[i]);
    stringbuffer_append_string(sb, "\n");
  }
  assert(stringbuffer_is_empty(sb) != true);
  char *ret = trim(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(ret);
}

