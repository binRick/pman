// MESON_BIN_ENABLED=false
#include "../src/includes.c"


int main(void){
  assert_eq(1, 1, %d);
  assert_null(NULL);
  assert_nonnull(main);
  assert_true(1, %d);
  assert_true(-1, %d);
  assert_false(0, %d);
  assert_eqf(!1, 0, % d, "foobar");
  return(0);
}
