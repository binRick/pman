#include "../include/includes.h"
// MESON_BIN_ENABLED=true


int main(const int argc, const char **argv){
  printf("Uptime: %lu\n", (unsigned long)getUptime());
  printf("OK!\n");
  return(0);
}
