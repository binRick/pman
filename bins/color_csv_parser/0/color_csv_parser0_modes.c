#pragma once
#ifndef COLOR_PARSER_MODES
#define COLOR_PARSER_MODES
#include "./color_csv_parser0_defines.h"
#include "./color_csv_parser0_globals.c"
#include "./color_csv_parser0_types.h"


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
#endif
