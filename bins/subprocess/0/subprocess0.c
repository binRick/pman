// MESON_BIN_ENABLED=false
#include "../include/includes.h"

int                 exited, result;
struct subprocess_s subprocess;

const char          *command_line[]  = { "/bin/ls", "/etc/passwd", NULL };
const char          *command_line1[] = { "/bin/ls", "/etc/passwd_BAD_FILE", NULL };


int main(void){
  result = subprocess_create(command_line, 0, &subprocess);
  assert_eq(result, 0, %d);

  FILE *p_stdout = subprocess_stdout(&subprocess);
  char *out      = malloc(1024);

  fgets(out, 32, p_stdout);
  dbg(out, %s);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  dbg(exited, %d);
  assert_eq(exited, 0, %d);


  result = subprocess_create(command_line1, 0, &subprocess);
  assert_eq(result, 0, %d);
  FILE *p_stderr = subprocess_stderr(&subprocess);
  char *err      = malloc(1024);

  fgets(err, 1024, p_stderr);
  dbg(err, %s);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  dbg(exited, %d);
  assert_eq(exited, 1, %d);


  return(0);
}
