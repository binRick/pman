// MESON_BIN_ENABLED=true
#include "../include/includes-pman.h"
#include "../src/pman-init.c"
/***********************/
#define COLOR_IMAGE_PATH_TEMPLATE        "../../ansi/pngs/color-resized-%u-%u-%u-40x20.png"
#define DEBUG_ARGUMENTS                  false
#define DEFAULT_QTY_LIMIT                10
#define MAX_QTY_LIMIT                    100
#define VERBOSE_DEBUG_MODE               false
#define MAX_FILE_SIZE                    128
#define PARSER_VERSION                   "0.0.1"
#define MD5_LEN                          16
#define DEBUG_COLORS                     false
#define DEFAULT_INPUT_FILE               "../etc/colornames.csv"
#define DEFAULT_OUTPUT_FILE              "/dev/null"
#define DEFAULT_COLORS_QTY               10
#define MAX_COLORS_QTY                   100000
#define MAX_NAME_LENGTH                  32
#define ANSI_TEMPLATE                    "38;2;%u;%u;%u"
#define ANSI_TEMPLATE_PREFIX             "\033"
#define ANSI_TEMPLATE_SUFFIX             "m"
#define COLOR_RESET_TO_DEFAULT           L"\033[0m"
/***********************/
#define COLOR_NAME_T_STRUCT_TEST_MAIN    "\
int main(const int argc, const char **argv) {\n\
    printf(\"|%zu Colors|%zu Color Content Bytes|\\n\"\
            , COLOR_NAMES_QTY\n\
            , COLOR_NAMES_PATH_SIZES\n\
          );\n\
}\n\
"
#define COLOR_NAME_T_STRUCT              "\
#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <stdbool.h>\n\
\#ifndef COLOR_NAME_STRUCT_DEFINED\n\
#define COLOR_NAME_STRUCT_DEFINED\n\
typedef struct color_name_t {\n\
  unsigned long      id;\n\
  uint32_t           red, green, blue, alpha;\n\
  bool               exists;\n\
  size_t             path_size;\n\
  char               hex[7], name[64], path[256], encoded_path_contents[1024];\n\
} color_name_t;\n"
/***********************/// ANSI Structs
typedef struct test_struct {
  int a;
  int b;
} test_struct;
/***********************/
typedef struct render_t          render_t;
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
const char *test_main = COLOR_NAME_T_STRUCT_TEST_MAIN;
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
  size_t       processed_qty;
  size_t       in_bytes;
  int          in_exists;
  size_t       in_lines_qty;
  char         *in_content;
  long long    timestamp;
  Strings      InputLines;
  StringBuffer *Input;
};
test_struct         *test0;
struct djbhash_node *item;
/***********************/
render_t            *ro; static pman_args_t *parser_args;


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
  ////////////////////////////////////////////////////////////////
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
  assert_eq(init_parser_args(argc, argv), 0, %d);
  tq_set_unit(tq_MILLISECONDS);
  tq_start(NULL);
  ////////////////////////////////////////////////////////////////
  struct djbhash *djb__hash;

  djb__hash = malloc(sizeof(struct djbhash));
  djbhash_init(djb__hash);
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  char *dur_msg = malloc(1024), **s = malloc(1024); short prop_val_ok; unsigned long path_size_sum = 0;

  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  ro->unique_list = list_new();
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  ro->in_exists = (int)fs_exists(parser_args->input_file);
  assert_eq(ro->in_exists, 0, %d);
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  ro->out_buffer = stringbuffer_new_with_options(1024 * 1024, true);
  ro->in_bytes   = fs_size(parser_args->input_file);
  assert_ge(ro->in_bytes, 10, %lu);
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  ro->in_content = (char *)fs_read(parser_args->input_file);
  ro->in_bytes   = (size_t)strlen(ro->in_content);
  ro->InputLines = stringfn_split_lines_and_trim(ro->in_content);
  assert_ge(ro->InputLines.count, 1, %d);
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->out_buffer, COLOR_NAME_T_STRUCT);
  stringbuffer_append_string(ro->out_buffer, "color_name_t COLOR_NAMES[] = {\n");
  ////////////////////////////////////////////////////////


  for (int i = 0; (i < ro->InputLines.count) && (ro->processed_qty < parser_args->colors_qty) && (ro->processed_qty <= MAX_COLORS_QTY); i++) {
    ro->processed_qty++;

    if (strlen(ro->InputLines.strings[i]) < 3 || strsplit(ro->InputLines.strings[i], s, ",") != 2) {
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

    rgba_t prop_val_rgba = rgba_new(_rgba);
    cn->red               = (uint32_t)_rgba >> 24 & 0xff;
    cn->green             = (uint32_t)_rgba >> 16 & 0xff;
    cn->blue              = (uint32_t)_rgba >> 8 & 0xff;
    cn->alpha             = (uint32_t)_rgba & 0xff;
    cn->ansi              = malloc(1024);
    cn->encoded_ansi_code = malloc(1024);
    char *encoded_ansi_code = malloc(1024);

    if (cn->red < 0 || cn->red > 256 || cn->green < 0 || cn->green > 256 || cn->blue < 0 || cn->blue > 256 || cn->alpha < 0 || cn->alpha > 256) {
      continue;
    }

    sprintf(cn->ansi, ANSI_TEMPLATE, cn->red, cn->green, cn->blue);
    sprintf(encoded_ansi_code, "%s%s%s", ANSI_TEMPLATE_PREFIX, cn->ansi, ANSI_TEMPLATE_SUFFIX);
    sprintf(cn->encoded_ansi_code, "%s", (char *)b64_encode((const unsigned char *)encoded_ansi_code, strlen(encoded_ansi_code)));

    list_node_t *item = list_node_new(cn->hex);
    list_node_t *node;
    tq_start(NULL);

    if (djbhash_find(djb__hash, cn->hex) != NULL) {
      continue;
    }

    djbhash_set(djb__hash, cn->hex, item, DJBHASH_OTHER);


    char *PATH = malloc(1024 * 2);

    sprintf(PATH, COLOR_IMAGE_PATH_TEMPLATE,
            cn->red, cn->green, cn->blue
            );

    bool exists = (bool)((fs_exists(PATH) == 0) ? true : false);

    if (!exists) {
      continue;
    }

    size_t path_size = (size_t)(exists ? fs_size(PATH) : 0);
    path_size_sum += path_size;
    char   *encoded_path_contents = (char *)(b64_encode((const unsigned char *)fsio_read_binary_file(PATH), path_size));


    char *__dat = malloc(1024 * 2);
    sprintf(
      __dat,
      "  "
      "{ "
      ".id = %lu, "
      ".hex = \"%s\", "
      ".red = %d, .green = %d, .blue = %d, .alpha = %d, "
      ".name = \"%.32s\", "
      ".path = \"%s\", "
      ".exists = %d, "
      ".path_size = %lu, "
      ".encoded_path_contents = \"%s\", "
      "},\n",
      ro->processed_qty,
      cn->hex,
      cn->red,
      cn->green,
      cn->blue,
      cn->alpha,
      cn->name,
      PATH,
      exists,
      path_size,
      encoded_path_contents
      );

    stringbuffer_append_string(ro->out_buffer, __dat);

    if (parser_args->verbose_mode) {
      _reset_terminal_to_default_color();
      _change_terminal_color_name(cn);
      _change_terminal_color_fg(0, 0, 0);
      fprintf(stdout, "%s", __dat);
      _reset_terminal_to_default_color();
    }

    free(__dat);
  }
  char *dur = tq_stop("Duration");

  stringbuffer_append_string(ro->out_buffer, "};\nconst size_t COLOR_NAMES_QTY = ");
  stringbuffer_append_unsigned_long(ro->out_buffer, ro->processed_qty);
  stringbuffer_append_string(ro->out_buffer, ";\n");

  stringbuffer_append_string(ro->out_buffer, "const size_t COLOR_NAMES_PATH_SIZES = ");
  stringbuffer_append_unsigned_long(ro->out_buffer, path_size_sum);
  stringbuffer_append_string(ro->out_buffer, ";\n");

  if (parser_args->test_mode) {
    stringbuffer_append_string(ro->out_buffer, "\n//TEST MODE ENABLED\n");
    stringbuffer_append_string(ro->out_buffer, (char *)test_main);
    stringbuffer_append_string(ro->out_buffer, "\n");
  }else{
    stringbuffer_append_string(ro->out_buffer, "//TEST MODE DISABLED\n");
  }
  stringbuffer_append_string(ro->out_buffer, "#endif\n");

  fs_write(parser_args->output_file, stringbuffer_to_string(ro->out_buffer));

  sprintf(dur_msg,
          "Processed %lu Colors from %lu byte file with %d lines :: %s"
          "\nWrote %lu bytes to %s",
          ro->processed_qty,
          ro->in_bytes,
          ro->InputLines.count,
          dur,
          stringbuffer_get_content_size(ro->out_buffer),
          parser_args->output_file
          );
  OK(dur_msg);
  return(0);
} /* main */

