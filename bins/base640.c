#include "../include/includes.h"
// MESON_BIN_ENABLED=false
char *str;
char *enc;
char *dec;
char *str = "brian the monkey and bradley the kinkajou are friends";


int main(const int argc, const char **argv){
  enc = (char *)b64_encode((const unsigned char *)str, strlen(str));
  OK(enc);

  dec = (char *)b64_decode(enc, strlen(enc));
  OK(dec);
  return(0);
}
