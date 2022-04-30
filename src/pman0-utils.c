#pragma once
#include "../include/includes.h"
#include "../src/colorcodes.c"


int __view_colorcode(const char *name) {
  color_name_t *cc = get_color_code_t_by_name(name);

  printf(
    AC_RESETALL AC_BRIGHT_YELLOW "name:%s|rgb:%s" AC_RESETALL
    "\n",
    cc->name,
    cc->rgb
    );
  return(0);
}


char **get_color_rgbs() {
  char **rgbs = malloc(COLOR_NAMES_QTY * 6 + 1);

  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    rgbs[i] = strdup(COLOR_NAMES[i].rgb);
  }
  return(rgbs);
}


int list_color_rgbs() {
  char **rgbs = get_color_rgbs();

  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf(
      AC_RESETALL AC_BRIGHT_MAGENTA AC_UNDERLINE "RGB: %s\n" AC_RESETALL
      AC_RESETALL ""  AC_BRIGHT_BLUE AC_UNDERLINE "Name:" AC_RESETALL " " "%s" AC_RESETALL "\n"
      AC_RESETALL ""  AC_BRIGHT_BLUE AC_UNDERLINE "Color:" AC_RESETALL " " "%s" AC_RESETALL "\n"
      AC_RESETALL "\t"  AC_BRIGHT_BLUE AC_UNDERLINE "RGB Table:" AC_RESETALL "\n" "%s" "\n" AC_RESETALL
      AC_RESETALL "\t"  AC_BRIGHT_BLUE AC_UNDERLINE "Attributes Table:" AC_RESETALL "\n" "%s" "\n" AC_RESETALL
      "\n=====================\n",
      rgbs[i],
      get_color_code_name(rgbs[i]),
      get_color_code_yourcolor(rgbs[i]),
      get_color_code_rgb_table(rgbs[i]),
      get_color_code_attributes(rgbs[i])
      );
  }
  return(0);
}


int list_color_names_and_rgbs() {
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf("%s:%s\n", COLOR_NAMES[i].name, COLOR_NAMES[i].rgb);
#ifdef VERBOSE_DEBUG_MODE
    printf(
      AC_RESETALL AC_BRIGHT_YELLOW "name:%s" AC_RESETALL
      "|"
      AC_RESETALL AC_BRIGHT_GREEN  "rgb:%s" AC_RESETALL
      "|RGB=%d/%d/%d|alpha=%d|rgba=%lu||hex=%s|"
      "\n",
      COLOR_NAMES[i].name,
      COLOR_NAMES[i].rgb,
      COLOR_NAMES[i].red,
      COLOR_NAMES[i].green,
      COLOR_NAMES[i].blue,
      COLOR_NAMES[i].alpha,
      COLOR_NAMES[i].rgba,
      COLOR_NAMES[i].hex
      );
#endif
  }
  return(0);
}


int list_color_names() {
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf("%s\n",
           COLOR_NAMES[i].name
           );
  }
  return(0);
}


int debug_error(){
  DO_ERR("some error"); return(0);
}


int debug_msg(){
  DO_MSG("some message"); return(0);
}


int debug_die(){
  DO_DIE("critical error"); return(0);
}


static char *__basename(const char *path){
  const char *slash = strrchr(path, '/');

  if (slash) {
    path = slash + 1;
  }
  return((char *)path);
}
