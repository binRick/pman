#pragma once

#include "../include/includes.h"

//   pman Functions
static void pman_init() __attribute__((constructor));
static int pman_args(const int argc, const char **argv);

//   Utility Functions
static char *__basename(const char *);

//   Palette Functions
char *get_palette_data(const char *name);
void *get_palette_data_i(const char *name);
char **get_palette_data_lines(const char *name);
char *get_palette_property_value(const char *name, const char *property);
int get_palette_data_lines_qty(const char *name);

//    Mode Functions
int print_default_palette_properties();
int print_current_palette_colors();
int view_default_palette();
int debug();
int view_palette();
int list_palette_names();
int iterate_templates();
int list_palettes();
int list_modes();
int test_hex1();
int debug_args();
int debug_error();
int debug_msg();
int debug_die();
int list_template();

