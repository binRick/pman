#include "../src/includes.c"

int                 exited, result;
struct subprocess_s subprocess;


int main(void){
  const char *command_line[] = { "/bin/ls", "/etc/passwd", NULL };

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


  const char *command_line1[] = { "/bin/ls", "/etc/passwdXXXXXXX", NULL };

  result = subprocess_create(command_line1, 0, &subprocess);
  assert_eq(result, 0, %d);
  FILE *p_stderr = subprocess_stderr(&subprocess);
  char *err      = malloc(1024);

  fgets(err, 32, p_stderr);
  dbg(err, %s);

  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  dbg(exited, %d);
  assert_eq(exited, 1, %d);

  return(0);
}
