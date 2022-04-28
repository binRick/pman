#ifndef __PALETTES_C
#define __PALETTES_C

#include "../include/includes.h"
#include "../src/globals.c"
#include "../src/includes.c"


int pc1(void){
  int i, j, n;

  for (i = 0; i < 11; i++) {
    for (j = 0; j < 10; j++) {
      n = 10 * i + j;
      if (n > 107) {
        break;
      }
//            printf("\n  n:%d|j:%d|i:%d\n  -033[%dm %3d-033[m\n\n", n,j,i, n, n);
      printf("\033[%dm %3d\033[m", n, n);
    }
    printf("\n");
  }
  return(0);
}


int print_current_palette_colors(){
  printf("print_current_palette_colors>\n");
  printf(CURRENT_PALETTE);
  //pc1();
}


char *get_palette_property_value(const char *name, const char *property){
  char *pd     = get_palette_data(name);
  char **lines = malloc(16 * 24);
  int  qty     = strsplit(pd, lines, "\n");

  for (int i = 0; i < qty; i++) {
    char **eq_split   = malloc(strlen(lines[i]) + 8);
    int  eq_split_qty = strsplit(lines[i], eq_split, "=");
    if (eq_split_qty == 2 && strcmp(eq_split[0], property) == 0) {
      char *v = strdup(eq_split[1]);
      free(eq_split);
      free(lines);
      free(pd);
      return(v);
    }
  }
  return(NULL);
}


void *get_palette_data_i(**PALETTE_t){
  char *dat = "ok123";

  return((void *)dat);
}


int get_palette_data_lines_qty(const char *name){
  char *pd     = get_palette_data(name);
  char **lines = malloc(16 * 24);
  int  qty     = strsplit(pd, lines, "\n");

  free(lines);
  return(qty);
}


char **get_palette_data_lines(const char *name){
  char *pd     = get_palette_data(name);
  char **lines = malloc(16 * 24);
  int  qty     = strsplit(pd, lines, "\n");

  fprintf("name:%s|props qty:%d\n", name, qty);
  return(lines);
}


char *get_palette_data(char *name){
  PALETTE_t *ptr = __embedded_table__;

  // char *pd = (char*)get_palette_data_i(ptr);
//    return(pd);
  for (int i = 0; i < TEMPLATES_QTY; i++, ptr++ ) {
    if (
      (__embedded_table__[i].data)
       && (
        (strcmp(name, __embedded_table__[i].filename) == 0)
          ||
        (strcmp(name, __basename(__embedded_table__[i].filename)) == 0)
        )
      ) {
      return(strdup((char *)__embedded_table__[i].data));
    }
  }

  return(NULL);
}


int list_palette_names(){
  PALETTE_t *ptr = __embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      "%s\n",
      __basename(__embedded_table__[i].filename)
      );
  }
  return(0);
}


int list_templates(){
  PALETTE_t *ptr = __embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK "%s",
      __embedded_table__[i].filename
      );
  }
  return(0);
}


int list_palettes(){
  PALETTE_t *ptr = __embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK "#%d"
      AC_RESETALL "/"
      AC_RESETALL AC_BRIGHT_BLUE_BLACK "%d"
      AC_RESETALL ">"
      AC_RESETALL ":: %s :: %db\n",
      i + 1, TEMPLATES_QTY,
      __embedded_table__[i].filename,
      __embedded_table__[i].size
      );
    char *d = get_palette_data(__embedded_table__[i].filename);
    printf("d=%s\n", d);
  }
  return(0);
}

#endif
