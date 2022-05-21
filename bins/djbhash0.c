// MESON_BIN_ENABLED=true
#include "../src/includes.c"

typedef struct test_struct {
  int a;
  int b;
} test_struct;

int                 temp = 10, temp_arr[] = { 8, 6, 7, 5, 3, 0, 9 };
double              temp2 = 3.14159;
char                temp3 = 'a', *mystr0 = "abc123", *missing = "missing key", _msg[1024], *msg = (char *)(&_msg);
test_struct         test = {
  .a = 10,
  .b = 20,
};
test_struct         *test0;
struct djbhash_node *item;


int main(int argc, char *argv[]){
  struct djbhash hash, temp_hash = { NULL };

  djbhash_init(&hash);
  djbhash_init(&temp_hash);

  test0    = calloc(1, sizeof(test_struct));
  test0->a = 101;
  test0->b = 666;

  djbhash_set(&hash, "int", &temp, DJBHASH_INT);
  djbhash_set(&hash, "double", &temp2, DJBHASH_DOUBLE);
  djbhash_set(&hash, "char", &temp3, DJBHASH_CHAR);
  djbhash_set(&hash, "string", "bar", DJBHASH_STRING);
  djbhash_set(&hash, "mystr0", mystr0, DJBHASH_STRING);
  djbhash_set(&hash, "array", temp_arr, DJBHASH_ARRAY, 7);
  djbhash_set(&hash, "hash", &temp_hash, DJBHASH_HASH);
  djbhash_set(&hash, "other", &test, DJBHASH_OTHER);
  djbhash_set(&hash, "test0", test0, DJBHASH_OTHER);

  djbhash_set(&temp_hash, "foo", "bar", DJBHASH_STRING);
  djbhash_set(&temp_hash, "baz", temp_arr, DJBHASH_ARRAY, 7);

  OK("Finding single items...");

  item = djbhash_find(&hash, "mystr01");
  assert_null(item);
  OK("did not find non existent item");

  item = djbhash_find(&hash, "mystr0");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "int");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "double");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "char");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "string");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "array");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "hash");
  assert_nonnull(item);
  djbhash_print(item);

  item = djbhash_find(&hash, "other");
  assert_nonnull(item);
  printf(" test.a: %d\n", (*((test_struct *)(item->value))).a);
  printf(" test.b: %d\n", (*((test_struct *)(item->value))).b);

  item = djbhash_find(&hash, "test0");
  assert_nonnull(item);
  printf(" test0->a: %d\n", ((test_struct *)(item->value))->a);
  printf(" test0->b: %d\n", ((test_struct *)(item->value))->b);

  if (djbhash_find(&hash, "int") != NULL) {
    OK("Removing key \"int\"...");
    djbhash_remove(&hash, "int");
    if (djbhash_find(&hash, "int") == NULL) {
      OK("int removed");
    }
  }

  // Print all items.
  OK("Dumping all items...");
  djbhash_dump(&hash);

  // Iterate through items.
  OK("Iterating...");
  unsigned int qty = 0;

  for (item = djbhash_iterate(&hash); item != NULL; item = djbhash_iterate(&hash), qty++) {
    printf("Item #%d |\n", qty);
    printf("       count:   %20d |\n", item->count);
    printf("       key:     %20s |\n", item->key);
    printf("       type:    %20d |\n", item->data_type);
    printf("       active:  %20d |\n", hash.active_count);
    djbhash_print(item);
  }
  djbhash_reset_iterator(&hash);


  sprintf(msg, "Searching for a missing key \"%s\"...", missing);
  OK(msg);
  if ((item = djbhash_find(&hash, missing)) == NULL) {
    sprintf(msg, "Searching for a missing key \"%s\"...", missing);
    OK(msg);
    sprintf(msg, "%s: No such item!", missing);
    OK(msg);
  }

  sprintf(msg, "temp_hash to json: %s", (char *)(djbhash_to_json(&temp_hash)));
  OK(msg);

  sprintf(msg, "hash to json: %s", (char *)(djbhash_to_json(&hash)));
  OK(msg);

  // Remove all items and free memory.
  djbhash_destroy(&temp_hash);
  djbhash_destroy(&hash);

  free(test0);

  OK("Hash tests OK.");
  return(0);
} /* main */
