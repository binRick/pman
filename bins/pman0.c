#ifndef PMAN_C
#define PMAN_C
///////////////////////////
#include "../include/includes.h"
///////////////////////////
#include "../include/pman0-types.h"
///////////////////////////
#include "../include/pman0-defines.h"
#include "../src/pman0-init.c"
///////////////////////////
#include "../include/embedded-colornames-base.h"
///////////////////////////
#include "../src/palettes.c"
///////////////////////////
#include "../src/pman0-globals.c"
///////////////////////////
///////////////////////////
#include "../src/pman0-utils.c"
///////////////////////////
#include "../src/colorcodes.c"
///////////////////////////
///////////////////////////
///////////////////////////


static void select_palette(char *sel) {
  char   *evar, *eval, *line;
  FILE   *fp = fopen(sel, "r");
  size_t len = 255;

  line = malloc(sizeof(char) * len);

  if (fp == NULL) {
    fprintf(stderr, "Selected palette does not exist\n");
    exit(1);
  }

  while (fgets(line, len, fp) != NULL) {
    evar = strtok(line, "=");
    eval = strtok(NULL, "=");
    setenv(evar, eval, 1);
  }

  fclose(fp);
  free(line);
  /*
   * fp = fopen(conf, "w");
   * fprintf(fp, "%s", sel);
   * fclose(fp);
   * fp = popen(SEQUENCE, "w");
   * pclose(fp);
   */
}


static void list_palette(char *sel) {
  struct dirent **de;
  int           n = scandir(sel, &de, NULL, alphasort);

  /*
   * while (n--) {
   * if (de[n]->d_type == 8) {
   *  printf("%s/%s\n", mode, de[n]->d_name);
   * }
   * }
   */

  free(de);
}


static void random_palette(char *sel) {
  struct dirent **de;
  int           n = scandir(sel, &de, NULL, alphasort);

  srand(time(0));
  int i = (rand() % (n - 0 + 1)) + 0;

  /*
   * while (n--) {
   * if (i == n) {
   *  sval = de[n]->d_name;
   * }
   * }
   */
  free(de);
}


static void print_palette(void) {
  /*
   * FILE   *fp = fopen(conf, "r");
   * size_t len = 255;
   * char   *line;
   *
   * line = malloc(sizeof(char) * len);
   *
   * if (fp == NULL) {
   * fprintf(stderr, "No palette set or config file missing\n");
   * exit(1);
   * }
   *
   * fgets(line, len, fp);
   * puts(line);
   * fclose(fp);
   * free(line);
   *
   * printf(PALETTE);
   */
}
#include "../src/pman0-main.c"


#endif // PMAN_C
