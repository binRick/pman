// MESON_BIN_ENABLED=true
#include "../include/includes-pman.h"
#include "../src/pman-init.c"
/***********************/
#define DEFAULT_QTY_LIMIT             10
#define DEFAULT_VERBOSE_MODE          false
#define DEFAULT_TEST_MODE             false
#define DEFAULT_COLORS_QTY            10
#define DEFAULT_BUFFER_SIZE           1024
#define DEFAULT_INPUT_FILE            "../etc/colornames.csv"
#define DEFAULT_OUTPUT_FILE           "/dev/null"
////////////////////////////////////////////////////////////////
#define COLOR_IMAGE_PATH_TEMPLATE     "../ansi/pngs/color-resized-%u-%u-%u-40x20.png"
#define DEBUG_ARGUMENTS               false
#define PARSER_VERSION                "0.0.1"
////////////////////////////////////////////////////////////////
#define MAX_COLORS_QTY                100000
////////////////////////////////////////////////////////////////
#define RGB_MIN_VAL                   0
#define RGB_MAX_VAL                   256
////////////////////////////////////////////////////////////////
#define ANSI_TEMPLATE                 "38;2;%u;%u;%u"
#define ANSI_TEMPLATE_PREFIX          "\033"
#define ANSI_TEMPLATE_SUFFIX          "m"
////////////////////////////////////////////////////////////////
#define PREVIEW_COLOR_FG_RED          0
#define PREVIEW_COLOR_FG_GREEN        0
#define PREVIEW_COLOR_FG_BLUE         0
////////////////////////////////////////////////////////////////
#define CSV_HEX_FIELD_OFFSET          1
#define CSV_NAME_FIELD_OFFSET         1
#define CSV_INPUT_FIELDS_QTY          2
////////////////////////////////////////////////////////////////
#define MAX_INPUT_FILE_NAME_LEN       128
#define MIN_INPUT_FILE_SIZE           10
#define MIN_INPUT_FILE_LINES          1
////////////////////////////////////////////////////////////////
#define MAX_OUTPUT_COLOR_ITEM_SIZE    1024 * 2
////////////////////////////////////////////////////////////////
#ifdef HEX_LEN
#undef HEX_LEN
#endif
#define HEX_LEN                          7
#define MIN_COLOR_NAME_LEN               3
////////////////////////////////////////////////////////////////
/***********************/
#define COLOR_NAME_T_STRUCT_TEST_MAIN    "\
int test_color_sizes(const int argc, const char **argv) {\n\
    printf(\"|%zu Colors|%zu Color Content Bytes|\\n\"\n\
            , COLOR_NAMES_QTY\n\
            , COLOR_NAMES_PATH_SIZES\n\
          );\n\
    return(0);\n\
}\n\
"
#define COLOR_NAME_T_STRUCT_PREFIX       "\
#include <stdio.h>\n\
#include <stdlib.h>\n\
#include <stdbool.h>\n\n\
"
#define COLOR_NAME_T_STRUCT              "\
typedef struct color_name_t {\n\
  unsigned long      id;\n\
  char               hex[8], name[64];\n\
  uint32_t           red, green, blue, alpha;\n\
  bool               exists;\n\
  size_t             path_size;\n\
  char               path[256], encoded_path_contents[1024];\n\
} color_name_t;\n\n"
/***********************/// ANSI Structs
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
const char *test_main = COLOR_NAME_T_STRUCT_TEST_MAIN;
/***********************/
struct pman_args_t {
  char   *input_file, *output_file;
  bool   verbose_mode, test_mode;
  size_t max_colors_qty;
};
typedef struct render_t {
  StringBuffer *OutputBuffer;
  StringBuffer *InputBuffer;
  Strings      InputLines;
  size_t       processed_colors_qty;
  size_t       input_buffer_bytes;
  int          input_file_exists;
  size_t       path_size_sum;
} render_t;
/***********************/
static render_t    *ro;
static pman_args_t *parser_args;


static void enable_verbose_mode() {
  parser_args->verbose_mode = true;
}


static void enable_test_mode(command_t *self){
  parser_args->test_mode = true;
}


static void set_max_colors_qty(command_t *self){
  parser_args->max_colors_qty = atoi(self->arg);
}


static void set_output_file(command_t *self){
  parser_args->output_file = strdup(self->arg);
}


static void set_input_file(command_t *self){
  parser_args->input_file = strdup(self->arg);
  assert_nonnull(parser_args->input_file);
}


////////////////////////////////////////////////////////////////////////
int init_parser_args(const int argc, const char **argv){
  if (parser_args != NULL) {
    return(0);
  }
  ////////////////////////////////////////////////////////////////
  command_t cmd;

  parser_args = malloc(sizeof(pman_args_t));
  ro          = malloc(sizeof(struct render_t));
  ////////////////////////////////////////////////////////////////
  ro->input_buffer_bytes = 0;
  ro->path_size_sum      = 0;
  ////////////////////////////////////////////////////////////////
  parser_args->test_mode      = DEFAULT_TEST_MODE;
  parser_args->verbose_mode   = DEFAULT_VERBOSE_MODE;
  parser_args->input_file     = malloc(MAX_INPUT_FILE_NAME_LEN);
  parser_args->output_file    = strdup(DEFAULT_OUTPUT_FILE);
  parser_args->max_colors_qty = DEFAULT_COLORS_QTY;
  ////////////////////////////////////////////////////////////////
  sprintf(parser_args->input_file, "%s", DEFAULT_INPUT_FILE);
  ////////////////////////////////////////////////////////////////
  command_init(&cmd, argv[0], PARSER_VERSION);
  command_option(&cmd, "-v", "--verbose", "Enable Verbose Mode", enable_verbose_mode);
  command_option(&cmd, "-T", "--test", "Enable Test Mode", enable_test_mode);
  command_option(&cmd, "-i", "--input-file  [in-file]", "Input Color File", set_input_file);
  command_option(&cmd, "-o", "--output-file  [out-file]", "Output Color File", set_output_file);
  command_option(&cmd, "-c", "--colors-qty  [colors-qty]", "Colors Quantity", set_max_colors_qty);
  command_parse(&cmd, argc, (char **)argv);
  ////////////////////////////////////////////////////////////////
  if (DEBUG_ARGUMENTS || parser_args->verbose_mode) {
    if (parser_args->verbose_mode) {
      fprintf(stderr, "Additional Args:\n");
      for (int i = 0; i < cmd.argc; ++i) {
        fprintf(stderr, "  - '%s'\n", cmd.argv[i]);
      }
    }
    fprintf(stderr, "================================\n");
    fprintf(stderr, "Input File:             %s\n", parser_args->input_file);
    fprintf(stderr, "Output File:            %s\n", parser_args->output_file);
    fprintf(stderr, "Colors Quantity:        %lu\n", parser_args->max_colors_qty);
    fprintf(stderr, "Test mode Enabled?      %s\n", parser_args->test_mode    ? "Yes" : "No");
    fprintf(stderr, "Verbose Enabled?        %s\n", parser_args->verbose_mode ? "Yes" : "No");
    fprintf(stderr, "================================\n");
  }
  command_free(&cmd);
  return(0);
} /* init_parser_args */


int main(const int argc, const char **argv) {
  int r;

  r = init_parser_args(argc, argv);
  assert_eq(r, 0, %d);
  tq_set_unit(tq_MILLISECONDS);
  tq_start(NULL);
  ////////////////////////////////////////////////////////////////
  struct djbhash *djb__hash;

  djb__hash = malloc(sizeof(struct djbhash));
  assert_nonnull(djb__hash);
  djbhash_init(djb__hash);
  assert_nonnull(djb__hash);
  ////////////////////////////////////////////////////////
  char *dur_msg                 = malloc(DEFAULT_BUFFER_SIZE);
  char **split_csv_buffer_lines = malloc(DEFAULT_BUFFER_SIZE);

  ////////////////////////////////////////////////////////
  ro->input_file_exists = (int)fs_exists(parser_args->input_file);
  assert_eq(ro->input_file_exists, 0, %d);
  ////////////////////////////////////////////////////////
  ro->OutputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(ro->OutputBuffer);
  ro->InputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(ro->InputBuffer);
  ////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->InputBuffer, (char *)fs_read(parser_args->input_file));
  ro->input_buffer_bytes = stringbuffer_get_content_size(ro->InputBuffer);
  assert_ge(ro->input_buffer_bytes, MIN_INPUT_FILE_SIZE, %lu);
  ro->InputLines = stringfn_split_lines_and_trim(stringbuffer_to_string(ro->InputBuffer));
  assert_ge(ro->InputLines.count, MIN_INPUT_FILE_LINES, %d);
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->OutputBuffer, COLOR_NAME_T_STRUCT_PREFIX);
  stringbuffer_append_string(ro->OutputBuffer, "#ifndef COLOR_NAME_STRUCT_DEFINED\n");
  stringbuffer_append_string(ro->OutputBuffer, "#define COLOR_NAME_STRUCT_DEFINED\n\n");
  stringbuffer_append_string(ro->OutputBuffer, COLOR_NAME_T_STRUCT);
  stringbuffer_append_string(ro->OutputBuffer, "color_name_t COLOR_NAMES[] = {\n");
  ////////////////////////////////////////////////////////

  for (unsigned long i = 0; (i < ro->InputLines.count) && (ro->processed_colors_qty < parser_args->max_colors_qty) && (ro->processed_colors_qty <= MAX_COLORS_QTY); i++) {
    ro->processed_colors_qty++;

    if (strlen(ro->InputLines.strings[i]) < MIN_INPUT_FILE_LINES || strsplit(ro->InputLines.strings[i], split_csv_buffer_lines, ",") != CSV_INPUT_FIELDS_QTY) {
      continue;
    }

    color_name_t *cn = malloc(sizeof(color_name_t));
    assert_nonnull(cn);

    cn->name = trim(split_csv_buffer_lines[CSV_NAME_FIELD_OFFSET]);
    assert_ge(strlen(cn->name), MIN_COLOR_NAME_LEN, %lu);
    cn->name[strlen(cn->name)] = '\0';

    cn->hex          = case_upper(trim(split_csv_buffer_lines[CSV_HEX_FIELD_OFFSET]));
    cn->hex[HEX_LEN] = '\0';

    if (strlen(cn->name) < MIN_COLOR_NAME_LEN || strlen(cn->hex) != HEX_LEN) {
      continue;
    }

    assert_eq(strlen(cn->hex), HEX_LEN, %lu);

    short    prop_val_ok;
    uint32_t _rgba = rgba_from_string(cn->hex, &prop_val_ok);
    assert_eq(prop_val_ok, 1, %d);

    rgba_t prop_val_rgba = rgba_new(_rgba);

    assert_le(prop_val_rgba.r, 1.0, % f);
    assert_le(prop_val_rgba.g, 1.0, % f);
    assert_le(prop_val_rgba.b, 1.0, % f);
    assert_le(prop_val_rgba.a, 1.0, % f);

    assert_ge(prop_val_rgba.r, RGB_MIN_VAL, % f);
    assert_ge(prop_val_rgba.g, RGB_MIN_VAL, % f);
    assert_ge(prop_val_rgba.b, RGB_MIN_VAL, % f);
    assert_ge(prop_val_rgba.a, RGB_MIN_VAL, % f);


    cn->red = (uint32_t)_rgba >> 24 & 0xff;
    assert_ge(cn->red, RGB_MIN_VAL, %d);
    assert_le(cn->red, RGB_MAX_VAL, %d);
    cn->green = (uint32_t)_rgba >> 16 & 0xff;
    assert_ge(cn->green, RGB_MIN_VAL, %d);
    assert_le(cn->green, RGB_MAX_VAL, %d);
    cn->blue = (uint32_t)_rgba >> 8 & 0xff;
    assert_ge(cn->blue, RGB_MIN_VAL, %d);
    assert_le(cn->blue, RGB_MAX_VAL, %d);
    cn->alpha = (uint32_t)_rgba & 0xff;
    assert_ge(cn->alpha, RGB_MIN_VAL, %d);
    assert_le(cn->alpha, RGB_MAX_VAL, %d);

    cn->ansi              = malloc(DEFAULT_BUFFER_SIZE);
    cn->encoded_ansi_code = malloc(DEFAULT_BUFFER_SIZE);
    char *ansi_code = malloc(DEFAULT_BUFFER_SIZE);

    if (cn->red < RGB_MIN_VAL || cn->red > RGB_MAX_VAL || cn->green < RGB_MIN_VAL || cn->green > RGB_MAX_VAL || cn->blue < RGB_MIN_VAL || cn->blue > RGB_MAX_VAL || cn->alpha < RGB_MIN_VAL || cn->alpha > RGB_MAX_VAL) {
      continue;
    }

    sprintf(cn->ansi, ANSI_TEMPLATE, cn->red, cn->green, cn->blue);
    sprintf(ansi_code, "%s%s%s", ANSI_TEMPLATE_PREFIX, cn->ansi, ANSI_TEMPLATE_SUFFIX);
    sprintf(cn->encoded_ansi_code, "%s", (char *)b64_encode((const unsigned char *)ansi_code, strlen(ansi_code)));
    free(ansi_code);

    tq_start(NULL);

    if (djbhash_find(djb__hash, cn->hex) != NULL) {
      continue;
    }

    djbhash_set(djb__hash, cn->hex, cn->hex, DJBHASH_STRING);
    struct djbhash_node *found = djbhash_find(djb__hash, cn->hex);
    assert_nonnull(found);

    char *PATH = malloc(DEFAULT_BUFFER_SIZE);

    sprintf(PATH, COLOR_IMAGE_PATH_TEMPLATE,
            cn->red, cn->green, cn->blue
            );

    bool exists = (bool)((fs_exists(PATH) == 0) ? true : false);
    if (!exists) {
      //  continue;
    }

    size_t path_size              = (size_t)(exists ? fs_size(PATH) : 0);
    char   *encoded_path_contents = (char *)(b64_encode((const unsigned char *)fsio_read_binary_file(PATH), path_size));

    char   *__dat = malloc(MAX_OUTPUT_COLOR_ITEM_SIZE);
    sprintf(
      __dat,
      "  { \n"
      "\t.id = %lu,\t.hex = \"%s\",\t.name = \"%.32s\",\n"
      "\t.red = %d,\t.green = %d,\t\t.blue = %d,\n"
      "\t.alpha = %d,\n"
      "\t.path = \"%s\",\n"
      "\t.exists = %s,\t.path_size = %lu,\n"
      "\t.encoded_path_contents = \"%s\",\n"
      "  },\n",
      i, cn->hex, cn->name,
      cn->red, cn->green, cn->blue,
      cn->alpha,
      PATH, exists == 1 ? "true" : "false", path_size,
      encoded_path_contents
      );

    stringbuffer_append_string(ro->OutputBuffer, __dat);
    ro->path_size_sum += path_size;

    if (parser_args->verbose_mode) {
      _reset_terminal_to_default_color();
      _change_terminal_color_name(cn);
      _change_terminal_color_fg(PREVIEW_COLOR_FG_RED, PREVIEW_COLOR_FG_GREEN, PREVIEW_COLOR_FG_BLUE);
      fprintf(stdout, "%s", __dat);
      _reset_terminal_to_default_color();
    }

    free(cn->ansi);
    free(cn->encoded_ansi_code);
    free(cn);
    free(PATH);
    free(__dat);
  }
  char *dur = tq_stop("Duration");

  stringbuffer_append_string(ro->OutputBuffer, "};");
  stringbuffer_append_string(ro->OutputBuffer, "\n\n");
  stringbuffer_append_string(ro->OutputBuffer, "const size_t COLOR_NAMES_QTY = ");
  stringbuffer_append_unsigned_long(ro->OutputBuffer, ro->processed_colors_qty);
  stringbuffer_append_string(ro->OutputBuffer, ";\n");

  stringbuffer_append_string(ro->OutputBuffer, "const size_t COLOR_NAMES_PATH_SIZES = ");
  stringbuffer_append_unsigned_long(ro->OutputBuffer, ro->path_size_sum);
  stringbuffer_append_string(ro->OutputBuffer, ";\n");
  stringbuffer_append_string(ro->OutputBuffer, "\n");
  stringbuffer_append_string(ro->OutputBuffer, "#endif");
  stringbuffer_append_string(ro->OutputBuffer, "\n");

  if (parser_args->test_mode) {
    stringbuffer_append_string(ro->OutputBuffer, "\n//TEST MODE ENABLED\n");
    stringbuffer_append_string(ro->OutputBuffer, "#define TEST_MODE_ENABLED\n");
    stringbuffer_append_string(ro->OutputBuffer, (char *)test_main);
    stringbuffer_append_string(ro->OutputBuffer, "\n");
  }else{
    stringbuffer_append_string(ro->OutputBuffer, "//TEST MODE DISABLED\n");
  }

  int  wrote_bytes         = fs_write(parser_args->output_file, stringbuffer_to_string(ro->OutputBuffer));
  bool output_file_created = (bool)((fs_exists(parser_args->output_file) == 0) ? true : false);

  assert_eq(output_file_created, true, %d);
  int output_buffer_size = stringbuffer_get_content_size(ro->OutputBuffer);

  assert_eq(wrote_bytes, output_buffer_size, %d);

  sprintf(dur_msg,
          "Processed %lu Colors from %lu byte file %s with %d lines :: %s and wrote %d bytes to %s",
          ro->processed_colors_qty,
          ro->input_buffer_bytes,
          parser_args->input_file,
          ro->InputLines.count,
          dur,
          wrote_bytes,
          parser_args->output_file
          );

  stringbuffer_release(ro->OutputBuffer);
  stringbuffer_release(ro->InputBuffer);
  stringfn_release_strings_struct(ro->InputLines);
  djbhash_destroy(djb__hash);
  free(parser_args->input_file);
  free(parser_args->output_file);
  free(ro);
  free(parser_args);
  OK(dur_msg);
  free(dur_msg);
  return(0);
} /* main */

