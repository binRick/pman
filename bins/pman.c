#include "../include/includes.h"
// MESON_BIN_ENABLED=true
/***********************/
#include "../include/includes-pman.h"
/***********************/
#include "../src/pman-init.c"
/***********************/
#define DEBUG_ARGUMENTS                   true
#define PRINT_PRETTY_COLORS_DEBUG         false
#define PRINT_PRETTY_COLOR_NAMES_DEBUG    false
/***********************/
#define PRETTY_PRINT_COLORS_TEXT          L"Testing 123"
#define DEFAULT_QTY_LIMIT                 10
#define MAX_QTY_LIMIT                     100
#define VERBOSE_DEBUG_MODE                false
#define PARSER_VERSION                    "0.0.1"
/***********************/// ANSI Structs
#define streq(a, b)    (strcmp(a, b) == 0)
/***********************/
typedef struct pman_args_t       pman_args_t;
typedef struct render_t          render_t;
typedef struct StringFNStrings   Strings;
typedef struct StringBuffer      StringBuffer;
/***********************/
void change_terminal_color(uint8_t r, uint8_t g, uint8_t b);
void reset_terminal_to_default_color();
int  pretty_print_colors();

/***********************/
struct pman_args_t {
  char *mode;
  FILE *input_fd;
  FILE *output_fd;
  char *input_file;
  char *output_file;
  char *template_file;
  ///////////////////////////
  /////////////// MODES
  bool verbose_mode, test_mode;
  bool render_template, pretty_print_colors_mode, parse_color_names_mode;
  ///////////////////////////
};
struct render_t {
  size_t         in_bytes, out_bytes, template_bytes, rendered_bytes;
  int            in_exists, out_exists, template_exists;
  size_t         in_lines_qty, out_lines_qty, template_lines_qty, renderd_lines_qty;
  char           *in_content, *out_content, *template_content, *rendered_template_content;
  char           *rendered;
  long long      timestamp;
  struct hashmap *hm, *in, *out, *stats, *template;
  struct env     *env;
  Strings        TemplateLines, InputLines, OutputLines;
  StringBuffer   *Template, *Input, *Output;
};
/***********************/
const char  *DEFAULT_INPUT_FILE           = "/tmp/colornames.csv";
const char  *DEFAULT_OUTPUT_FILE          = "/tmp/embedded-palettes.h";
const char  *DEFAULT_COLOR_LOGS_DIRECTORY = "./etc/color-logs";
const char  *DEFAULT_EXECUTION_MODE       = "list_colors";
const char  *DEFAULT_TEMPLATE             = "color-names.tpl";
/***********************/
render_t    *ro; static pman_args_t *parser_args;
static bool prefix_ran = false, suffix_ran = false; size_t qty;

#define MAX_LEN    16


/***********************/
char *cn_template_file, *cn_template_contents;  Strings ColornameTemplateLines;


/***********************/
void init_get_color_structure_item(){
  cn_template_file       = "/Users/rick/repos/pman/etc/tpl/color-name/color-name.tpl";
  cn_template_contents   = trim(fs_read(cn_template_file));
  ColornameTemplateLines = stringfn_split_lines_and_trim(cn_template_contents);
  if (parser_args->verbose_mode) {
    dbg(cn_template_contents, %s);
  }
}


/***********************/
char *get_color_structure_item(color_name_t *cn){
  char *buf_cn = malloc(strlen(cn_template_contents) + 1024);

  assert_nonnull(buf_cn);
  sprintf(buf_cn, cn_template_contents,
          cn->name,
          cn->rgb,
          "HEX",
          cn->red, cn->green, cn->blue, cn->alpha,
          "cn->rgba", cn->encoded_log, cn->encoded_log_bytes
          );
  buf_cn = trim(stringfn_remove(buf_cn, "\n"));
  if (parser_args->verbose_mode) {
    dbg(buf_cn, %s);
  }
  return(buf_cn);
}


/***********************/
typedef struct ColorsListResult ColorsListResult;
struct ColorsListResult {
  Strings Lines;
};

/***********************/


ColorsListResult *get_colors_list(char *data){
  init_get_color_structure_item();
  unsigned     colors_qty = 0;
  StringBuffer *_sb       = stringbuffer_new_with_options(1024, true);
  Strings      Lines      = stringfn_split_lines_and_trim(data);

  tq_set_unit(tq_MICROSECONDS);
  tq_start(NULL);
  for (int i = 0; i < Lines.count; i++) {
    size_t split_comma_qty = occurrences(",", Lines.strings[i]);
    size_t split_hash_qty  = occurrences("#", Lines.strings[i]);
    if (split_comma_qty == 1 && split_hash_qty == 1) {
      char **_ss = malloc(strlen(Lines.strings[i]) + 8);
      int  _qty  = strsplit(Lines.strings[i], _ss, ",");
      if (_qty == 2 && strlen(trim(_ss[1])) == 7 && stringfn_starts_with(trim(_ss[1]), "#")) {
        char *ns = stringfn_replace(trim(_ss[1]), '#', ' ');
        if (strlen(trim(ns)) == 6) {
          short   rgba_ok;
          int32_t rgba_val = rgba_from_string(trim(_ss[1]), &rgba_ok);
          if (rgba_ok == 1) {
            rgba_t RGBA       = rgba_new(rgba_val);
            char   *rgba_name = malloc(1024);
            rgba_to_string(RGBA, rgba_name, 256);
            int    red            = (uint32_t)rgba_val >> 24 & 0xff;
            int    green          = (uint32_t)rgba_val >> 16 & 0xff;
            int    blue           = (uint32_t)rgba_val >> 8 & 0xff;
            int    alpha          = (uint32_t)rgba_val & 0xff;
            char   *cur_rgba_name = trim(stringfn_to_uppercase(rgba_name));
            colors_qty++;
            stringbuffer_append_string(_sb, "\"");
            stringbuffer_append_string(_sb, cur_rgba_name);
            stringbuffer_append_string(_sb, "\":");
            stringbuffer_append_unsigned_int(_sb, red);
            stringbuffer_append_string(_sb, ":");
            stringbuffer_append_unsigned_int(_sb, green);
            stringbuffer_append_string(_sb, ":");
            stringbuffer_append_unsigned_int(_sb, blue);
            stringbuffer_append_string(_sb, ":");
            stringbuffer_append_unsigned_int(_sb, alpha);
            stringbuffer_append_string(_sb, ":\"");
            stringbuffer_append_string(_sb, _ss[0]);
            stringbuffer_append_string(_sb, "\"");
            stringbuffer_append_string(_sb, "\n");

            if (parser_args->verbose_mode) {
              dbg(stringbuffer_to_string(_sb), %s);
            }

            color_name_t cn = {
              .name              = _ss[0],
              .rgb               = cur_rgba_name,
              .red               = red,                 .green= green, .blue = blue,
              .alpha             = alpha,
              .rgba              = (long long)111111111,
              .encoded_log       = "xxx",
              .encoded_log_bytes = 123,
            };
            char         *color_item_line = get_color_structure_item(&cn);
            assert_nonnull(color_item_line);
            assert_ge(strlen(color_item_line), 10, %lu);
            if (parser_args->verbose_mode) {
              dbg(color_item_line, %s);
            }
            if (PRINT_PRETTY_COLOR_NAMES_DEBUG) {
              change_terminal_color(red, green, blue);
              wprintf(L"               |%3u|%3u|%3u|%3u|%s|%25s|         \n", red, green, blue, alpha, cur_rgba_name, _ss[0]);
            }
            free(cur_rgba_name);
            free(rgba_name);
          }
        }
        free(ns);
      }
      free(_ss);
    }
  }
  Strings _S = stringfn_split_lines_and_trim(stringbuffer_to_string(_sb));

  stringbuffer_release(_sb);
  stringfn_release_strings_struct(Lines);
  char *ns_s           = tq_stop("get_colors_list_dur");
  char **ns_items      = malloc(strlen(ns_s) + 8);
  char **_ns_items     = malloc(strlen(ns_s) + 8);
  int  colon_split_qty = strsplit(ns_s, ns_items, ":");

  dbg(colon_split_qty, %d);
  assert_eq(colon_split_qty, 2, %d);
  dbg(ns_items[1], %s);
  int period_split_qty = strsplit(ns_items[1], _ns_items, ".");

  dbg(period_split_qty, %d);
  assert_eq(period_split_qty, 2, %d);
  dbg(_ns_items[0], %s);
  char *ns_str = strdup(_ns_items[0]);

  free(ns_s);
  free(_ns_items);
  free(ns_items);

  int ns_is_num = is_number(ns_str, strlen(ns_str));

  dbg(ns_is_num, %d);
  assert_eq(ns_is_num, 1, %d);
  int dur_ns_int = atoi(ns_str);

  dbg(dur_ns_int, %d);
  assert_ge(dur_ns_int, 10, %d);
  char *dur_msg = malloc(1024);


  ColorsListResult *clr = malloc(sizeof(ColorsListResult));

  clr->Lines = _S;
  dbg(clr->Lines.count, %d);

  sprintf(dur_msg, "Processed %d Colors in %d milliseconds", clr->Lines.count, dur_ns_int / 1000);
  dbg(dur_msg, %s);

  return(clr);
} /* get_colors_list */


int __ORIG__do_render_template() {
  //////////////////////////////////////////////////////////////////////////////
  //ro->env              = env_new("./etc/tpl");
  ro->env      = env_new("/Users/rick/repos/pman-gh/etc/tpl/color-names");
  ro->hm       = hashmap_new();
  ro->stats    = hashmap_new();
  ro->template = hashmap_new();
  ro->in       = hashmap_new();
  ro->out      = hashmap_new();
  //////////////////////////////////////////////////////////////////////////////
  assert_nonnull(ro->env);
  assert_nonnull(ro->hm);
  assert_nonnull(ro->stats);
  assert_nonnull(ro->template);
  assert_nonnull(ro->in);
  assert_nonnull(ro->out);
  //////////////////////////////////////////////////////////////////////////////
  assert_ge(strlen(parser_args->template_file), 1, %lu);
  assert_ge(strlen(parser_args->output_file), 1, %lu);
  assert_ge(strlen(parser_args->input_file), 1, %lu);
  //////////////////////////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->Input, fs_read(parser_args->input_file));
  ColorsListResult *CLR = get_colors_list(stringbuffer_to_string(ro->Input));

  exit(0);

  for (int i = 0; i < CLR->Lines.count; i++) {
    if (strlen(CLR->Lines.strings[i]) < 10) {
      continue;
    }
    if (i < 50 || i > (CLR->Lines.count - 50)) {
      size_t _qty_colons = occurrences(":", CLR->Lines.strings[i]);
      size_t _qty_quotes = occurrences("\"", CLR->Lines.strings[i]);
      if ((_qty_colons != 6) || (_qty_quotes != 4)) {
        continue;
      }
      if (parser_args->verbose_mode) {
        fprintf(stderr, "%d> %s\n", i, CLR->Lines.strings[i]);
      }
    }
  }
  dbg(CLR->Lines.count, %d);
  //tm();
  //exit(0);
  stringbuffer_append_string(ro->Template, fs_read(parser_args->template_file));
  //////////////////////////////////////////////////////////////////////////////
  if (!fs_exists(parser_args->output_file)) {
    fs_write(parser_args->output_file, "");
  }
  //////////////////////////////////////////////////////////////////////////////
  dbg(parser_args->template_file, %s);
  dbg(parser_args->output_file, %s);
  dbg(parser_args->input_file, %s);
  dbg(parser_args->output_file, %s);
  dbg(fs_exists(parser_args->output_file), %d);
  //////////////////////////////////////////////////////////////////////////////
  assert_eq(fs_exists(parser_args->template_file), 0, %d);
  assert_eq(fs_exists(parser_args->input_file), 0, %d);
  assert_eq(fs_exists(parser_args->output_file), -1, %d);
  //////////////////////////////////////////////////////////////////////////////
  dbg(stringbuffer_get_content_size(ro->Template), %lu);
  dbg(stringbuffer_get_content_size(ro->Input), %lu);
  dbg(stringbuffer_get_content_size(ro->Output), %lu);
  //////////////////////////////////////////////////////////////////////////////
  assert_ge(stringbuffer_get_content_size(ro->Template), 1, %lu);
  assert_ge(stringbuffer_get_content_size(ro->Input), 1, %lu);
  assert_eq(stringbuffer_get_content_size(ro->Output), 0, %lu);
  //////////////////////////////////////////////////////////////////////////////
  ro->InputLines    = stringfn_split_lines_and_trim(stringbuffer_to_string(ro->Input));
  ro->OutputLines   = stringfn_split_lines_and_trim(stringbuffer_to_string(ro->Output));
  ro->TemplateLines = stringfn_split_lines_and_trim(stringbuffer_to_string(ro->Template));
  //////////////////////////////////////////////////////////////////////////////
  assert_ge(ro->TemplateLines.count, 1, %d);
  assert_ge(ro->InputLines.count, 1, %d);
  assert_eq(ro->OutputLines.count, 1, %d);
  //////////////////////////////////////////////////////////////////////////////
  dbg(ro->TemplateLines.count, %d);
  dbg(ro->InputLines.count, %d);
  dbg(ro->OutputLines.count, %d);
  //////////////////////////////////////////////////////////////////////////////
  char *input_lines_qty = malloc(1024), *template_lines_qty = malloc(1024), *input_bytes_qty = malloc(1024),
       *template_bytes_qty = malloc(1024), *output_bytes_qty = malloc(1024), *output_lines_qty = malloc(1024),
       *dt               = malloc(1024);
  char *ts               = malloc(1024);
  char *input_colors_qty = malloc(1024);

  //////////////////////////////////////////////////////////////////////////////
  sprintf(ts, "%lu", (long unsigned)timestamp());
  sprintf(dt, "%s", (char *)get_datetime());
  sprintf(input_colors_qty, "%d", CLR->Lines.count);
  //////////////////////////////////////////////////////////////////////////////
  sprintf(output_bytes_qty, "%lu", stringbuffer_get_content_size(ro->Output));
  sprintf(template_bytes_qty, "%lu", stringbuffer_get_content_size(ro->Template));
  sprintf(input_bytes_qty, "%lu", stringbuffer_get_content_size(ro->Input));
  //////////////////////////////////////////////////////////////////////////////
  sprintf(output_lines_qty, "%d", ro->OutputLines.count);
  sprintf(input_lines_qty, "%d", ro->InputLines.count);
  sprintf(template_lines_qty, "%d", ro->TemplateLines.count);
  //////////////////////////////////////////////////////////////////////////////
  dbg(input_colors_qty, %s);
  dbg(input_lines_qty, %s);
  dbg(ro->InputLines.count, %d);
  //////////////////////////////////////////////////////////////////////////////
  dbg(output_lines_qty, %s);
  dbg(ro->OutputLines.count, %d);
  //////////////////////////////////////////////////////////////////////////////
  dbg(template_lines_qty, %s);
  dbg(ro->TemplateLines.count, %d);
  //////////////////////////////////////////////////////////////////////////////
  dbg(output_bytes_qty, %s);
  dbg(parser_args->output_file, %s);
  //////////////////////////////////////////////////////////////////////////////
  hashmap_insert(ro->out, "file", parser_args->output_file);
  hashmap_insert(ro->out, "bytes", output_bytes_qty);
  hashmap_insert(ro->out, "lines", output_lines_qty);
  //////////////////////////////////////////////////////////////////////////////
  hashmap_insert(ro->in, "file", parser_args->input_file);
  hashmap_insert(ro->in, "bytes", input_bytes_qty);
  hashmap_insert(ro->in, "lines", input_lines_qty);
  hashmap_insert(ro->in, "colors_qty", input_colors_qty);
  //////////////////////////////////////////////////////////////////////////////
  hashmap_insert(ro->template, "file", parser_args->template_file);
  hashmap_insert(ro->template, "bytes", template_bytes_qty);
  hashmap_insert(ro->template, "lines", template_lines_qty);
  //////////////////////////////////////////////////////////////////////////////
  hashmap_insert(ro->stats, "datetime", (char *)dt);
  hashmap_insert(ro->stats, "timestamp", (char *)ts);
  /////////////////////////////////////////////////////////////////////////////
  hashmap_insert(ro->hm, "template", ro->template);
  hashmap_insert(ro->hm, "stats", ro->stats);
  hashmap_insert(ro->hm, "out", ro->out);
  hashmap_insert(ro->hm, "in", ro->in);
  ////////////////////////////////////////////////////////////////////////////
  dbg(parser_args->template_file, %s);
  assert_nonnull(ro->hm);
  assert_nonnull(ro->env);
  assert_nonnull(parser_args->template_file);
  ////////////////////////////////////////////////////////////////////////////
  ro->template_content = trim(fs_read(parser_args->template_file));
  ////////////////////////////////////////////////////////////////////////////
  assert_nonnull(ro->template_content);
  assert_ge(strlen(ro->template_content), 1, %lu);
  dbg(ro->template_content, %s);
  Strings TemplateContentLines = stringfn_split_lines_and_trim(ro->template_content);

  assert_nonnull(ro->template_content);
  assert_ge(strlen(ro->template_content), 1, %lu);
  dbg(ro->template_content, %s);
  dbg(strlen(ro->template_content), %lu);


  char *buf = malloc(strlen(ro->template_content) + 1024);

  assert_nonnull(buf);
  assert_nonnull(buf);
  dbg(strlen(buf), %lu);
  sprintf(buf, ro->template_content,
          parser_args->template_file, fs_size(parser_args->template_file), TemplateContentLines.count,
          parser_args->input_file, fs_size(parser_args->input_file), ro->InputLines.count,
          parser_args->output_file,
          CLR->Lines.count,
          timestamp(), get_datetime()
          );
  assert_nonnull(buf);
  dbg(strlen(buf), %lu);
  dbg(buf, %s);

  exit(0);
  return(EXIT_SUCCESS);
} /* do_render_template */


int do_render_template() {
  stringbuffer_append_string(ro->Input, fs_read(parser_args->input_file));
  ColorsListResult *CLR = get_colors_list(stringbuffer_to_string(ro->Input));

  exit(0);
  return(EXIT_SUCCESS);
} /* do_render_template */


////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
////                       Argument Handler Functions                ///
////////////////////////////////////////////////////////////////////////
static void set_execution_mode(command_t *self){
  sprintf(parser_args->mode, "%s", self->arg);
}


static void set_template_file(command_t *self){
  sprintf(parser_args->template_file, "%s", self->arg);
  if (parser_args->verbose_mode) {
    dbg(parser_args->template_file, %s);
    dbg(fs_exists(parser_args->template_file), %d);
  }
  assert_eq(fs_exists(parser_args->template_file), 0, %d);
}


static void enable_verbose_mode() {
  parser_args->verbose_mode = true;
}


static void enable_pretty_print_colors_mode() {
  parser_args->pretty_print_colors_mode = true;
}


static void enable_test_mode(command_t *self){
  parser_args->test_mode = true;
}


static void set_parse_color_names_mode(){
  parser_args->parse_color_names_mode = true;
}


static void set_template_render(){
  parser_args->render_template = true;
}


////////////////////////////////////////////////////////////////////////
static void set_output_file(command_t *self){
  if (strcmp(parser_args->output_file, "-") == 0) {
    parser_args->output_file = "STDOUT";
//    parser_args->output_fd = fopen(STDOUT_FILENO, "w");
  }else{
    parser_args->output_file = strdup(self->arg);
    //   parser_args->output_fd = fopen(parser_args->output_fd, "w");
  }
}


////////////////////////////////////////////////////////////////////////
static void set_input_file(command_t *self){
  if (strcmp(parser_args->output_file, "-") == 0) {
    parser_args->input_file = "STDIN";
    char buf[1024];
    while (fread(buf, 1, 1024, stdin) != 0) {
      printf("read:%s\n", buf);
    }
  }else{
    parser_args->input_file = strdup(self->arg);
    parser_args->input_fd   = fopen(parser_args->input_file, "r");
    //parser_args->input_fd = fopen(parser_args->input_fd, "r");
  }
}


////////////////////////////////////////////////////////////////////////
int init_parser_args(const int argc, const char **argv){
  ////////////////////////////////////////////////////////////////
  if (parser_args != NULL) {
    return(0);
  }
  ////////////////////////////////////////////////////////////////
  ro = malloc(sizeof(struct render_t));
  ////////////////////////////////////////////////////////////////
  ro->Template = stringbuffer_new_with_options(1024, true);
  ro->Input    = stringbuffer_new_with_options(1024, true);
  ro->Output   = stringbuffer_new_with_options(1024, true);
  ////////////////////////////////////////////////////////////////
  ro->in_bytes         = 0;
  ro->out_bytes        = 0;
  ro->template_bytes   = 0;
  ro->in_content       = malloc(1024 * 1024 * 4);
  ro->out_content      = malloc(1024 * 1024 * 4);
  ro->template_content = malloc(1024 * 1024 * 4);
  ro->template_content = malloc(1024 * 1024 * 4);
  ////////////////////////////////////////////////////////////////
  parser_args = malloc(sizeof(pman_args_t));
  ////////////////////////////////////////////////////////////////
  parser_args->template_file          = malloc(1024);
  parser_args->test_mode              = false;
  parser_args->verbose_mode           = false;
  parser_args->render_template        = false;
  parser_args->parse_color_names_mode = false;
  parser_args->input_file             = malloc(1024);
  parser_args->mode                   = malloc(1024);
  parser_args->output_file            = malloc(1024);
  ////////////////////////////////////////////////////////////////
  sprintf(parser_args->input_file, "%s", DEFAULT_INPUT_FILE);
  sprintf(parser_args->output_file, "%s", DEFAULT_OUTPUT_FILE);
  sprintf(parser_args->template_file, "%s", DEFAULT_TEMPLATE);
  sprintf(parser_args->mode, "%s", DEFAULT_EXECUTION_MODE);
  ////////////////////////////////////////////////////////////////
  command_t cmd;

  ////////////////////////////////////////////////////////////////
  command_init(&cmd, argv[0], PARSER_VERSION);
  command_option(&cmd, "-v", "--verbose", "Enable Verbose Mode", enable_verbose_mode);
  command_option(&cmd, "-T", "--test", "Enable Test Mode", enable_test_mode);
  command_option(&cmd, "-m", "--mode [mode]", "Set Execution Mode", set_execution_mode);
  command_option(&cmd, "-t", "--template [template]", "Set Template File", set_template_file);
  command_option(&cmd, "-i", "--input-file  [in-file]", "Input  Color File", set_input_file);
  command_option(&cmd, "-o", "--output-file [out-file]", "Output Color File", set_output_file);
  command_option(&cmd, "-r", "--render-template", "Enable Template Render", set_template_render);
  command_option(&cmd, "-c", "--parse-color-names", "Parse Color Names", set_parse_color_names_mode);
  command_option(&cmd, "-p", "--pretty-print-colors", "Pretty Print Colors", enable_pretty_print_colors_mode);
  command_parse(&cmd, argc, (char **)argv);
  ////////////////////////////////////////////////////////////////
  fprintf(stderr, "Additional Args:\n");
  for (int i = 0; i < cmd.argc; ++i) {
    fprintf(stderr, "  - '%s'\n", cmd.argv[i]);
  }
  command_free(&cmd);
  if (DEBUG_ARGUMENTS) {
    fprintf(stderr, "================================\n");
    fprintf(stderr, "Execution Mode:         %s\n", parser_args->mode);
    fprintf(stderr, "Input  File:            %s\n", parser_args->input_file);
    fprintf(stderr, "Output File:            %s\n", parser_args->output_file);
    fprintf(stderr, "Tempplate File:         %s\n", parser_args->template_file);
    fprintf(stderr, "Render Template?        %s\n", parser_args->render_template    ? "Yes" : "No");
    fprintf(stderr, "Parse Color Names?      %s\n", parser_args->parse_color_names_mode    ? "Yes" : "No");
    fprintf(stderr, "Test mode Enabled?      %s\n", parser_args->test_mode    ? "Yes" : "No");
    fprintf(stderr, "Pretty Print Enabled?   %s\n", parser_args->pretty_print_colors_mode    ? "Yes" : "No");
    fprintf(stderr, "Verbose Enabled?      %s\n", parser_args->verbose_mode ? "Yes" : "No");
    fprintf(stderr, "================================\n");
  }
  return(0);
} /* init_parser_args */


///////////////////////////////////////////////////////////////////////////////////////////
///                         Untemplated output mode                                     ///
///////////////////////////////////////////////////////////////////////////////////////////
void print_prefix(){
  fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "..............prefix........................" AC_RESETALL "\n");
  fprintf(stdout, "#pragma once");
  fprintf(stdout, "\n#include \"../include/includes.h\"");
  fprintf(stdout, "\n#include \"../include/types.h\"");
  fprintf(stdout, "\n#ifndef COLOR_NAMES_DEFINED\n#define COLOR_NAMES_DEFINED\n");
  fprintf(stdout, "\ncolor_name_t COLOR_NAMES[] = {\n");
  prefix_ran = true;
}


///////////////////////////////////////////////////////////////////////////////////////////
void print_suffix(void){
  if (prefix_ran) {
    char *dt = get_datetime();
    fprintf(stdout, "\t{ NULL },\n};\n\nconst size_t COLOR_NAMES_QTY = %lu;\nconst unsigned long created_ts = %lu;\nconst char *created_datetime = \"%s\";\n#endif\n", (unsigned long)qty, (unsigned long)timestamp(), dt);
    suffix_ran = true;
  }
  fprintf(stderr, AC_RESETALL AC_YELLOW AC_REVERSED "..............suffix........................" AC_RESETALL "\n");
}
///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
///                      MAIN                                                           ///
///////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char **argv) {
  int q, err, done;  short prop_val_ok;

  assert_eq(init_parser_args(argc, argv), 0, %d);
  if (!meson_test_mode_enabled) {
  }else{
    meson_test_mode();
    exit(0);
  }
  dbg(parser_args->parse_color_names_mode ? "Yes" : "No", %s);
  dbg(parser_args->parse_color_names_mode, %d);
  dbg(parser_args->render_template, %d);

  if (parser_args->pretty_print_colors_mode) {
    return(pretty_print_colors());

    return(0);
  }

  if (parser_args->parse_color_names_mode) {
    stringbuffer_append_string(ro->Input, fs_read(parser_args->input_file));
    ColorsListResult *CLR = get_colors_list(stringbuffer_to_string(ro->Input));
    exit(0);
  }

  exit(1);

  if (parser_args->render_template) {
    return(do_render_template());
  }

  exit(1);
  print_prefix();
  atexit(print_suffix);

  ro->in_exists       = (int)fs_exists(parser_args->input_file);
  ro->out_exists      = (int)fs_exists(parser_args->output_file);
  ro->template_exists = (int)fs_exists(parser_args->template_file);

  if (ro->in_exists == 0) {
    ro->in_bytes = fs_size(parser_args->input_file);
    assert_ge(ro->in_bytes, 10, %lu);
    ro->in_content   = (char *)fs_read(parser_args->input_file);
    ro->in_bytes     = (size_t)strlen(ro->in_content);
    ro->in_lines_qty = occurrences("\n", ro->in_content);
    //  print("    INPUT>", parser_args->input_file, "size:", ro->in_bytes, "lines:", in_lines_qty, "bytes:", strlen(in_content));
  }
  if (false) {
    dbg(ro->out_exists, %d);
    if (ro->out_exists == 0) {
      ro->out_bytes = fs_size(parser_args->output_file);
      dbg(ro->out_bytes, %lu);
      if (parser_args->verbose_mode) {
        fprintf(stderr, "> out log %s size:%lu\n", parser_args->output_file, ro->out_bytes);
      }
      assert_ge(ro->out_bytes, 10, %lu);
    }
  }
  exit(0);

  while (1 && (q <= MAX_QTY_LIMIT)) {
    q++;
    char *txt = fread_csv_line(parser_args->input_fd, 1024, &done, &err);
    if (done == 1) {
      break;
    }
    assert(err != CSV_ERR_NO_MEMORY);
    assert(txt);
    char **r = parse_csv(txt);
    assert(r);

    char *rgb_hex = case_upper(trim(r[1]));
    char *rgb     = str_replace(rgb_hex, "#", "");
    if (strlen(rgb) != 6) {
      continue;
    }

    int32_t  _r = rgba_from_string(rgb_hex, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t   prop_val_rgba = rgba_new(_r);

    char     *name = trim(r[0]);
    uint32_t red   = (uint32_t)_r >> 24 & 0xff;
    uint32_t green = (uint32_t)_r >> 16 & 0xff;
    uint32_t blue  = (uint32_t)_r >> 8 & 0xff;
    uint32_t alpha = (uint32_t)_r & 0xff;
    if (red < 0 || red > 256) {
      continue;
    }
    if (green < 0 || green > 256) {
      continue;
    }
    if (blue < 0 || blue > 256) {
      continue;
    }
    if (alpha < 0 || alpha > 256) {
      continue;
    }
    char *RGB = case_upper(rgb);


    char *in_data  = fs_read(parser_args->input_file);
    char *out_data = fs_read(parser_args->output_file);
    assert_ge(strlen(in_data), 100, %lu);
    assert_ge(strlen(out_data), 100, %lu);
    char *in_encoded = (char *)b64_encode((const unsigned char *)in_data, strlen(in_data));
    assert_ge(strlen(in_encoded), 100, %lu);

    fprintf(stdout, "\t{ \"%s\", \"%s\", \"%s\", %d, %d, %d, %d, %lu, \"%s\", %lu },\n",
            name,
            rgb,
            rgb_hex,
            red, green, blue, alpha,
            (unsigned long)0,
            in_encoded,
            strlen(in_encoded)
            );

    free(name);
    free(txt);
    qty++;
  }
  return(0);
} /* main */


/////////////////////////////////////////////////////////////////////
void change_terminal_color(uint8_t r, uint8_t g, uint8_t b){
  wprintf(COLOR_RGB, r, g, b);
}


void reset_terminal_to_default_color(){
  wprintf(L"%ls", COLOR_RESET_TO_DEFAULT);
}


int pretty_print_colors(){
  for (uint16_t r = 0; r < 256; r++) {
    for (uint16_t g = 0; g < 256; g++) {
      for (uint16_t b = 0; b < 256; b++) {
        change_terminal_color(r, g, b);
        wprintf(L"%3u,%3u,%3u |%ls|\n", r, g, b, PRETTY_PRINT_COLORS_TEXT);
      }
    }
  }
  reset_terminal_to_default_color();
  return(0);
}
