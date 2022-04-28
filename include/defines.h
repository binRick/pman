#pragma once
#define _POSIX_C_SOURCE                200809L
#define VERSION                        "v1.0.0"
#define DBG_H_DEF_ONCE

#define DEFAULT_MODE                   "list_palettes"
#define DEFAULT_PALETTE                "vscode"
#define DEFAULT_VERBOSE                false

#define DEFAULT_PALETTE_DATA           "\
background=1e1e1e\
foreground=d4d4d4\
cursor=f44747\
color00=1e1e1e\
color01=f44747\
color02=d7ba7d\
color03=608b4e\
color04=569cd6\
color05=4ec9b0\
color06=c586c0\
color07=d4d4d4\
color08=808080\
color09=f44747\
color10=d7ba7d\
color11=608b4e\
color12=569cd6\
color13=4ec9b0\
color14=c586c0\
color15=d4d4d4\
"

#define SEQUENCE                       "printf \"\
\\033]4;0;#$(echo $color00)\\033\\ \
\\033]4;1;#$(echo $color01)\\033\\ \
\\033]4;2;#$(echo $color02)\\033\\ \
\\033]4;3;#$(echo $color03)\\033\\ \
\\033]4;4;#$(echo $color04)\\033\\ \
\\033]4;5;#$(echo $color05)\\033\\ \
\\033]4;6;#$(echo $color06)\\033\\ \
\\033]4;7;#$(echo $color07)\\033\\ \
\\033]4;8;#$(echo $color08)\\033\\ \
\\033]4;9;#$(echo $color09)\\033\\ \
\\033]4;10;#$(echo $color10)\\033\\ \
\\033]4;11;#$(echo $color11)\\033\\ \
\\033]4;12;#$(echo $color12)\\033\\ \
\\033]4;13;#$(echo $color13)\\033\\ \
\\033]4;14;#$(echo $color14)\\033\\ \
\\033]4;15;#$(echo $color15)\\033\\ \
\\033]10;#$(echo $foreground)\\033\\ \
\\033]11;#$(echo $background)\\033\\ \
\\033]12;#$(echo $cursor)\\033\\ \
\\033]708;#$(echo $border_background)\\033\\ \
\\033[21D\""

#define PALETTE_ICON0                  "❽"
#define PALETTE_ICON1                  "🏴"
#define PALETTE_ICON2                  "☼"
#define PALETTE_ICON3                  "❰⇄❱"
#define PALETTE_ICON                   PALETTE_ICON1

#define CURRENT_PALETTE_LABEL_STYLE    AC_RESETALL AC_UNDERLINE AC_REVERSED AC_BOLD AC_BRIGHT_YELLOW_BLACK

#define CURRENT_PALETTE                "\
\n\t"                                        CURRENT_PALETTE_LABEL_STYLE " Foreground " AC_RESETALL ":\t" AC_RESETALL "\
\033[48;5;0m   " PALETTE_ICON "  \033[0m\
\033[48;5;1m   " PALETTE_ICON "   \033[0m\
\033[48;5;2m   " PALETTE_ICON "   \033[0m\
\033[48;5;3m   " PALETTE_ICON "   \033[0m\
\033[48;5;4m   " PALETTE_ICON "   \033[0m\
\033[48;5;5m   " PALETTE_ICON "   \033[0m\
\033[48;5;6m   " PALETTE_ICON "   \033[0m\
\033[48;5;7m   " PALETTE_ICON "   \033[0m\
\n\t" CURRENT_PALETTE_LABEL_STYLE " Background " AC_RESETALL ":\t" AC_RESETALL "\
\033[48;5;8m   " PALETTE_ICON "  \033[0m\
\033[48;5;9m   " PALETTE_ICON "   \033[0m\
\033[48;5;10m   " PALETTE_ICON "   \033[0m\
\033[48;5;11m   " PALETTE_ICON "   \033[0m\
\033[48;5;12m   " PALETTE_ICON "   \033[0m\
\033[48;5;13m   " PALETTE_ICON "   \033[0m\
\033[48;5;14m   " PALETTE_ICON "   \033[0m\
\033[48;5;15m   " PALETTE_ICON "   \033[0m\
"

#define __MSG_PREFIX(...)      \
  char *prefix = malloc(1024); \
  sprintf(prefix, "<%d> %s", getpid(), __VA_ARGS__);

#define __MSG_SUFFIX \
  free(prefix);

#define DO_ERR(...)                                                    \
  do {                                                                 \
    __MSG_PREFIX(__VA_ARGS__)                                          \
    fprintf(stderr, AC_RESETALL AC_RED "%s" AC_RESETALL "\n", prefix); \
    __MSG_SUFFIX                                                       \
  } while (0)

#define DO_MSG(...)                                                       \
  do {                                                                    \
    __MSG_PREFIX(__VA_ARGS__)                                             \
    fprintf(stderr, AC_RESETALL AC_YELLOW "%s" AC_RESETALL "\n", prefix); \
    __MSG_SUFFIX                                                          \
  } while (0)

#define DO_DIE(...)      \
  do {                   \
    DO_ERR(__VA_ARGS__); \
    exit(EXIT_FAILURE);  \
  } while (0)

