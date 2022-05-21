// MESON_BIN_ENABLED=true
////////////////////////////////////////////////////
#include "../src/includes.c"
////////////////////////////////////////////////////
#include "../include/embedded-colornames-dev.h"
#include "../include/pman0-types.h"


////////////////////////////////////////////////////


void ansi_bar_fg(color_name_t *cn){
  _change_terminal_color_name(cn);
  printf("##################################################\n");
  _reset_terminal_to_default_color();
}


void ansi_bar(color_name_t *cn){
  _change_terminal_color_name_fg(cn);
  //printf("##################################################\n");
  printf("                                                  \n");
  _reset_terminal_to_default_color();
}


int main(const int argc, const char **argv){
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    if ((i < 10) || (i > (COLOR_NAMES_QTY - 10))) {
      if ((argc == 2) && (strcmp(argv[1], "--test") == 0)) {
        if (i >= 10) {
          exit(0);
        }
      }
      _change_terminal_color_name(&COLOR_NAMES[i]);
      printf("|%s|%s|%lubyte image|%s|\n",
             COLOR_NAMES[i].name,
             COLOR_NAMES[i].hex,
             COLOR_NAMES[i].path_size,
             COLOR_NAMES[i].encoded_path_contents
             );
      _reset_terminal_to_default_color();

      //ansi_bar(&COLOR_NAMES[i]);
    }
  }
  dbg(COLOR_NAMES_QTY, %lu);
  OK("Done");
  return(0);
}
