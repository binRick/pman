#include "../include/includes.h"
// MESON_BIN_ENABLED=true
#define MD5_LEN    16
char *str = "hello world";


int main(const int argc, const char **argv){
  md5_ctx       ctx;
  unsigned char hash[MD5_LEN];

  rhash_md5_init(&ctx);
  rhash_md5_update(&ctx, (const unsigned char *)str, strlen(str));
  rhash_md5_final(&ctx, hash);
  char *encoded_md5 = (char *)b64_encode((const unsigned char *)hash, MD5_LEN);

  OK(encoded_md5);
  return(0);
}
