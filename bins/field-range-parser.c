// MESON_BIN_ENABLED=false
#include "../include/includes.h"


int main(int argc, const char **argv) {
  int                i;
  struct field_range fs;

  field_range_init(&fs, NULL);
  field_range_parse(&fs, "3");
  dbg(fs.num_explicit_fields, %d);
  field_range_free(&fs, NULL);


  field_range_init(&fs, NULL);
  field_range_parse(&fs, "-3");

  /*
   * "==", 1, "should have 1 fields set");
   * ok(field_range_is_set(&fs, 3), "field 3 set");
   * ok(!fs.err, "shouldnt have err");
   * field_range_free(&fs, NULL);
   *
   * field_range_init(&fs, NULL);
   * field_range_parse(&fs, "-3");
   * cmp_ok(fs.num_explicit_fields, "==", 3, "should have 3 fields set");
   * ok(field_range_is_set(&fs, 1), "field 1 set");
   * ok(field_range_is_set(&fs, 2), "field 2 set");
   * ok(field_range_is_set(&fs, 3), "field 3 set");
   * ok(!fs.err, "shouldnt have err");
   * field_range_free(&fs, NULL);
   *
   * field_range_init(&fs, NULL);
   * field_range_parse(&fs, "2-4");
   * cmp_ok(fs.num_explicit_fields, "==", 3, "should have 3 fields set");
   * ok(field_range_is_set(&fs, 2), "field 2 set");
   * ok(field_range_is_set(&fs, 3), "field 3 set");
   * ok(field_range_is_set(&fs, 4), "field 4 set");
   * ok(!fs.err, "shouldnt have err");
   * field_range_free(&fs, NULL);
   *
   * field_range_init(&fs, NULL);
   * field_range_parse(&fs, "11-15-");
   * cmp_ok(fs.num_explicit_fields, "==", 5, "should have 111 fields set");
   * ok(field_range_is_set(&fs, 11), "field 333 set");
   * ok(!field_range_is_set(&fs, 10), "field 332 not set");
   * ok(field_range_is_set(&fs, 532), "field 532 set");
   * field_range_free(&fs, NULL);
   *
   * field_range_init(&fs, NULL);
   * field_range_parse(&fs, "-10000");
   * cmp_ok(fs.num_explicit_fields, "==", 10000, "should have 9 fields set");
   * ok(field_range_is_set(&fs, 1), "field 1 set");
   * ok(field_range_is_set(&fs, 10000), "field 10000 set");
   * ok(!field_range_is_set(&fs, 10001), "field 10001 not set");
   *
   * for (i = 6; i < 12; i++) {
   * ok(field_range_is_set(&fs, i), "field %d set", i);
   * }
   *
   * ok(!fs.err, "shouldnt have err");
   * field_range_free(&fs, NULL);
   */
  return(0);
}
