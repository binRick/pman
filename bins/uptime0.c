// MESON_BIN_ENABLED=true
/////////////////////////////////
#include "../src/includes.c"
/////////////////////////////////


int main(const int argc, const char **argv){
  printf("Uptime: %lu\n", (unsigned long)getUptime());
  printf("OK!\n");
  return(0);
}
