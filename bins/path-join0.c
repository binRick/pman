// MESON_BIN_ENABLED=false
#include "../src/includes.c"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
  char *path = NULL;

  path = path_join("/foo/bar", "baz");
  assert(0 == strcmp("/foo/bar/baz", path));
  free(path);

  path = path_join("/foo/bar/", "baz");
  assert(0 == strcmp("/foo/bar/baz", path));
  free(path);

  path = path_join("/foo/bar", "/baz");
  assert(0 == strcmp("/foo/bar/baz", path));
  free(path);

  path = path_join("/foo/bar", "baz.c");
  assert(0 == strcmp("/foo/bar/baz.c", path));
  free(path);

  return(0);
}
