#pragma once
#include "../include/includes.h"
//////////////////////////////////////////////////////////
/***********************/// Control Code CONSTANTS
#define C256_FG_CODE "\x1b[38;5;%dm"
#define C256_BG_CODE "\x1b[48;5;%dm"
#define TRUECOLOR_FG_CODE "\x1b[38;2;%d;%d;%dm"
#define TRUECOLOR_BG_CODE "\x1b[48;2;%d;%d;%dm"
#define RESET_CODE "\x1b[0m"
#define COLOR_RGB                         L"\033[38;2;%u;%u;%um"
#define COLOR_RESET_TO_DEFAULT            L"\033[0m"
/***********************/// HEX COLOR CONSTANTS
#define HEX_LEN 6
static const char *HEX_VALUES = "0123456789ABCDEF";
/***********************///
#define LAB_XYZ_SIGMA (6.0 / 29.0)
#define LAB_XYZ_SIGMA_SQUARED (LAB_XYZ_SIGMA * LAB_XYZ_SIGMA)
#define LAB_XYZ_SIGMA_CUBED (LAB_XYZ_SIGMA_SQUARED * LAB_XYZ_SIGMA)
#define XYZ_D65_XN 0.95047
#define XYZ_D65_YN 1.0
#define XYZ_D65_ZN 1.08883
#define VAL_25_POW_7 6103515625
/***********************/// ANSI COLOR CONSTANTS
#define ANSI_MIN 16
#define ANSI_MAX 256
#define ANSI_MAP_OFFSET ANSI_MIN
#define ANSI_MAP_LEN (ANSI_MAX - ANSI_MAP_OFFSET)
//////////////////////////////////////////////////////////
typedef struct ColorInfo {
  const char *name;
  const char *hex;
  struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
  } rgb;
} ColorInfo;
struct hexstring{ char hex[7]; };
struct RGB_Double{   double r;   double g;   double b; };
struct RGB_Int{   int r;     int g;   int b; };
struct HSV_Double{   double h;    double s;   double v; };
//////////////////////////////////////////////////////////
typedef struct {    double L;   double a;   double b; } LabColor;
typedef struct {    double L;   double C;   double h; } LChColor;
typedef struct {    double r;   double g;    double b; } RGBColor;
typedef struct {   double rl;    double gl;    double bl; } SRGBColor;
typedef struct {   double x;    double y;   double z; } XYZColor;
//////////////////////////////////////////////////////////
void print_ansi_color(int red, int green, int blue, int wl, char *word);
void print_ansi_to_rgb(int ansi_code);
//////////////////////////////////////////////////////////
void ansi_256_fg(FILE *file, int color);
void ansi_256_bg(FILE *file, int color);
void ansi_truecolor_fg(FILE *file, int r, int g, int b);
void ansi_truecolor_bg(FILE *file, int r, int g, int b);
void ansi_reset(FILE *file);
//////////////////////////////////////////////////////////
static const double srgb_to_xyz_matrix[] = {
      0.4124, 0.3576, 0.1805,
      0.2126, 0.7152, 0.0722,
      0.0193, 0.1192, 0.9505,
};
static const double xyz_to_srgb_matrix[] = {
      3.2406255, -1.537208, -0.4986286,
      -0.9689307, 1.8757561, 0.0415175,
      0.0557101, -0.2040211, 1.0569959,
};
//////////////////////////////////////////////////////////
