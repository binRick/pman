// MESON_BIN_ENABLED=true
#include "../src/includes.c"


int main_free() {
  char   text[] = "Le grand orchestre";

  Buffet own = buffet_memcopy(text, sizeof(text));
  Buffet ref = buffet_view(&own, 9, 9);   // 'orchestre'

  // Too soon but marked for release
  buffet_free(&own);

  // Was last ref, data gets actually released
  buffet_free(&ref);

  OK("Free");
  return(0);
}


int main_view() {
  char   text[] = "Bonjour monsieur Buddy. Already speaks french!";
  // view own
  Buffet own     = buffet_memcopy(text, sizeof(text));
  Buffet Bonjour = buffet_view(&own, 0, 7);

  buffet_debug(&Bonjour);   // REF cstr:'Bonjour'

  // view ref
  Buffet Bon = buffet_view(&Bonjour, 0, 3);

  buffet_debug(&Bon);   // REF cstr:'Bon'

  // detach views
  buffet_append(&Bonjour, "!", 1);
  buffet_free(&Bon);
  buffet_free(&own);   // OK

  // view vue
  Buffet vue = buffet_memview("Good day", 4);   // "Good"
  Buffet Goo = buffet_view(&vue, 0, 3);

  buffet_debug(&Goo);   // VUE cstr:'Goo'

  // view sso
  Buffet sso  = buffet_memcopy("Hello", 5);
  Buffet Hell = buffet_view(&sso, 0, 4);

  buffet_debug(&Hell);   // VUE cstr:'Hell'
  buffet_free(&Hell);    // OK
  buffet_free(&sso);     // OK

  OK("View");
  return(0);
}


int main(){
  char   text[] = "The train goes";

  Buffet vue = buffet_memview(text + 4, 5);

  buffet_print(&vue);       // "train"

  text[4] = 'b';
  buffet_print(&vue);       // "brain"

  Buffet ref = buffet_view(&vue, 1, 4);

  buffet_print(&ref);       // "rain"

  char tail[] = "ing";

  buffet_append(&ref, tail, sizeof(tail));
  buffet_print(&ref);       // "raining"

  int res = main_view();

  assert_eq(res, 0, %d);

  res = main_free();
  assert_eq(res, 0, %d);

  OK("Main");
  return(0);
}
