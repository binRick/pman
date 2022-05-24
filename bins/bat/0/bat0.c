#include "../include/includes.h"
// MESON_BIN_ENABLED=false

#define CMD    "env sh -c 'bat --force-colorization --style=plain --theme=ansi /tmp/test.c > /tmp/test-bat.c'"


int main(const int argc, const char **argv){
  struct ScriptExecOptions options = scriptexec_create_options();

  options.runner            = "sh";
  options.working_directory = "/tmp";
  options.exit_on_error     = true;       // default true, will break script execution on any error
  options.print_commands    = true;
  struct ScriptExecResult result = scriptexec_run_with_options(CMD, options);

  printf("Code: %d\nOutput:\n%s\nError:\n%s\n", result.code, result.out, result.err);
  free(result.out);
  free(result.err);
  printf("OK\n");


  return(0);
}
