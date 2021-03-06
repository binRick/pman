#include "../include/includes.h"


// MESON_BIN_ENABLED=false


void my_program(void *context){
  dbg("program", %s);
  if (context != NULL) {
    // do something with the context
  }

  sleep(1);
  exit(0);
}


int callback(void *context, const unsigned char started, int stat_loc){
  dbg("callback", %s);
  if (context != NULL) {
    // do something with the context
  }

  if (stat_loc == 0 || !started) {
    return(-1); // no more retries
  }

  return(500); // wait 500 millies before next invocation, 0 for no wait.
}


int main(const int argc, const char **argv){
  if ((argc == 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Forever OK");
    exit(0);
  }
  void *context = NULL;

  // call 'my_program' and when it ends/crashes invoke it again, up
  // to 10 times and wait 250 millies between invocations.
  // counter will hold the amount of times 'my_program' was invoked.
  unsigned int counter = forever_with_options(
    my_program, // function to invoke
    context,    // context that is passed to the function on every invocation
    10,         // max amount of retries. 0 for unlimited retries.
    250         // amount of millies to wait between invocations. 0 for no wait.
    );

  printf("Invoked %u time/s.\n", counter);

  // call 'my_program' and when it ends/crashes call the provided callback
  counter = forever_with_callback(my_program, context, callback);
  printf("Invoked %u time/s.\n", counter);

  // run with unlimited retries and no delay between invocations
  forever(my_program, context);
}
