#pragma once
#ifndef COLOR_PARSER_MODULE_LOGIC
#define COLOR_PARSER_MODULE_LOGIC
////////////////////////////////////////////////
#include "./color_csv_parser1_includes.c"
////////////////////////////////////////////////
module(colorcsvparser1) * colorcsvparser1;
////////////////////////////////////////////////////////////
#ifdef M
#undef M
#endif
#define M    require(colorcsvparser1)


////////////////////////////////////////////////////////////


static void enable_verbose_mode() {
  M->parser_args->verbose_mode = true;
}


static void enable_test_mode(command_t *self){
  M->parser_args->test_mode = true;
}


static void set_max_colors_qty(command_t *self){
  M->parser_args->max_colors_qty = atoi(self->arg);
}


static void set_output_file(command_t *self){
  M->parser_args->output_file = strdup(self->arg);
}


static void set_input_file(command_t *self){
  M->parser_args->input_file = strdup(self->arg);
  assert_nonnull(M->parser_args->input_file);
}


////////////////////////////////////////////////////////////////////////
int init_parser_args(const int argc, const char **argv){
//  if (M->parser_args != NULL) {
//    return(0);
//  }
  ////////////////////////////////////////////////////////////////
  command_t cmd;

  M->parser_args = malloc(sizeof(pman_args_t));
  M->ro          = malloc(sizeof(struct render_t));
  ////////////////////////////////////////////////////////////////
  M->ro->input_buffer_bytes = 0;
  M->ro->path_size_sum      = 0;
  ////////////////////////////////////////////////////////////////
  M->parser_args->test_mode      = DEFAULT_TEST_MODE;
  M->parser_args->verbose_mode   = DEFAULT_VERBOSE_MODE;
  M->parser_args->input_file     = malloc(MAX_INPUT_FILE_NAME_LEN);
  M->parser_args->output_file    = strdup(DEFAULT_OUTPUT_FILE);
  M->parser_args->max_colors_qty = DEFAULT_COLORS_QTY;
  ////////////////////////////////////////////////////////////////
  sprintf(M->parser_args->input_file, "%s", DEFAULT_INPUT_FILE);
  ////////////////////////////////////////////////////////////////
  command_init(&cmd, argv[0], PARSER_VERSION);
  command_option(&cmd, "-v", "--verbose", "Enable Verbose Mode", enable_verbose_mode);
  command_option(&cmd, "-T", "--test", "Enable Test Mode", enable_test_mode);
  command_option(&cmd, "-i", "--input-file  [in-file]", "Input Color File", set_input_file);
  command_option(&cmd, "-o", "--output-file  [out-file]", "Output Color File", set_output_file);
  command_option(&cmd, "-c", "--colors-qty  [colors-qty]", "Colors Quantity", set_max_colors_qty);
  command_parse(&cmd, argc, (char **)argv);
  ////////////////////////////////////////////////////////////////
  if (DEBUG_ARGUMENTS || M->parser_args->verbose_mode) {
    if (M->parser_args->verbose_mode) {
      fprintf(stderr, "Additional Args:\n");
      for (int i = 0; i < cmd.argc; ++i) {
        fprintf(stderr, "  - '%s'\n", cmd.argv[i]);
      }
    }
    fprintf(stderr, "================================\n");
    fprintf(stderr, "Input File:             %s\n", M->parser_args->input_file);
    fprintf(stderr, "Output File:            %s\n", M->parser_args->output_file);
    fprintf(stderr, "Colors Quantity:        %lu\n", M->parser_args->max_colors_qty);
    fprintf(stderr, "Test mode Enabled?      %s\n", M->parser_args->test_mode    ? "Yes" : "No");
    fprintf(stderr, "Verbose Enabled?        %s\n", M->parser_args->verbose_mode ? "Yes" : "No");
    fprintf(stderr, "================================\n");
  }
  command_free(&cmd);
  return(0);
}   /* init_parser_args */


int colorcsvparser1_logicinit(){
  colorcsvparser1 = require(colorcsvparser1);
  dbg(colorcsvparser1->loggermode, %d);
  M->loggermode = LOGGER_DEBUG;
  M->djb__hash  = malloc(sizeof(struct djbhash));
  assert_nonnull(M->djb__hash);
  djbhash_init(M->djb__hash);
  assert_nonnull(M->djb__hash);

//static render_t    *ro;
//static pman_args_t *parser_args;
//static const char *test_main = COLOR_NAME_T_STRUCT_TEST_MAIN;
//  M->ro          = malloc(sizeof(struct render_t));
//  M->parser_args = malloc(sizeof(pman_args_t));
  M->ro->input_file_exists = (int)fs_exists(M->parser_args->input_file);


  //return(0);
  dbg(M->parser_args->input_file, %s);

  assert_eq(M->ro->input_file_exists, 0, %d);




  ////////////////////////////////////////////////////////
  M->ro->OutputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(M->ro->OutputBuffer);
  M->ro->InputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(M->ro->InputBuffer);
  ////////////////////////////////////////////////////////
  stringbuffer_append_string(M->ro->InputBuffer, (char *)fs_read(M->parser_args->input_file));
  M->ro->input_buffer_bytes = stringbuffer_get_content_size(M->ro->InputBuffer);
  assert_ge(M->ro->input_buffer_bytes, MIN_INPUT_FILE_SIZE, %lu);
  M->ro->InputLines = stringfn_split_lines_and_trim(stringbuffer_to_string(M->ro->InputBuffer));
  assert_ge(M->ro->InputLines.count, MIN_INPUT_FILE_LINES, %d);
  ////////////////////////////////////////////////////////
  stringbuffer_append_string(M->ro->OutputBuffer, COLOR_NAME_T_STRUCT_PREFIX);
  stringbuffer_append_string(M->ro->OutputBuffer, "#ifndef COLOR_NAME_STRUCT_DEFINED\n");
  stringbuffer_append_string(M->ro->OutputBuffer, "#define COLOR_NAME_STRUCT_DEFINED\n\n");
  stringbuffer_append_string(M->ro->OutputBuffer, COLOR_NAME_T_STRUCT);
  stringbuffer_append_string(M->ro->OutputBuffer, "color_name_t COLOR_NAMES[] = {\n");
  ////////////////////////////////////////////////////////

  for (unsigned long i = 0; (i < M->ro->InputLines.count) && (M->ro->processed_colors_qty < M->parser_args->max_colors_qty) && (M->ro->processed_colors_qty <= MAX_COLORS_QTY); i++) {
    M->ro->processed_colors_qty++;

    if (strlen(M->ro->InputLines.strings[i]) < MIN_INPUT_FILE_LINES || strsplit(M->ro->InputLines.strings[i], M->split_csv_buffer_lines, ",") != CSV_INPUT_FIELDS_QTY) {
      continue;
    }

    color_name_t *cn = malloc(sizeof(color_name_t));
    assert_nonnull(cn);

    cn->name = trim(M->split_csv_buffer_lines[CSV_NAME_FIELD_OFFSET]);
    assert_ge(strlen(cn->name), MIN_COLOR_NAME_LEN, %lu);
    cn->name[strlen(cn->name)] = '\0';

    cn->hex          = case_upper(trim(M->split_csv_buffer_lines[CSV_HEX_FIELD_OFFSET]));
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

    if (djbhash_find(colorcsvparser1->djb__hash, cn->hex) != NULL) {
      continue;
    }

    djbhash_set(colorcsvparser1->djb__hash, cn->hex, cn->hex, DJBHASH_STRING);
    struct djbhash_node *found = djbhash_find(colorcsvparser1->djb__hash, cn->hex);
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

    stringbuffer_append_string(M->ro->OutputBuffer, __dat);
    M->ro->path_size_sum += path_size;

    if (M->parser_args->verbose_mode) {
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

  stringbuffer_append_string(M->ro->OutputBuffer, "};");
  stringbuffer_append_string(M->ro->OutputBuffer, "\n\n");
  stringbuffer_append_string(M->ro->OutputBuffer, "const size_t COLOR_NAMES_QTY = ");
  stringbuffer_append_unsigned_long(M->ro->OutputBuffer, M->ro->processed_colors_qty);
  stringbuffer_append_string(M->ro->OutputBuffer, ";\n");

  stringbuffer_append_string(M->ro->OutputBuffer, "const size_t COLOR_NAMES_PATH_SIZES = ");
  stringbuffer_append_unsigned_long(M->ro->OutputBuffer, M->ro->path_size_sum);
  stringbuffer_append_string(M->ro->OutputBuffer, ";\n");
  stringbuffer_append_string(M->ro->OutputBuffer, "\n");
  stringbuffer_append_string(M->ro->OutputBuffer, "#endif");
  stringbuffer_append_string(M->ro->OutputBuffer, "\n");

  if (M->parser_args->test_mode) {
    stringbuffer_append_string(M->ro->OutputBuffer, "\n//TEST MODE ENABLED\n");
    stringbuffer_append_string(M->ro->OutputBuffer, "#define TEST_MODE_ENABLED\n");
    stringbuffer_append_string(M->ro->OutputBuffer, (char *)M->test_main);
    stringbuffer_append_string(M->ro->OutputBuffer, "\n");
  }else{
    stringbuffer_append_string(M->ro->OutputBuffer, "//TEST MODE DISABLED\n");
  }

  int  wrote_bytes         = fs_write(M->parser_args->output_file, stringbuffer_to_string(M->ro->OutputBuffer));
  bool output_file_created = (bool)((fs_exists(M->parser_args->output_file) == 0) ? true : false);

  assert_eq(output_file_created, true, %d);
  int output_buffer_size = stringbuffer_get_content_size(M->ro->OutputBuffer);

  assert_eq(wrote_bytes, output_buffer_size, %d);

  sprintf(M->dur_msg,
          "Processed %lu Colors from %lu byte file %s with %d lines :: %s and wrote %d bytes to %s",
          M->ro->processed_colors_qty,
          M->ro->input_buffer_bytes,
          M->parser_args->input_file,
          M->ro->InputLines.count,
          dur,
          wrote_bytes,
          M->parser_args->output_file
          );

  stringbuffer_release(M->ro->OutputBuffer);
  stringbuffer_release(M->ro->InputBuffer);
  stringfn_release_strings_struct(M->ro->InputLines);
  djbhash_destroy(colorcsvparser1->djb__hash);
  free(M->parser_args->input_file);
  free(M->parser_args->output_file);
  free(M->ro);
  free(M->parser_args);
  OK(M->dur_msg);
  free(M->dur_msg);
  dbg("logic init OK", %s);
  return(0);
} /* colorcsvparser1_logicinit */


void colorcsvparser1_debug(){
  dbg(colorcsvparser1->loggermode, %d);
}


int colorcsvparser1_work(){
  int r;

  colorcsvparser1_debug();

  ////////////////////////////////////////////////////////
  colorcsvparser1_debug();

  return(0);
}


int colorcsvparser1_clean(){
  clib_module_free(colorcsvparser1);
  return(0);
}


int colorcsvparser1_modulemain(const int argc, const char **argv){
  int r;

  r = colorcsvparser1_logicinit();
  assert_eq(r, 0, %d);

  // r = colorcsvparser1_work();
  // assert_eq(r, 0, %d);

  r = colorcsvparser1_clean();
  assert_eq(r, 0, %d);

  OK("COLOR_PARSER_MODULE_LOGIC");
  return(0);
}


#undef M
#endif
