#pragma once
#include "../include/pman.h"
#include "../src/args.c"
#include "../src/globals.c"
#include "../src/init.c"
#include "../src/modes.c"


int main(const int argc, const char **argv) {
  assert(pman_args(argc, argv) == 0);
  return(run_mode(args->mode));

  /*
   * tmp = getenv("XDG_CONFIG_HOME");
   *
   * if (tmp != NULL) {
   * len  = strlen(tmp) + sizeof("/pman/current");
   * conf = malloc(sizeof(char) * len);
   * snprintf(conf, len, "%s", tmp);
   * }else {
   * fprintf(stderr, "XDG_CONFIG_HOME is not defined. Defaulting to HOME/.config\n");
   * tmp  = getenv("HOME");
   * len  = strlen(tmp) + sizeof("/.config/pman/current");
   * conf = malloc(sizeof(char) * len);
   * snprintf(conf, len, "%s/.config", tmp);
   * }
   *
   * strcat(conf, "/pman");
   *
   * if (mkdir(conf, 0777) == 0) {
   * puts("Created 'pman' directory in XDG_CONFIG_HOME");
   * }
   *
   * strcat(conf, "/current");
   *
   * while ((cval = getopt(argc, argv, "rlLpvs:")) != -1) {
   * switch (cval) {
   * case 'v': puts("pman 0.1.2");  break;
   * case 'L': mode = "light";     break;
   * case 'l': lflag++;            break;
   * case 'r': rflag++;            break;
   * case 'p': pflag++;            break;
   * case 's':
   *  if (rflag) {
   *    fprintf(stderr, "Cannot specify -r with -s\n");
   *    return(1);
   *  }
   *  sval = optarg;
   *  break;
   * case '?': return(1);
   * }
   * }*/
/*
 * len = strlen(seq)
 + sizeof("/")
 + strlen(mode)
 + (sval ? strlen(sval) + 1 : 0);
 +
 + sel = malloc(sizeof(char) * len);
 +
 + if (lflag) {
 +  snprintf(sel, len, "%s/%s", seq, mode);
 +  list_palette(sel);
 + }
 +
 + if (rflag) {
 +  snprintf(sel, len, "%s/%s", seq, mode);
 +  random_palette(sel);
 +  len = strlen(sel)
 + sizeof("/")
 + strlen(sval);
 +  sel = (char *)realloc(sel, sizeof(char) * len);
 + }
 +
 + if (sval) {
 +  snprintf(sel, len, "%s/%s/%s", seq, mode, sval);
 +  select_palette(sel);
 + }
 +
 + if (pflag) {
 +  print_palette();
 + }
 +
 + free(sel);
 */

  return(0);
} /* main */

