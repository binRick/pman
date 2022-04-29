#include "../include/includes.h"

/***********************/

short prop_val_ok;


int main(const int argc, const char **argv) {
  int  err, done, qty = 0;
  FILE *fp = fopen(argv[1], "r");

  printf("typedef struct color_names_t {\n\
    char *name;\n\
    char *rgb;\n\
    char *hex;\n\
    int red;\n\
    int green;\n\
    int blue;\n\
    int alpha;\n\
    uint32_t rgba;\n\
    char *encoded_log;\n\
    int encoded_log_bytes;\n\
};\nstruct color_names_t COLOR_NAMES[] = {\n");

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

    int32_t _r = rgba_from_string(rgb_hex, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t  prop_val_rgba = rgba_new(_r);

    char    *name = trim(r[0]);
    int     red   = (uint32_t)_r >> 24 & 0xff;
    int     green = (uint32_t)_r >> 16 & 0xff;
    int     blue  = (uint32_t)_r >> 8 & 0xff;
    int     alpha = (uint32_t)_r & 0xff;
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
    char *log_file = malloc(1024);
    char *RGB      = case_upper(rgb);
    sprintf(log_file, "%s", RGB);


    int exists = fs_exists(log_file);
    int ls     = fs_size(log_file);
    if (ls < 10) {
      continue;
    }
    //fprintf(stderr, "log %s exists? %d, size:%d\n", log_file, exists, ls);
    char *dat = fs_read(log_file);
    // fprintf(stderr, "%s\n",dat);
    assert(strlen(dat) > 0);

    char *dat_encoded = b64_encode((const unsigned char *)dat, strlen(dat));
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
    qty++;
  }

  fprintf(stdout, "\t{ NULL },\n};\nconst size_t COLOR_NAMES_QTY = %d;\n", qty);
  return(0);
} /* main */
