#ifndef __KFC_DEFINES_H__
#define __KFC_DEFINES_H__

#define _POSIX_C_SOURCE        200809L
#define VERSION                "v1.0.0"
#define DBG_H_DEF_ONCE

#define DEFAULT_REQUESTS       5000
#define DEFAULT_CONCURRENCY    10
#define DEFAULT_URL            ":3000"
#define DEFAULT_MODE           "list_palettes"
#define DEFAULT_PALETTE        "vscode"
#define DEFAULT_VERBOSE        false

#define SEQUENCE               "printf \"\
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
\\033[21D\""

#define CURRENT_PALETTE        "\
\n\tForeground:\t\
\033[48;5;0m  ❽  \033[0m\
\033[48;5;1m  ❽  \033[0m\
\033[48;5;2m  ❽  \033[0m\
\033[48;5;3m  ❽  \033[0m\
\033[48;5;4m  ❽  \033[0m\
\033[48;5;5m  ❽  \033[0m\
\033[48;5;6m  ❽  \033[0m\
\033[48;5;7m  ❽  \033[0m\
\n\tBackground:\t\
\033[48;5;8m  ❽  \033[0m\
\033[48;5;9m  ❽  \033[0m\
\033[48;5;10m  ❽  \033[0m\
\033[48;5;11m  ❽  \033[0m\
\033[48;5;12m  ❽  \033[0m\
\033[48;5;13m  ❽  \033[0m\
\033[48;5;14m  ❽  \033[0m\
\033[48;5;15m  ❽  \033[0m\
"

#define MSG_PREFIX(...)        \
  char *prefix = malloc(1024); \
  sprintf(prefix, "<%d> %s", getpid(), __VA_ARGS__);

#define MSG_SUFFIX \
  free(prefix);

#define DO_ERR(...)                                                    \
  do {                                                                 \
    MSG_PREFIX(__VA_ARGS__)                                            \
    fprintf(stderr, AC_RESETALL AC_RED "%s" AC_RESETALL "\n", prefix); \
    MSG_SUFFIX                                                         \
  } while (0)

#define DO_MSG(...)                                                       \
  do {                                                                    \
    MSG_PREFIX(__VA_ARGS__)                                               \
    fprintf(stderr, AC_RESETALL AC_YELLOW "%s" AC_RESETALL "\n", prefix); \
    MSG_SUFFIX                                                            \
  } while (0)

#define DO_DIE(...)      \
  do {                   \
    DO_ERR(__VA_ARGS__); \
    exit(EXIT_FAILURE);  \
  } while (0)

#endif
