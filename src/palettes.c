#pragma once
/**********************************/
#include "../src/includes.c"


/**********************************/
int view_palette(){
#ifdef VEBOSE_DEBUG_MODE    
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
#else  
  printf("%s\n", get_palette_data((const char *)args->palette));
#endif  
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
  //fprintf(stderr, "name:%s|props qty:%d\n", name, qty);
  return(lines);
}


char *get_palette_data(const char *name){
  palette_t *ptr = (palette_t *)__embedded_table__;

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
#ifdef VERBOSE_DEBUG_MODE      
    fprintf(stderr,
      AC_RESETALL AC_BRIGHT_YELLOW_BLACK "#%d"
      AC_RESETALL "/"
      AC_RESETALL AC_BRIGHT_BLUE_BLACK "%lu"
      AC_RESETALL ">"
      AC_RESETALL ":: %s :: %db\n",
      i + 1, TEMPLATES_QTY,
      __embedded_table__[i].filename,
      __embedded_table__[i].size
      );
#else    
    printf(
      "%s\n",
      __basename(__embedded_table__[i].filename)
      );
#endif    
  }
  return(0);
}

int get_palette_data_properties_qty(const char *name){
  char **lines   = get_palette_data_lines(name);
  char **props   = malloc(1024);
  int  props_qty = 0;

  for (int i = 0; lines[i]; i++) {
    char **eq_split   = malloc(strlen(lines[i]) + 8);
    int  eq_split_qty = strsplit(lines[i], eq_split, "=");
    if (eq_split_qty == 2) {
      props_qty++;
    }
  }
  return(props_qty);
}


char **get_palette_data_properties(const char *name){
  char **lines   = get_palette_data_lines(name);
  char **props   = malloc(1024);
  int  props_qty = 0;

  for (int i = 0; lines[i]; i++) {
    char **eq_split   = malloc(strlen(lines[i]) + 8);
    int  eq_split_qty = strsplit(lines[i], eq_split, "=");
    if (eq_split_qty == 2) {
      props[props_qty] = strdup(eq_split[0]);
      props_qty++;
#ifdef VERBOSE_DEBUG_MODE
      printf(
        AC_RESETALL "> Line #%d:  " AC_RESETALL AC_BRIGHT_YELLOW_BLACK AC_REVERSED "\"%s\"" AC_RESETALL
        " "
        AC_RESETALL "prop:%s"
        " | "
        AC_RESETALL "val:%s"
        "\n",
        i,
        lines[i],
        eq_split[0],
        eq_split[1]
        );
#endif
    }
    free(eq_split);
  }
  props[props_qty] = NULL;
  free(lines);
  return(props);
}


int print_default_palette_properties(){
  char **props   = get_palette_data_properties(DEFAULT_PALETTE);
  int  props_qty = get_palette_data_properties_qty(DEFAULT_PALETTE);

#ifdef VERBOSE_DEBUG_MODE
  dbg(props_qty, %d);
  p(DEFAULT_PALETTE, "has", props_qty, "properties");
#endif
  for (int i = 0; i < props_qty; i++) {
    char    *prop_val = get_palette_property_value(DEFAULT_PALETTE, props[i]);
    short   prop_val_ok;
    int32_t _r = rgba_from_string(prop_val, &prop_val_ok);
    assert(prop_val_ok);
    rgba_t  prop_val_rgba  = rgba_new(_r);
    char    *prop_val_name = malloc(1024);

    rgba_to_string(prop_val_rgba, prop_val_name, 256);
    int red   = (uint32_t)_r >> 24 & 0xff;
    int green = (uint32_t)_r >> 16 & 0xff;
    int blue  = (uint32_t)_r >> 8 & 0xff;
    int alpha = (uint32_t)_r & 0xff;
#ifdef VERBOSE_DEBUG_MODE
    p("  >Property #", i, ":", props[i], "->", prop_val, "->", prop_val_name, " : red:", red, "|green:", green, "blue:", blue, "alpha:", alpha);
#endif
    free(prop_val); free(prop_val_name);
  }
  free(props);
  return(0);
}

