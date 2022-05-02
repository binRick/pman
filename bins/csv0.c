#include "../include/includes-pman.h"
// MESON_BIN_ENABLED=true
/***********************/
#include "../src/pman-init.c"
/***********************/
#define DEBUG_ARGUMENTS           false
/***********************/
#define DEFAULT_QTY_LIMIT         10
//#define MAX_QTY_LIMIT                     35000
#define MAX_QTY_LIMIT             100
#define VERBOSE_DEBUG_MODE        false
#define MAX_FILE_SIZE             128
#define PARSER_VERSION            "0.0.1"
#define MD5_LEN                   16
#define DEBUG_COLORS              false
#define DEFAULT_INPUT_FILE        "../etc/colornames.csv"
#define DEFAULT_OUTPUT_FILE       "/dev/null"
#define DEFAULT_COLORS_QTY        10
#define MAX_COLORS_QTY            100000
#define MAX_NAME_LENGTH           32
#define ANSI_TEMPLATE             "38;2;%u;%u;%u"
#define ANSI_TEMPLATE_PREFIX      "\033"
#define ANSI_TEMPLATE_SUFFIX      "m"
#define COLOR_RESET_TO_DEFAULT    L"\033[0m"
#define COLOR_NAME_T_STRUCT       "\
#include <stdio.h>\n\
#include <stdlib.h>\n\
typedef struct dev_color_name_t dev_color_name_t;\n\
struct dev_color_name_t {\n\
  unsigned long      id;\n\
  char               hex[7];\n\
  uint32_t           red, green, blue, alpha;\n\
  char               name[32];\n\
};"
/***********************/// ANSI Structs
/***********************/
//typedef struct pman_args_t       pman_args_t;
typedef struct render_t          render_t;
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
/***********************/
struct pman_args_t {
  FILE   *input_fd;
  char   *input_file, *output_file;
  bool   verbose_mode, test_mode;
  size_t colors_qty;
};
struct render_t {
  list_t       *unique_list;
  StringBuffer *out_buffer;
  size_t       in_bytes;
  int          in_exists;
  size_t       in_lines_qty;
  char         *in_content;
  long long    timestamp;
  Strings      InputLines;
  StringBuffer *Input;
};
/***********************/
render_t *ro; static pman_args_t *parser_args;


char *encoded_hash(const char *str){
  md5_ctx       ctx;
  unsigned char hash[MD5_LEN];

  rhash_md5_init(&ctx);
  rhash_md5_update(&ctx, (const unsigned char *)str, strlen(str));
  rhash_md5_final(&ctx, hash);
  char *encoded_md5 = (char *)b64_encode((const unsigned char *)hash, MD5_LEN);

  return(encoded_md5);
}


static void enable_verbose_mode() {
  parser_args->verbose_mode = true;
}


static void enable_test_mode(command_t *self){
  parser_args->test_mode = true;
}


static void set_colors_qty(command_t *self){
  parser_args->colors_qty = atoi(self->arg);
}


static void set_output_file(command_t *self){
  parser_args->output_file = strdup(self->arg);
}


static void set_input_file(command_t *self){
  if (strcmp(parser_args->input_file, "-") == 0) {
    parser_args->input_file = "STDIN";
    char buf[1024];
    while (fread(buf, 1, 1024, stdin) != 0) {
      printf("read:%s\n", buf);
    }
  }else{
    parser_args->input_file = strdup(self->arg);
    parser_args->input_fd   = fopen(parser_args->input_file, "r");
  }
}


////////////////////////////////////////////////////////////////////////
int init_parser_args(const int argc, const char **argv){
  if (parser_args != NULL) {
    return(0);
  }
  ro = malloc(sizeof(struct render_t));
  ////////////////////////////////////////////////////////////////
  ro->in_bytes   = 0;
  ro->in_content = malloc(1024 * 1024 * 4);
  ////////////////////////////////////////////////////////////////
  parser_args = malloc(sizeof(pman_args_t));
  ////////////////////////////////////////////////////////////////
  parser_args->test_mode    = false;
  parser_args->verbose_mode = false;
  parser_args->input_file   = malloc(MAX_FILE_SIZE);
  parser_args->output_file  = strdup(DEFAULT_OUTPUT_FILE);
  parser_args->colors_qty   = DEFAULT_COLORS_QTY;
  ////////////////////////////////////////////////////////////////
  sprintf(parser_args->input_file, "%s", DEFAULT_INPUT_FILE);
  ////////////////////////////////////////////////////////////////
  command_t cmd;

  command_init(&cmd, argv[0], PARSER_VERSION);
  command_option(&cmd, "-v", "--verbose", "Enable Verbose Mode", enable_verbose_mode);
  command_option(&cmd, "-T", "--test", "Enable Test Mode", enable_test_mode);
  command_option(&cmd, "-i", "--input-file  [in-file]", "Input Color File", set_input_file);
  command_option(&cmd, "-o", "--output-file  [out-file]", "Output Color File", set_output_file);
  command_option(&cmd, "-c", "--colors-qty  [colors-qty]", "Colors Quantity", set_colors_qty);
  command_parse(&cmd, argc, (char **)argv);
  ////////////////////////////////////////////////////////////////
  if (parser_args->verbose_mode) {
    fprintf(stderr, "Additional Args:\n");
    for (int i = 0; i < cmd.argc; ++i) {
      fprintf(stderr, "  - '%s'\n", cmd.argv[i]);
    }
  }
  command_free(&cmd);
  if (DEBUG_ARGUMENTS || parser_args->verbose_mode) {
    fprintf(stderr, "================================\n");
    fprintf(stderr, "Input File:             %s\n", parser_args->input_file);
    fprintf(stderr, "Output File:            %s\n", parser_args->output_file);
    fprintf(stderr, "Colors Quantity:        %lu\n", parser_args->colors_qty);
    fprintf(stderr, "Test mode Enabled?      %s\n", parser_args->test_mode    ? "Yes" : "No");
    fprintf(stderr, "Verbose Enabled?        %s\n", parser_args->verbose_mode ? "Yes" : "No");
    fprintf(stderr, "================================\n");
  }
  return(0);
} /* init_parser_args */


int main(const int argc, const char **argv) {
  size_t qty;
  char   *dur_msg = malloc(1024);
  short  prop_val_ok;
  char   **s = malloc(1024);

  tq_set_unit(tq_MILLISECONDS);
  tq_start(NULL);
  ////////////////////////////////////////////////////////
  assert_eq(init_parser_args(argc, argv), 0, %d);
  ////////////////////////////////////////////////////////
  ro->in_exists = (int)fs_exists(parser_args->input_file);
  assert_eq(ro->in_exists, 0, %d);

  ro->out_buffer  = stringbuffer_new_with_options(1024 * 1024, true);
  ro->unique_list = list_new();
  ro->in_bytes    = fs_size(parser_args->input_file);
  assert_ge(ro->in_bytes, 10, %lu);
  ro->in_content = (char *)fs_read(parser_args->input_file);
  ro->in_bytes   = (size_t)strlen(ro->in_content);
  ro->InputLines = stringfn_split_lines_and_trim(ro->in_content);
  assert_ge(ro->InputLines.count, 1, %d);
  stringbuffer_append_string(ro->out_buffer, COLOR_NAME_T_STRUCT);
  stringbuffer_append_string(ro->out_buffer, "\n#ifndef DEV_COLOR_NAME_STRUCT_DEFINED\n#define DEV_COLOR_NAME_STRUCT_DEFINED\n");
  stringbuffer_append_string(ro->out_buffer, "dev_color_name_t COLOR_NAMES[] = {\n");

  for (int i = 0; (i < ro->InputLines.count) && (i <= parser_args->colors_qty) && (i <= MAX_COLORS_QTY); i++) {
    if (strlen(ro->InputLines.strings[i]) < 3) {
      continue;
    }
    int _qty = strsplit(ro->InputLines.strings[i], s, ",");
    if (_qty != 2) {
      continue;
    }
    color_name_t *cn = malloc(sizeof(color_name_t));
    cn->name = trim(s[0]);
    cn->hex  = case_upper(trim(s[1]));

    if (strlen(cn->name) < 3 || strlen(cn->hex) != 7) {
      continue;
    }
    uint32_t _rgba = rgba_from_string(cn->hex, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t   prop_val_rgba = rgba_new(_rgba);
    cn->red               = (uint32_t)_rgba >> 24 & 0xff;
    cn->green             = (uint32_t)_rgba >> 16 & 0xff;
    cn->blue              = (uint32_t)_rgba >> 8 & 0xff;
    cn->alpha             = (uint32_t)_rgba & 0xff;
    cn->ansi              = malloc(1024);
    cn->encoded_ansi_code = malloc(1024);
    char *encoded_ansi_code = malloc(1024);
    if (cn->red < 0 || cn->red > 256) {
      continue;
    }
    if (cn->green < 0 || cn->green > 256) {
      continue;
    }
    if (cn->blue < 0 || cn->blue > 256) {
      continue;
    }
    if (cn->alpha < 0 || cn->alpha > 256) {
      continue;
    }
    sprintf(cn->ansi, ANSI_TEMPLATE, cn->red, cn->green, cn->blue);
    sprintf(encoded_ansi_code, "%s%s%s", ANSI_TEMPLATE_PREFIX, cn->ansi, ANSI_TEMPLATE_SUFFIX);
    sprintf(cn->encoded_ansi_code, "%s", (char *)b64_encode((const unsigned char *)encoded_ansi_code, strlen(encoded_ansi_code)));

    list_node_t     *item = list_node_new(cn->hex);
    list_node_t     *node;
    bool            found = false;
    list_iterator_t *it   = list_iterator_new(ro->unique_list, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
      if (strcmp(cn->hex, (char *)node->val) == 0) {
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }
    list_lpush(ro->unique_list, item);
    list_iterator_destroy(it);

    char *__dat = malloc(1024 * 2);

    sprintf(
      __dat,
      "  "
      "{ "
      ".id = %lu, "
      ".hex = \"%s\", "
      ".red = %d, .green = %d, .blue = %d, .alpha = %d, "
      ".name = \"%.32s\", "
      "},\n",
      qty,
      cn->hex,
      cn->red,
      cn->green,
      cn->blue,
      cn->alpha,
      cn->name
      );
    stringbuffer_append_string(ro->out_buffer, __dat);
    if (parser_args->verbose_mode) {
      _change_terminal_color_name(cn);
      fprintf(stdout, "%s", __dat);
      _reset_terminal_to_default_color();
    }

    free(__dat);
    qty++;
    if (qty >= ro->InputLines.count) {
      break;
    }
  }
  char *dur = tq_stop("Duration");

  stringbuffer_append_string(ro->out_buffer, "};\nconst size_t COLOR_NAMES_QTY = ");
  stringbuffer_append_int(ro->out_buffer, qty);
  stringbuffer_append_string(ro->out_buffer, ";\n");
  stringbuffer_append_string(ro->out_buffer, "#endif\n");
  fs_write(parser_args->output_file, stringbuffer_to_string(ro->out_buffer));

  sprintf(dur_msg,
          "Processed %lu Colors from %lu byte file with %d lines :: %s"
          "\nWrote %lu bytes to %s",
          qty,
          ro->in_bytes,
          ro->InputLines.count,
          dur,
          stringbuffer_get_content_size(ro->out_buffer),
          parser_args->output_file
          );
  OK(dur_msg);
  return(0);
} /* main */

