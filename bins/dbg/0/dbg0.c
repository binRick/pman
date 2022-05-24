// MESON_BIN_ENABLED=false
#include "../include/includes.h"


//////////////////////////////////////


int main(const int argc, const char **argv){
  char *s = "test123";

  dbg(s, %s);
  OK(AC_RESETALL AC_BLUE "Done" AC_RESETALL);
  return(0);
}
