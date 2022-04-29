#pragma once

#include "../include/includes.h"

//   pman Functions
static void pman_init() __attribute__((constructor));
static int pman_args(const int argc, const char **argv);

//   Utility Functions
static char *__basename(const char *);

//   Palette Functions
char *get_palette_data(const char *name);
char **get_palette_data_lines(const char *name);
char *get_palette_property_value(const char *name, const char *property);
int get_palette_data_lines_qty(const char *name);

//    Mode Functions
int print_default_palette_properties();
int print_current_palette_colors();
int view_default_palette();
int debug();
int list_color_names();
int list_color_names_and_rgb();
int list_color_rgbs();
int view_palette();
int list_palette_names();
int list_modes();
int debug_args();
int debug_error();
int debug_msg();
int debug_die();
int view_colorcode();

