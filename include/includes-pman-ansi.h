#pragma once
#include "../include/includes.h"
//////////////////////////////////////////////////////////
/***********************/// Control Code CONSTANTS
#define C256_FG_CODE              "\x1b[38;5;%dm"
#define C256_BG_CODE              "\x1b[48;5;%dm"
#define TRUECOLOR_FG_CODE         "\x1b[38;2;%d;%d;%dm"
#define TRUECOLOR_BG_CODE         "\x1b[48;2;%d;%d;%dm"
#define RESET_CODE                "\x1b[0m"
#define COLOR_RGB                 L"\033[38;2;%u;%u;%um"
#define COLOR_RESET_TO_DEFAULT    L"\033[0m"
/***********************/// HEX COLOR CONSTANTS
#define HEX_LEN                   6
static const char *HEX_VALUES = "0123456789ABCDEF";
/***********************///
#define LAB_XYZ_SIGMA             (6.0 / 29.0)
#define LAB_XYZ_SIGMA_SQUARED     (LAB_XYZ_SIGMA * LAB_XYZ_SIGMA)
#define LAB_XYZ_SIGMA_CUBED       (LAB_XYZ_SIGMA_SQUARED * LAB_XYZ_SIGMA)
#define XYZ_D65_XN                0.95047
#define XYZ_D65_YN                1.0
#define XYZ_D65_ZN                1.08883
#define VAL_25_POW_7              6103515625
/***********************/// ANSI COLOR CONSTANTS
#define ANSI_MIN                  16
#define ANSI_MAX                  256
#define ANSI_MAP_OFFSET           ANSI_MIN
#define ANSI_MAP_LEN              (ANSI_MAX - ANSI_MAP_OFFSET)
//////////////////////////////////////////////////////////
#define ESCAPE                    "\x1b"
#define BOLD                      ESCAPE "[1m"
#define DIM                       ESCAPE "[2m"
#define ITALIC                    ESCAPE "[3m"
#define UNDER                     ESCAPE "[4m"
#define BLINK                     ESCAPE "[5m"
#define INVERSE                   ESCAPE "[7m"
#define STRIKE                    ESCAPE "[8m"
// Text 256 colors
#define FG_256(code)       printf(ESCAPE "[38;5;" #code "m")
#define BG_256(code)       printf(ESCAPE "[48;5;" #code "m")
// Text RGB colors
#define FG_RGB(r, g, b)    printf(ESCAPE "[38;2;" #r ";" #g ";" #b "m")
#define BG_RGB(r, g, b)    printf(ESCAPE "[48;2;" #r ";" #g ";" #b "m")
// Disable colors
#define FG_DISABLE()       printf(ESCAPE "[39m")
#define BG_DISABLE()       printf(ESCAPE "[49m")
// Terminal utilities
#define CLEAR()            printf(ESCAPE "c")
#define RESET    ESCAPE "[0m" ESCAPE "[49m"
#define RESETF()           printf(ESCAPE "[0m" ESCAPE "[49m")
#define OUTPUT_HIDE()      printf(ESCAPE "^")
// Cursor attributes
#define CURSOR_HIDE()      printf(ESCAPE "[?25l")
#define CURSOR_SHOW()      printf(ESCAPE "[?25h")
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
struct hexstring { char hex[7]; };
struct RGB_Double { double r;   double g;   double b; };
struct RGB_Int { int r;     int g;   int b; };
struct HSV_Double { double h;    double s;   double v; };
//////////////////////////////////////////////////////////
typedef struct { double L;   double a;   double b; }        LabColor;
typedef struct { double L;   double C;   double h; }        LChColor;
typedef struct { double r;   double g;    double b; }       RGBColor;
typedef struct { double rl;    double gl;    double bl; }   SRGBColor;
typedef struct { double x;    double y;   double z; }       XYZColor;
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
  3.2406255,  -1.537208,  -0.4986286,
  -0.9689307, 1.8757561,  0.0415175,
  0.0557101,  -0.2040211, 1.0569959,
};
//////////////////////////////////////////////////////////
struct RGB {
  float red;
  float green;
  float blue;
};

struct HSL {
  float hue;
  float saturation;
  float luminance;
};

struct HSV {
  float hue;
  float saturation;
  float value;
};

bool is_in_rgb_range(struct RGB rgb);
float get_rgb_min(struct RGB rgb);
float get_rgb_max(struct RGB rgb);
float get_rgb_range(struct RGB rgb);

float rgb_to_hue(struct RGB rgb);

float rgb_to_hsl_luminance(struct RGB rgb);
float rgb_to_hsl_saturation(struct RGB rgb);

float rgb_to_hsv_value(struct RGB rgb);
float rgb_to_hsv_saturation(struct RGB rgb);

//////////////////////////////////////////////////////////
