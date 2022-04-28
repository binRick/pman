#pragma once
#include "../src/includes.c"


int view_palette(){
  printf(
    AC_RESETALL AC_BRIGHT_YELLOW AC_REVERSED "%s"
    AC_RESETALL ":"
    AC_RESETALL "(%d lines)"
    AC_RESETALL " :: cursor=%s | color07=%s"
    AC_RESETALL "\n"
    AC_RESETALL AC_BOLD "%s"
    AC_RESETALL "\n",
    __basename((const char *)args->palette),
    get_palette_data_lines_qty((const char *)args->palette),
    get_palette_property_value((const char *)args->palette, "cursor"),
    get_palette_property_value((const char *)args->palette, "color07"),
    get_palette_data((const char *)args->palette)
    );
  palette_t *ptr = (palette_t *)__embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    if (strcmp(__basename(__embedded_table__[i].filename), args->palette) == 0) {
    }
  }
  return(0);
}


int view_default_palette(){
  args->palette = DEFAULT_PALETTE;
  return(view_palette());
}


int print_current_palette_colors(){
  printf(CURRENT_PALETTE);
  return(0);
}


char *get_palette_property_value(const char *name, const char *property){
  char *pd     = get_palette_data((char *)name);
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


void *get_palette_data_i(const char *name){
  char *dat = "ok123";

  return((void *)dat);
}


int get_palette_data_lines_qty(const char *name){
  char *pd     = get_palette_data(name);
  char **lines = malloc(strlen(name) + 1);
  int  qty     = strsplit(pd, lines, "\n");

  free(lines);
  free(pd);
  return(qty);
}


char **get_palette_data_lines(const char *name){
  char *pd     = get_palette_data(name);
  char **lines = malloc(1024 * 4);
  int  qty     = strsplit(pd, lines, "\n");

  lines[qty] = NULL;
  fprintf(stderr, "name:%s|props qty:%d\n", name, qty);
  return(lines);
}


char *get_palette_data(const char *name){
  palette_t *ptr = (palette_t *)__embedded_table__;

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
  palette_t *ptr = (palette_t *)__embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      "%s\n",
      __basename(__embedded_table__[i].filename)
      );
  }
  return(0);
}


int list_templates(){
  palette_t *ptr = (palette_t *)__embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK "%s",
      __embedded_table__[i].filename
      );
  }
  return(0);
}


int list_palettes(){
  palette_t *ptr = (palette_t *)__embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK "#%d"
      AC_RESETALL "/"
      AC_RESETALL AC_BRIGHT_BLUE_BLACK "%lu"
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


char **get_palette_data_properties(const char *name){
  p("number:", 25, "fractional number:", 1.2345, "expression:", (2.0 + 5) / 3);
  char **lines   = get_palette_data_lines(name);
  char **props   = malloc(1024);
  int  props_qty = 0;

  for (int i = 0; lines[i]; i++) {
    printf("#%d> line:%s\n", i, lines[i]);
    char **eq_split   = malloc(strlen(lines[i]) + 8);
    int  eq_split_qty = strsplit(lines[i], eq_split, "=");
    if (eq_split_qty == 2) {
      props[props_qty] = strdup(eq_split[0]);
      props_qty++;
    }
    free(eq_split);
  }
  free(lines);
  props[props_qty] = NULL;
  return(props);
}


int print_default_palette_properties(){
  dbg("ok123", % s);
  get_palette_data_properties(DEFAULT_PALETTE);
  return(0);
}

