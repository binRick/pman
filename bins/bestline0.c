#include "../../include/includes.h"
// MESON_BIN_ENABLED=false


void completion(const char *buf, bestlineCompletions *lc) {
  if (buf[0] == 'h') {
    bestlineAddCompletion(lc, "hello");
    bestlineAddCompletion(lc, "hello there");
  }
}


char *hints(const char *buf, const char **ansi1, const char **ansi2) {
  if (!strcmp(buf, "hello")) {
    *ansi1 = "\033[35m";     /* magenta foreground */
    *ansi2 = "\033[39m";     /* reset foreground */
    return(" World");
  }
  return(NULL);
}


int main(int argc, char **argv) {
  char *line;

  /* Set the completion callback. This will be called every time the
   * user uses the <tab> key. */
  bestlineSetCompletionCallback(completion);
  bestlineSetHintsCallback(hints);

  /* Load history from file. The history file is just a plain text file
   * where entries are separated by newlines. */
  bestlineHistoryLoad("history.txt");   /* Load the history at startup */

  /* Now this is the main loop of the typical bestline-based application.
   * The call to bestline() will block as long as the user types something
   * and presses enter.
   *
   * The typed string is returned as a malloc() allocated string by
   * bestline, so the user needs to free() it. */
  char *__is_meson_test_mode__ = env_get_or("__MESON_TEST_MODE__", "-1");

  if (strcmp(__is_meson_test_mode__, "1") == 0) {
    fprintf(stdout, "is_meson_test_mode enabled!\n");
    exit(0);
  }

  while ((line = bestline("hello> ")) != NULL) {
    /* Do something with the string. */
    if (line[0] != '\0' && line[0] != '/') {
      fputs("echo: '", stdout);
      fputs(line, stdout);
      fputs("'\n", stdout);
      bestlineHistoryAdd(line);           /* Add to the history. */
      bestlineHistorySave("history.txt"); /* Save the history on disk. */
    } else if (!strncmp(line, "/mask", 5)) {
      bestlineMaskModeEnable();
    } else if (!strncmp(line, "/unmask", 7)) {
      bestlineMaskModeDisable();
    } else if (line[0] == '/') {
      fputs("Unreconized command: ", stdout);
      fputs(line, stdout);
      fputs("\n", stdout);
    }
    free(line);
  }
  return(0);
}
