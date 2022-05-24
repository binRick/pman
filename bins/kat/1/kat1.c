// MESON_BIN_ENABLED=true
#include "../src/includes.c"


static inline void quit(int errcode, const char *msg){
  puts(msg);
  exit(errcode);
}


int main(){
  if (highlight_init(NULL) < 0) {
    quit(-1, "Unable to initialize the highlight!\n");
  }
  char *line;

  line = highlight_line("#include <stdio.h>", NULL, 0);
  puts(line);
  line = highlight_line("int main(int argc, char **argv){ /* Comment. */", line, 0);
  puts(line);
  line = highlight_line("    printf(\"Hello World \%s\\n\", argv[1]);", line, 0);
  puts(line);
  line = highlight_line("}", line, 0);
  puts(line);

  highlight_free(line);
  highlight_finish();
  return(0);
}
