// MESON_BIN_ENABLED=false
#include "../src/includes.c"
#include "../include/template/hashmap.h"
//////////////////////////////////////////


int main() {
  struct env     *env = env_new(env_get_or("TEMPLATE_PATH", "./etc/tpl"));

  struct hashmap *vars = hashmap_new();

  hashmap_insert(vars, "name", "John Doexxxxxxxx");

  struct hashmap *c1 = hashmap_new();
  struct hashmap *u1 = hashmap_new();

  hashmap_insert(u1, "name", "Danny");
  hashmap_insert(c1, "user", u1);
  char *o1 = template(env, "t1.tpl", c1);

  printf("%s\n=======================\n", o1);

  char *o0 = template(env, "t0.tpl", vars);

  printf("%s\n=======================\n", o0);

  free(o0);
  free(o1);
  hashmap_free(vars);
  env_free(env);
}
