// MESON_BIN_ENABLED=true
#include "../include/includes.h"


int main(const int argc, const char **argv){
  env_load("", 0);

  printf("server: %s\n", getenv("SERVER"));
  printf("user: %s\n", getenv("USER"));
  printf("extra_var: %s\n", getenv("EXTRA_VAR"));
  printf("empty: %s\n", getenv("EMPTY"));
  printf("double: %s\n", getenv("DOUBLE_QUOTES"));
  printf("single: %s\n", getenv("SINGLE_QUOTES"));
  printf("inner space: %s\n", getenv("INNER_SPACE"));
  printf("outer space: %s\n", getenv("OUTER_SPACE"));
  printf("multi line: %s\n", getenv("MULTILINE"));

  printf("OK\n");
  return(0);
}
