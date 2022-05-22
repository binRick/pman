// MESON_BIN_ENABLED=true
#include "../src/includes.c"
#define BAD_DIR    "/...........BAR_DIR---------"


int main(const int argc, const char **argv){
  char *dir = gettempdir();
  int  exists;

  exists = fsio_dir_exists(BAD_DIR);
  assert_eq(exists, 0, %d);
  OK(BAD_DIR);

  exists = fsio_dir_exists("/");
  assert_eq(exists, 1, %d);
  OK("/");

  exists = fsio_dir_exists(dir);
  assert_eq(exists, 1, %d);
  OK(dir);

  OK("Temp dir OK");
  return(0);
}
