#ifndef __KFC_H__
#define __KFC_H__

#include "../include/includes.h"

static int pman_args(const int argc, const char **argv);
static void pman_init() __attribute__((constructor));
static char *__basename(const char *);

char *get_palette_data(char *name);

void *get_palette_data_i(**PALETTE_t);
char **get_palette_data_lines(const char *name);
char *get_palette_property_value(const char *name, const char *property);
int get_palette_data_lines_qty(const char *name);

//    modes
int print_current_palette_colors();
int debug();
int view_palette();
int list_palette_names();
int iterate_templates();
int list_palettes();
int list_modes();
int test_hex1();
int debug_args();
int list_template();


#endif
