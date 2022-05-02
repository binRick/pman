/***********************/
#include "../include/includes.h"
/***********************/
#include "../include/includes-pman.h"
/***********************/
#include "../src/pman-init.c"
/***********************/
#define DEBUG_ARGUMENTS                   true
/***********************/
#define DEFAULT_QTY_LIMIT                 10
//#define MAX_QTY_LIMIT                     35000
#define MAX_QTY_LIMIT                     100
#define VERBOSE_DEBUG_MODE                false
#define MAX_FILE_SIZE 128
#define PARSER_VERSION                    "0.0.1"
#define DEBUG_COLORS false
#define DEFAULT_INPUT_FILE "../etc/colornames.csv"
/***********************/// ANSI Structs
/***********************/
//typedef struct pman_args_t       pman_args_t;
typedef struct render_t          render_t;
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
/***********************/
struct pman_args_t {
  FILE *input_fd;
  char *input_file;
  bool verbose_mode, test_mode;
};
struct render_t {
  size_t       in_bytes;
  int          in_exists;
  size_t       in_lines_qty;
  char         *in_content;
  long long    timestamp;
  Strings      InputLines;
  StringBuffer *Input;
};
/***********************/
render_t    *ro; static pman_args_t *parser_args;
static void enable_verbose_mode() { parser_args->verbose_mode = true; }
static void enable_test_mode(command_t *self){   parser_args->test_mode = true; }
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
  parser_args->test_mode              = false;
  parser_args->verbose_mode           = false;
  parser_args->input_file             = malloc(MAX_FILE_SIZE);
  ////////////////////////////////////////////////////////////////
  sprintf(parser_args->input_file, "%s", DEFAULT_INPUT_FILE);
  ////////////////////////////////////////////////////////////////
  command_t cmd;
  command_init(&cmd, argv[0], PARSER_VERSION);
  command_option(&cmd, "-v", "--verbose", "Enable Verbose Mode", enable_verbose_mode);
  command_option(&cmd, "-T", "--test", "Enable Test Mode", enable_test_mode);
  command_option(&cmd, "-i", "--input-file  [in-file]", "Input  Color File", set_input_file);
  command_parse(&cmd, argc, (char **)argv);
  ////////////////////////////////////////////////////////////////
  fprintf(stderr, "Additional Args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    fprintf(stderr, "  - '%s'\n", cmd.argv[i]);
  }
  command_free(&cmd);
  if (DEBUG_ARGUMENTS) {
    fprintf(stderr, "================================\n");
    fprintf(stderr, "Input  File:            %s\n", parser_args->input_file);
    fprintf(stderr, "Test mode Enabled?      %s\n", parser_args->test_mode    ? "Yes" : "No");
    fprintf(stderr, "Verbose Enabled?      %s\n", parser_args->verbose_mode ? "Yes" : "No");
    fprintf(stderr, "================================\n");
  }
  return(0);
} /* init_parser_args */


int main(const int argc, const char **argv) {
  size_t qty;
  char *dur_msg = malloc(1024);
  short prop_val_ok;
  char **s = malloc(1024);
  tq_set_unit(tq_MILLISECONDS);
  tq_start(NULL);
  ////////////////////////////////////////////////////////
  assert_eq(init_parser_args(argc, argv), 0, %d);
  ////////////////////////////////////////////////////////
  ro->in_exists = (int)fs_exists(parser_args->input_file);
  assert_eq(ro->in_exists, 0, %d);

  ro->in_bytes = fs_size(parser_args->input_file);
  assert_ge(ro->in_bytes, 10, %lu);
  ro->in_content   = (char *)fs_read(parser_args->input_file);
  ro->in_bytes     = (size_t)strlen(ro->in_content);
  ro->InputLines = stringfn_split_lines_and_trim(ro->in_content);
  assert_ge(ro->InputLines.count, 1, %d);

  for (int i = 0; (i < ro->InputLines.count) && (qty < MAX_QTY_LIMIT); i++) {
    if(strlen(ro->InputLines.strings[i]) < 3)continue;
    int  _qty = strsplit(ro->InputLines.strings[i], s, ",");
    if (_qty != 2) {
      continue;
    }
    color_name_t *cn = malloc(sizeof(color_name_t));
    cn->name = case_upper(trim(s[0]));
    cn->rgb = case_upper(trim(s[1]));

    if (strlen(cn->name) < 3 || strlen(cn->rgb) != 7) {
      continue;
    }
    uint32_t  _rgba = rgba_from_string(cn->rgb, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t   prop_val_rgba = rgba_new(_rgba);
    cn->red           = (uint32_t)_rgba >> 24 & 0xff;
    cn->green         = (uint32_t)_rgba >> 16 & 0xff;
    cn->blue          = (uint32_t)_rgba >> 8 & 0xff;
    cn->alpha         = (uint32_t)_rgba & 0xff;
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

    if (DEBUG_COLORS|| (qty < 10)) {
      //rgba_inspect(_rgba);
      fprintf(stdout, "\t{ \"%s\", \"%s\", %d, %d, %d, %d },\n",
              cn->name,
              cn->rgb,
              cn->red, cn->green, cn->blue, cn->alpha
              );
    }
    qty++;
    if(qty>=MAX_QTY_LIMIT)break;
    if(qty>=ro->InputLines.count)break;
  }
  char *dur = tq_stop("Duration");
  sprintf(dur_msg, 
          "Processed %lu Colors from %lu byte file with %d lines :: %s"
          , qty
          , ro->in_bytes
          , ro->InputLines.count
          , dur
          );
  OK(dur_msg);
  return(0);
} /* main */

