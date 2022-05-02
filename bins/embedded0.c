#include "../include/includes.h"
// MESON_BIN_ENABLED=true
#include "../include/embedded-colornames-dev.h"
#include "../include/pman0-types.h"


int main(const int argc, const char **argv){
  dbg(COLOR_NAMES_QTY, %d);
  for (int i = 0; i < COLOR_NAMES_QTY; i++) {
    printf("%s - %s | \n",
           COLOR_NAMES[i].hex,
           COLOR_NAMES[i].name
           );
    _change_terminal_color_name(&COLOR_NAMES[i]);
  }
  OK("Done");
  return(0);
}
