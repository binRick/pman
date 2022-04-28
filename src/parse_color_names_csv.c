#include "../include/includes.h"
#include "../src/includes.c"


/***********************/


int main(const int argc, const char **argv) {
  int  err, done, qty = 0;
  FILE *fp = fopen(argv[1], "r");

  printf("typedef struct color_names_t {\n\
    char *name;\n\
    char *rgb;\n\
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
    qty++;
    fprintf(stdout, "\t{ \"%s\", \"%s\" },\n", trim(r[0]), trim(r[1]));
  }

  fprintf(stdout, "\t{ NULL },\n};\nconst size_t COLOR_NAMES_QTY = %d;\n", qty);
  return(0);
}
