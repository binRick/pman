#pragma once
#include "../include/includes.h"


////////////////////////////////////////////////////////////////////////////
void print_ansi_color(int red, int green, int blue, int wl, char *word) {
  for (int i = 0; i < wl; i++) {
    red   = ((255 / wl) * i);
    green = ((255 / wl) * i);
    blue  = ((255 / wl) * i);
    int x = (int)red;
    int y = (int)green;
    int z = (int)blue;
    printf("{%d,%d,%d}%c", x, y, z, word[i]);
  }
}


////////////////////////////////////////////////////////////////////////////
void print_ansi_to_rgb(int ansi_code) {
  RGBColor rgb = ansi_to_rgb(ansi_code);
  int      r = 0, g = 0, b = 0;

  rgb_to_ints(rgb, &r, &g, &b);
  printf("%d %d %d\n", r, g, b);
}


////////////////////////////////////////////////////////////////////////////
void print_rgb_to_ansi(int r, int g, int b) {
  int ansi_code = approxdb_closest_to_rgb(r, g, b);

  printf("%d\n", ansi_code);
}


////////////////////////////////////////////////////////////////////////////
void ansi_256_fg(FILE *file, int color) {
  fprintf(file, C256_FG_CODE, color);
}


void ansi_256_bg(FILE *file, int color) {
  fprintf(file, C256_BG_CODE, color);
}


void ansi_truecolor_fg(FILE *file, int r, int g, int b) {
  fprintf(file, TRUECOLOR_FG_CODE, r, g, b);
}


void ansi_truecolor_bg(FILE *file, int r, int g, int b) {
  fprintf(file, TRUECOLOR_BG_CODE, r, g, b);
}


void ansi_reset(FILE *file) {
  fputs(RESET_CODE, file);
}
////////////////////////////////////////////////////////////////////////////
