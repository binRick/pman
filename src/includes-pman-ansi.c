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


/////////////////////////////////////////////////////////////////////////////////////////
bool is_in_rgb_range(struct RGB rgb) {
  if (
    rgb.red < 0
     || rgb.red > 1
     || rgb.green < 0
     || rgb.green > 1
     || rgb.blue < 0
     || rgb.blue > 1
    ) {
    return(false);
  }
  return(true);
}


float get_rgb_min(struct RGB rgb) {
  if (rgb.red <= rgb.green && rgb.red <= rgb.blue) {
    return(rgb.red);
  } else if (rgb.green <= rgb.blue) {
    return(rgb.green);
  } else {
    return(rgb.blue);
  }
}


float get_rgb_max(struct RGB rgb) {
  if (rgb.red >= rgb.green && rgb.red >= rgb.blue) {
    return(rgb.red);
  } else if (rgb.green >= rgb.blue) {
    return(rgb.green);
  } else {
    return(rgb.blue);
  }
}


/* returns max - min */
float get_rgb_range(struct RGB rgb) {
  return(get_rgb_max(rgb) - get_rgb_min(rgb));
}


/* rgb -> hsl luminance */
float rgb_to_hsl_luminance(struct RGB rgb) {
  return((get_rgb_min(rgb) + get_rgb_max(rgb)) / 2);
}


/* rgb -> hsl saturation */
float rgb_to_hsl_saturation(struct RGB rgb) {
  float min       = get_rgb_min(rgb);
  float max       = get_rgb_max(rgb);
  float luminance = rgb_to_hsl_luminance(rgb);

  if (luminance <= 0.5) {
    return((max - min) / (max + min));
  } else {
    return((max - min) / (2.0 - max - min));
  }
}


/* rgb -> hue */
float rgb_to_hue(struct RGB rgb) {
  float max   = get_rgb_max(rgb);
  float range = get_rgb_range(rgb);
  float hue;

  if (range == 0) {
    return(NAN);
  }

  if (rgb.red == max) {
    hue = fmodf((rgb.green - rgb.blue) / (range), 6);
  } else if (rgb.green == max) {
    hue = ((rgb.blue - rgb.red) / (range)) + 2;
  } else {
    hue = ((rgb.red - rgb.green) / (range)) + 4;
  }

  hue *= 60;
  if (hue < 0) {
    hue += 360;
  }
  return(hue);
}


/* rgb -> hsv value */
float rgb_to_hsv_value(struct RGB rgb) {
  if (!is_in_rgb_range(rgb)) {
    return(-1);
  }

  return(get_rgb_max(rgb));
}


/* rgb -> hsv saturation */
float rgb_to_hsv_saturation(struct RGB rgb) {
  if (!is_in_rgb_range(rgb)) {
    return(-1);
  }

  float value = rgb_to_hsv_value(rgb);

  if (value == 0) {
    return(-1);
  } else {
    return((get_rgb_range(rgb)) / value);
  }
}

