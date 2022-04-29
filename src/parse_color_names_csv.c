#pragma once
#define DBG_H_DEF_ONCE
#include "../include/includes.h"
/***********************/
#define DEFAULT_QTY_LIMIT     10
#define VERBOSE_DEBUG_MODE    false
const char *DEFAULT_COLOR_CODES_CSV_FILE = "./etc/colornames.csv";
const char *DEFAULT_COLOR_LOGS_DIRECTORY = "./etc/color-logs";
/***********************/

/***********************/
size_t qty; FILE *fp;
char   *COLOR_CODES_CSV_FILE;
/***********************/


void print_prefix(){
  fprintf(stdout, "#pragma once");
  fprintf(stdout, "\n#include \"../include/includes.h\"");
  fprintf(stdout, "\n#include \"../include/types.h\"");
  fprintf(stdout, "\n#ifndef COLOR_NAMES_DEFINED\n#define COLOR_NAMES_DEFINED\n");
  fprintf(stdout, "\ncolor_name_t COLOR_NAMES[] = {\n");
}


void print_suffix(){
  fprintf(stdout, "\t{ NULL },\n};\n\nconst size_t COLOR_NAMES_QTY = %lu;\n\n#endif", qty);
  fprintf(stdout, "\n");
}


int main(const int argc, const char **argv) {
  int err, done;  short prop_val_ok;

  COLOR_CODES_CSV_FILE = malloc(1024);
  if (argc > 1) {
    sprintf(COLOR_CODES_CSV_FILE, "%s", argv[1]);
  }else{
    sprintf(COLOR_CODES_CSV_FILE, "%s", DEFAULT_COLOR_CODES_CSV_FILE);
  }
  fp = fopen(COLOR_CODES_CSV_FILE, "r");
  if (VERBOSE_DEBUG_MODE) {
    fprintf(stderr, "csv=%s\n", COLOR_CODES_CSV_FILE);
  }
  assert(fp);

  print_prefix();

  while (1) {
    char *txt = fread_csv_line(fp, 1024, &done, &err);
    if (done == 1) {
      break;
    }
    assert(err != CSV_ERR_NO_MEMORY);
    assert(txt);
    char **r = parse_csv(txt);
    assert(r);

    char *rgb_hex = case_upper(trim(r[1]));
    char *rgb     = str_replace(rgb_hex, "#", "");
    if (strlen(rgb) != 6) {
      continue;
    }

    int32_t  _r = rgba_from_string(rgb_hex, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t   prop_val_rgba = rgba_new(_r);

    char     *name = trim(r[0]);
    uint32_t red   = (uint32_t)_r >> 24 & 0xff;
    uint32_t green = (uint32_t)_r >> 16 & 0xff;
    uint32_t blue  = (uint32_t)_r >> 8 & 0xff;
    uint32_t alpha = (uint32_t)_r & 0xff;
    if (red < 0 || red > 256) {
      continue;
    }
    if (green < 0 || green > 256) {
      continue;
    }
    if (blue < 0 || blue > 256) {
      continue;
    }
    if (alpha < 0 || alpha > 256) {
      continue;
    }
    char *RGB = case_upper(rgb);

    char *log_file = malloc(1024);
    sprintf(log_file, "%s/%s", DEFAULT_COLOR_LOGS_DIRECTORY, RGB);
    if (VERBOSE_DEBUG_MODE) {
      fprintf(stderr, "log_file=%s\n", COLOR_CODES_CSV_FILE);
    }

    int exists = fs_exists(log_file);
    int ls     = fs_size(log_file);
    if (ls < 10) {
      continue;
    }
    if (VERBOSE_DEBUG_MODE) {
      fprintf(stderr, "log %s exists? %d, size:%d\n", log_file, exists, ls);
    }
    char *dat = fs_read(log_file);
    free(log_file);
    free(RGB);
    assert(strlen(dat) > 0);

    char *dat_encoded = (char *)b64_encode((const unsigned char *)dat, strlen(dat));
    //fprintf(stderr, "%s\n",dat_encoded);
    assert(strlen(dat_encoded) > 0);

    fprintf(stdout, "\t{ \"%s\", \"%s\", \"%s\", %d, %d, %d, %d, %lu, \"%s\", %lu },\n",
            name,
            rgb,
            rgb_hex,
            red, green, blue, alpha,
            _r,
            dat_encoded,
            strlen(dat_encoded)
            );

//    free(name);
//    free(txt);
//    free(r);
//    free(rgb);
    qty++;
  }
  print_suffix();
  return(0);
} /* main */
