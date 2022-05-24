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
#define M                             require(colorcsvparser1)
////////////////////////////////////////////////////////////

int colorcsvparser1_logicinit(){
  colorcsvparser1 = require(colorcsvparser1);
  dbg(colorcsvparser1->loggermode, %d);
  M->loggermode             = LOGGER_DEBUG;
  M->djb__hash = malloc(sizeof(struct djbhash));
  assert_nonnull(M->djb__hash);
  djbhash_init(M->djb__hash);
  assert_nonnull(M->djb__hash);

  M->ro          = malloc(sizeof(struct render_t));
  M->parser_args = malloc(sizeof(pman_args_t));
  M->ro->input_file_exists = (int)fs_exists(parser_args->input_file);a

  


  assert_eq(ro->input_file_exists, 0, %d);

  ////////////////////////////////////////////////////////
  M->ro->OutputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(ro->OutputBuffer);
  M->ro->InputBuffer = stringbuffer_new_with_options(DEFAULT_BUFFER_SIZE, true);
  assert_nonnull(ro->InputBuffer);
  ////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->InputBuffer,  (char *)fs_read(parser_args->input_file));
  M->ro->input_buffer_bytes   = stringbuffer_get_content_size(ro->InputBuffer);
  assert_ge(ro->input_buffer_bytes, MIN_INPUT_FILE_SIZE, %lu);
  M->ro->InputLines = stringfn_split_lines_and_trim(stringbuffer_to_string(ro->InputBuffer));
  assert_ge(ro->InputLines.count, MIN_INPUT_FILE_LINES, %d);

  ////////////////////////////////////////////////////////
  stringbuffer_append_string(ro->OutputBuffer, COLOR_NAME_T_STRUCT_PREFIX);
  stringbuffer_append_string(ro->OutputBuffer, "#ifndef COLOR_NAME_STRUCT_DEFINED\n");
  stringbuffer_append_string(ro->OutputBuffer, "#define COLOR_NAME_STRUCT_DEFINED\n\n");
  stringbuffer_append_string(ro->OutputBuffer, COLOR_NAME_T_STRUCT);
  stringbuffer_append_string(ro->OutputBuffer, "color_name_t COLOR_NAMES[] = {\n");
  ////////////////////////////////////////////////////////

  for (unsigned long i = 0; (i < M->roInputLines.count) && (ro->processed_colors_qty < M->parser_argsmax_colors_qty) && (ro->processed_colors_qty <= MAX_COLORS_QTY); i++) {
    M->roprocessed_colors_qty++;

    if (strlen(ro->InputLines.strings[i]) < MIN_INPUT_FILE_LINES || strsplit(ro->InputLines.strings[i], M->split_csv_buffer_lines, ",") != CSV_INPUT_FIELDS_QTY) {
     continue;
    }

    color_name_t *cn = malloc(sizeof(color_name_t));
    assert_nonnull(cn);

    cn->name                   = trim(M->split_csv_buffer_lines[CSV_NAME_FIELD_OFFSET]);
    assert_ge(strlen(cn->name), MIN_COLOR_NAME_LEN, %lu);
    cn->name[strlen(cn->name)] = '\0';

    cn->hex          = case_upper(trim(M->split_csv_buffer_lines[CSV_HEX_FIELD_OFFSET]));
    cn->hex[HEX_LEN] = '\0';

    if (strlen(cn->name) < MIN_COLOR_NAME_LEN || strlen(cn->hex) != HEX_LEN) {
     continue;
    }

    assert_eq(strlen(cn->hex), HEX_LEN, %lu);

    short prop_val_ok;
    uint32_t _rgba = rgba_from_string(cn->hex, &prop_val_ok);
    assert_eq(prop_val_ok, 1, %d);

    rgba_t prop_val_rgba = rgba_new(_rgba);

    assert_le(prop_val_rgba.r, 1.0, %f);
    assert_le(prop_val_rgba.g, 1.0, %f);
    assert_le(prop_val_rgba.b, 1.0, %f);
    assert_le(prop_val_rgba.a, 1.0, %f);

    assert_ge(prop_val_rgba.r, RGB_MIN_VAL, %f);
    assert_ge(prop_val_rgba.g, RGB_MIN_VAL, %f);
    assert_ge(prop_val_rgba.b, RGB_MIN_VAL, %f);
    assert_ge(prop_val_rgba.a, RGB_MIN_VAL, %f);


    cn->red               = (uint32_t)_rgba >> 24 & 0xff;
    assert_ge(cn->red, RGB_MIN_VAL, %d);
    assert_le(cn->red, RGB_MAX_VAL, %d);
    cn->green             = (uint32_t)_rgba >> 16 & 0xff;
    assert_ge(cn->green, RGB_MIN_VAL, %d);
    assert_le(cn->green, RGB_MAX_VAL, %d);
    cn->blue              = (uint32_t)_rgba >> 8 & 0xff;
    assert_ge(cn->blue, RGB_MIN_VAL, %d);
    assert_le(cn->blue, RGB_MAX_VAL, %d);
    cn->alpha             = (uint32_t)_rgba & 0xff;
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

    stringbuffer_append_string(ro->OutputBuffer, __dat);
    M->ropath_size_sum += path_size;

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
  stringbuffer_append_unsigned_long(ro->OutputBuffer, M->roprocessed_colors_qty);
  stringbuffer_append_string(ro->OutputBuffer, ";\n");

  stringbuffer_append_string(ro->OutputBuffer, "const size_t COLOR_NAMES_PATH_SIZES = ");
  stringbuffer_append_unsigned_long(ro->OutputBuffer, M->ropath_size_sum);
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

  int wrote_bytes = fs_write(parser_args->output_file, stringbuffer_to_string(ro->OutputBuffer));
  bool output_file_created = (bool)((fs_exists(parser_args->output_file) == 0) ? true : false);
  assert_eq(output_file_created, true, %d);
  int output_buffer_size = stringbuffer_get_content_size(ro->OutputBuffer);
  assert_eq(wrote_bytes, output_buffer_size, %d);

  sprintf(M->dur_msg,
    "Processed %lu Colors from %lu byte file %s with %d lines :: %s and wrote %d bytes to %s",
    M->roprocessed_colors_qty,
    M->roinput_buffer_bytes,
    M->parser_argsinput_file,
    M->roInputLines.count,
    dur,
    wrote_bytes,
    M->parser_argsoutput_file
    );

  stringbuffer_release(ro->OutputBuffer);
  stringbuffer_release(ro->InputBuffer);
  stringfn_release_strings_struct(ro->InputLines);
  djbhash_destroy(colorcsvparser1->djb__hash);
  free(parser_args->input_file);
  free(parser_args->output_file);
  free(ro);
  free(parser_args);
  OK(M->dur_msg);
  free(M->dur_msg);
  dbg("logic init OK", %s);
  return(0);

}


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
  r = init_parser_args(argc,argv);
  assert_eq(r, 0, %d);

  r = colorcsvparser1_logicinit();
  assert_eq(r, 0, %d);

  r = colorcsvparser1_work();
  assert_eq(r, 0, %d);

  r = colorcsvparser1_clean();
  assert_eq(r, 0, %d);

  OK("COLOR_PARSER_MODULE_LOGIC");
  return(0);
}



#undef M
#endif
