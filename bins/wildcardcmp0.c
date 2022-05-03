// MESON_BIN_ENABLED=true
#include "../include/includes.h"


int main(const int argc, const char **argv){
  // positive
  assert_eq(1, wildcardcmp("foo*", "foo"), %d);
  assert(1 == wildcardcmp("foobar", "foobar"));
  assert(1 == wildcardcmp("*", "foobar"));
  assert(1 == wildcardcmp("foo*", "foobar"));
  assert(1 == wildcardcmp("fo*bar", "foobar"));
  assert(1 == wildcardcmp("*bar", "foobar"));
  assert(1 == wildcardcmp("f*b*r", "foobar"));
  assert(1 == wildcardcmp("f**b*r", "foobar"));
  assert(1 == wildcardcmp("f*", "foobar"));
  // negative
  assert(0 == wildcardcmp("FOOBAR", "foobar"));
  assert(0 == wildcardcmp("foo", "foobar"));
  assert(0 == wildcardcmp("bar*", "foobar"));
  assert(0 == wildcardcmp("f*R", "foobar"));
  // malformed
  assert(0 == wildcardcmp(NULL, "foobar"));
  assert(0 == wildcardcmp("foobar", NULL));
  // the whole point of this lib
  char *DEBUG = "clib:*";

  assert(1 == wildcardcmp(DEBUG, "clib:package"));
  assert(1 == wildcardcmp(DEBUG, "clib:install"));
  assert(1 == wildcardcmp(DEBUG, "clib:search"));
  assert(1 == wildcardcmp(DEBUG, "clib:help"));
  printf("OK!\n");
  return(0);
}
