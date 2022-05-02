// MESON_BIN_ENABLED=true
#include "../include/includes.h"
//////////////////////////////////////
#define DEFAULT_BIG_NUMBER    1000000000

int big_number = DEFAULT_BIG_NUMBER;


int main(const int argc, const char **argv){
  int x       = 0;
  int working = 1;

  if ((argc == 2) && (strcmp(argv[1], "--test") == 0)) {
    big_number = 1000;
  }
  spinner *s = spin_new(utf8_pat1, AC_RESETALL AC_RED AC_UNDERLINE "Working" AC_RESETALL, UTF8_CHAR_WIDTH);

  while (working) {
    if (x == (big_number * .25)) {
      spin_upd_msg(s, AC_RESETALL AC_YELLOW "Part way through" AC_RESETALL);
      spin_drw(s);
    }
    if (x == (big_number * .75)) {
      spin_upd_msg(s, AC_RESETALL AC_GREEN AC_BOLD "Getting close now" AC_RESETALL);
      spin_drw(s);
    }
    if (x % 9999999 == 0) {  // this is just to throttle it a bit
      spin_drw(s);
    }
    if (x++ > big_number) {
      working = 0;
    }
  }
  spin_del(s);

  OK(AC_RESETALL AC_BLUE "Done" AC_RESETALL);
  return(0);
}
