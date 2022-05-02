// MESON_BIN_ENABLED=true
#include "../include/includes.h"
////////////////////////////////////////////////////
#include "../include/embedded-colornames-dev.h"
////////////////////////////////////////////////////
#include "../include/pman0-types.h"


////////////////////////////////////////////////////


void ansi_bar_fg(dev_color_name_t *cn){
  _change_terminal_color_name(cn);
  printf("##################################################\n");
  _reset_terminal_to_default_color();
}


void ansi_bar(dev_color_name_t *cn){
  _change_terminal_color_name_fg(cn);
  //printf("##################################################\n");
  printf("                                                  \n");
  _reset_terminal_to_default_color();
}


int main(const int argc, const char **argv){
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    if ((i < 10) || (i > (COLOR_NAMES_QTY - 10))) {
      ansi_bar(&COLOR_NAMES[i]);
      continue;
      _change_terminal_color_name(&COLOR_NAMES[i]);
      printf("%s|%s\n",
             COLOR_NAMES[i].name,
             COLOR_NAMES[i].hex
             );
      _reset_terminal_to_default_color();
    }
  }
  dbg(COLOR_NAMES_QTY, %lu);
  OK("Done");
  return(0);
}
