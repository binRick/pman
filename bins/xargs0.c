// MESON_BIN_ENABLED=false
#include "../include/includes.h"
#define BUFFER_LEN    1024

int                 exited, result;
struct subprocess_s subprocess;

const char          *cmd1[]          = { "find", "../bins", "-type", "f", "-name", "*.c", NULL };
const char          *cmd_xargs[]     = { "xargs", "-I", "%", "basename", "%", NULL };
unsigned int        subprocesses_qty = 0;


int find_xargs(void){
  tq_start(NULL);
  struct subprocess_s xsubprocess;
  int                 result = subprocess_create(cmd1, subprocess_option_search_user_path, &subprocess);

  assert_eq(result, 0, %d);
  FILE                *p_stdout = subprocess_stdout(&subprocess);
  FILE                *p_stderr = subprocess_stderr(&subprocess);
  struct StringBuffer *sb       = stringbuffer_new_with_options(BUFFER_LEN, true);
  struct StringBuffer *sb_err   = stringbuffer_new_with_options(BUFFER_LEN, true);
  char                *err      = malloc(BUFFER_LEN);
  char                *out      = malloc(BUFFER_LEN);

  while (fgets(out, BUFFER_LEN, p_stdout) != NULL) {
    stringbuffer_append_string(sb, out);
  }
  while (fgets(err, BUFFER_LEN, p_stderr) != NULL) {
    stringbuffer_append_string(sb_err, err);
  }
  result = subprocess_join(&subprocess, &exited);
  assert_eq(result, 0, %d);
  assert_eq(exited, 0, %d);
  subprocesses_qty++;

  char                   *r_err = stringfn_trim(stringbuffer_to_string(sb_err));
  struct StringFNStrings Stderr = stringfn_split_lines_and_trim(r_err);
  char                   *r     = stringfn_trim(stringbuffer_to_string(sb));
  struct StringFNStrings Stdout = stringfn_split_lines_and_trim(r);

  char                   *pdur = tq_stop("Find");

  for (int i = 0; i <= Stdout.count && Stdout.strings[i] && strlen(Stdout.strings[i]) > 0; i++) {
    printf(AC_RESETALL AC_GREEN ">%s\n" AC_RESETALL, Stdout.strings[i]);
  }
  for (int i = 0; i <= Stderr.count && Stderr.strings[i] && strlen(Stderr.strings[i]) > 0; i++) {
    printf(AC_RESETALL AC_RED ">%s\n" AC_RESETALL, Stderr.strings[i]);
  }

  result = subprocess_destroy(&subprocess);
  assert_eq(result, 0, %d);

  printf(">Exited %d :: %s\n", exited, pdur);
  printf(">Read %d lines from stdout :: %lu bytes\n", Stdout.count, strlen(r));
  printf(">Read %d lines from stderr :: %lu bytes\n", strlen(r_err) > 0 ? Stderr.count : 0, strlen(r_err));
  stringfn_release_strings_struct(Stdout);
  stringfn_release_strings_struct(Stderr);
  free(r_err); free(out); free(err); free(pdur);

  tq_start(NULL);
  int  xresult    = subprocess_create(cmd_xargs, subprocess_option_search_user_path, &xsubprocess);
  FILE *xp_stdout = subprocess_stdout(&xsubprocess);

  assert_nonnull(xp_stdout);
  FILE *xp_stdin = subprocess_stdin(&xsubprocess);

  assert_nonnull(xp_stdin);
  int wrote_bytes = 0;

  while (wrote_bytes < strlen(r)) {
    wrote_bytes += fputs(r, xp_stdin);
  }
  dbg(wrote_bytes, %d);

  result = subprocess_join(&xsubprocess, &exited);
  assert_eq(result, 0, %d);
  assert_eq(exited, 0, %d);
  subprocesses_qty++;

  char                *xdur = tq_stop("Find");
  char                *xout = malloc(BUFFER_LEN);

  struct StringBuffer *xb = stringbuffer_new_with_options(BUFFER_LEN, true);

  while (fgets(xout, BUFFER_LEN, xp_stdout) != NULL) {
    stringbuffer_append_string(xb, xout);
  }
  struct StringFNStrings xStdout = stringfn_split_lines_and_trim(stringbuffer_to_string(xb));
  char                   *xr     = stringfn_trim(stringbuffer_to_string(xb));

  for (int i = 0; i <= xStdout.count && xStdout.strings[i] && strlen(xStdout.strings[i]) > 0; i++) {
    printf(AC_RESETALL AC_BLUE ">%s\n" AC_RESETALL, xStdout.strings[i]);
  }
  printf(">Exited %d :: %s\n", exited, xdur);
  printf(">Read %d lines from stdout :: %lu bytes\n", Stdout.count, strlen(xr));
  printf("># Subprocesses:  %d\n", subprocesses_qty);

  stringfn_release_strings_struct(xStdout); free(r); free(xr); free(xdur); free(xout);
  return(exited);
} /* find_xargs */


int main(void){
  return(find_xargs());
}
