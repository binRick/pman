// MESON_BIN_ENABLED=true
////////////////////////////////////////////////////
#include "../src/includes.c"
////////////////////////////////////////////////////
#include "/Users/rick/repos/pman/include/embedded-colornames-dev.h"
#include "../include/pman0-types.h"
////////////////////////////////////////////////////
#define MAX_TEST_COLORS_QTY      10
#define CHANGE_TERMINAL_COLOR    false
#define BAR_WIDTH                10 * 3
#define HEX_LENGTH               7
#define BUFFER_LEN               1024
////////////////////////////////////////////////////
#define ANSI_CMD                 "\
env RED=155 GREEN=200 BLUE=50 ~/repos/ansi/draw_ansi_bar.sh\
"
#define HTML_CMD                 "\
env OPEN=0 RED=155 GREEN=200 BLUE=50 FONT_SIZE=1.5 ~/repos/ansi/create_html_bar.sh\
"
#define PNG_CMD                  "\
env OPEN=0 RED=255 GREEN=20 BLUE=255 ~/repos/ansi/create_png_bar.sh\
"


////////////////////////////////////////////////////
char *ansi_bar(color_name_t *cn){
  char *bar = malloc(BUFFER_LEN), *bar_content = malloc(BUFFER_LEN), *bg = malloc(BUFFER_LEN), *bar_template = malloc(BUFFER_LEN);

  sprintf(bar_template,
          "%s%s%s%%%s%ds",
          "%s",
          "%s",
          "%s",
          "",
          BAR_WIDTH
          );

  sprintf(bg, "\x1b[48;2;%d;%d;%dm",
          cn->red,
          cn->green,
          cn->blue
          );

  sprintf(bar_content, bar_template, bg, AC_BLACK, " ");
  sprintf(bar, AC_RESETALL "%s" AC_RESETALL,
          bar_content
          );
  bar[strlen(bar)] = '\0';

  free(bg); free(bar_content); free(bar_template);
  assert_ge(strlen(bar), (unsigned long)BAR_WIDTH, %lu);
  return(bar);
}


int test_mode(){
  OK("Test OK");
  return(0);
}


int main(const int argc, const char **argv){
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    return(test_mode());
  }

  for (int i = 0; (i <= (COLOR_NAMES_QTY)) && COLOR_NAMES[i].hex[0] == '#'; i++) {
    if ((COLOR_NAMES[i].path_size < 1) || (COLOR_NAMES[i].hex[0] == '\0') || (strlen(COLOR_NAMES[i].hex) != HEX_LENGTH)) {
      continue;
    }

    fprintf(stdout,
            AC_RESETALL AC_REVERSED AC_BOLD AC_BG8(7) AC_FG8(0) "#" AC_RESETALL
            AC_RESETALL AC_REVERSED AC_BRIGHT_GREEN_BLACK AC_ITALIC "%lu" AC_RESETALL
            AC_RESETALL AC_REVERSED AC_BOLD AC_BG8(7) AC_FG8(0) ">" AC_RESETALL,
            (COLOR_NAMES[i].id + 1)
            );


    if (CHANGE_TERMINAL_COLOR) {
      _change_terminal_color_name(&COLOR_NAMES[i]);
    }

    char *BAR = ansi_bar(&(COLOR_NAMES[i]));

    fprintf(stdout,
            AC_RESETALL
            "|"
            "%s"
            "|"
            "%20s|%10s|%s Image|%s"
            "|"
            AC_RESETALL,
            BAR,
            COLOR_NAMES[i].name,
            COLOR_NAMES[i].hex,
            bytes_to_string(COLOR_NAMES[i].path_size),
            COLOR_NAMES[i].encoded_path_contents
            );

    if (CHANGE_TERMINAL_COLOR) {
      _reset_terminal_to_default_color();
    }

    fprintf(stdout,
            AC_RESETALL "\n"
            );
    fflush(stdout);
  }
  dbg(COLOR_NAMES_QTY, %lu);
#ifdef TEST_MODE_ENABLED
  int ret = test_color_sizes(argc, argv);
  assert_eq(ret, 0, %d);
#endif
  OK("Done");
  return(0);
} /* main */
