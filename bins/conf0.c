#include "../include/includes.h"
// MESON_BIN_ENABLED=true

static struct option getopt_long_options[] = {
  { "name", 1, NULL, 'n' }, { "bell", 0, NULL, 'b' }, { NULL, 0, NULL, 0 }
};
static const char    *getopt_options = "n:b";


void parse_options(int argc, char *argv[]){
  int flag, index = 0;

  while ((flag = getopt_long(argc, argv, getopt_options,
                             getopt_long_options, &index)) != -1) {
    switch (flag) {
    case 'n': printf("Hello %s!\n", optarg); break;
    case 'b': putchar(7); break;
    }
  }
}


int main(int argc, char *argv[]){
  static const SimpleConfEntry sc_defs[] = {
    { "Name (<any*>)", "--name=$0" },
    { "Bell? <bool>",  "--bell"    }
  };

  sc_build_command_line_from_file("../etc/conf0.conf", NULL, sc_defs, 2,
                                  argv[0], &argc, &argv);
  parse_options(argc, argv);
  return(0);
}
