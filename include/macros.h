
#define color_reset() \
  printf("\x1b[0m")

#define color_set(r, g, b) \
  printf("\x1b[38;2;%d;%d;%dm", r, g, b)

#define colorB_set(br, bg, bb) \
  printf("\x1b[48;2;%d;%d;%dm", br, bg, bb)

#define colorAll_set(r, g, b, br, bg, bb) \
  printf("\x1b[38;2;%d;%d;%d;48;2;%d;%d;%dm", r, g, b, br, bg, bb)

#define color256_set(code) \
  printf("\x1b[38;5;%dm", code)

#define color256B_set(code) \
  printf("\x1b[48;5;%dm", code)

#define LIST_QTY(LIST)    {                  \
    ((sizeof(LIST) / sizeof((LIST)[0])) - 1) \
}

#define PALETTES_QTY    ((sizeof(__embedded_table__) / sizeof((__embedded_table__)[0])) - 1)
