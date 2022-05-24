// MESON_BIN_ENABLED=true
#include "../src/module0.c"

module(module0) * module0;


int init(){
  module0 = require(module0);
  return(0);
}


int work(){
  module0->mode = LOGGER_DEBUG;
  module0->info("hello");
  module0->error("oops");
  module0->debug("help");
  return(0);
}


int clean(){
  clib_module_free(module0);
  return(0);
}


int main(void) {
  assert(init() == 0);
  assert(work() == 0);
  assert(clean() == 0);
  return(0);
}

