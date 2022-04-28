#ifndef __MODES_C__
#define __MODES_C__
/**********************************************/
#include "../include/pman.h"
#include "../src/args.c"
#include "../src/palettes.c"


/**********************************************/
int debug_error(){
  DO_ERR("some error"); return(0);
}


int debug_msg(){
  DO_MSG("some message"); return(0);
}


int debug_die(){
  DO_DIE("critical error"); return(0);
}
/**********************************************/
struct mode_t modes[] = {
  { .name = "debug_args",     .fxn = debug_args                   },
  { .name = "test_hex1",      .fxn = test_hex1                    },
  { .name = "list_palettes",  .fxn = list_palettes                },
  { .name = "list_templates", .fxn = list_templates               },
  { .name = "list_palettes",  .fxn = list_palettes                },
  { .name = "list_modes",     .fxn = list_modes                   },
  { .name = "palettes",       .fxn = list_palette_names           },
  { .name = "view_palette",   .fxn = view_palette                 },
  { .name = "cur",            .fxn = print_current_palette_colors },
  { .name = "err",            .fxn = debug_error                  },
  { .name = "msg",            .fxn = debug_msg                    },
  { .name = "die",            .fxn = debug_die                    },
  { NULL },
};
/**********************************************/
const size_t  MODES_QTY = LIST_QTY(modes);


/**********************************************/
int get_mode_index(const char *name){
  for (int i = 0; i < MODES_QTY; i++) {
    if (strcmp(modes[i].name, name) == 0) {
      return(i);
    }
  }
  return(-1);
}


/**********************************************/
int run_mode(const char *name){
  int mode_index = get_mode_index(name);

  if (mode_index < 0) {
    fprintf(stderr, AC_RESETALL AC_BRIGHT_RED_BLACK AC_REVERSED AC_BOLD "Invalid mode '%s'!" AC_RESETALL "\n", name);
    return(-1);
  }
  return(modes[mode_index].fxn());
}


/**********************************************/
int view_palette(){
  printf(
    AC_RESETALL AC_BRIGHT_YELLOW AC_REVERSED "%s"
    AC_RESETALL ":"
    AC_RESETALL "(%d lines)"
    AC_RESETALL " :: cursor=%s | color07=%s"
    AC_RESETALL "\n"
    AC_RESETALL AC_BOLD "%s"
    AC_RESETALL "\n",
    __basename((const char *)args->palette),
    get_palette_data_lines_qty((const char *)args->palette),
    get_palette_property_value((const char *)args->palette, "cursor"),
    get_palette_property_value((const char *)args->palette, "color07"),
    get_palette_data((const char *)args->palette)
    );
  PALETTE_t *ptr = __embedded_table__;

  for (int i = 0; (i < TEMPLATES_QTY && __embedded_table__[i].data); i++, ptr++ ) {
    if (strcmp(__basename(__embedded_table__[i].filename), args->palette) == 0) {
    }
  }
  return(0);
}


/**********************************************/
int list_modes(){
  for (int i = 0; i < MODES_QTY; i++) {
    printf("%s\n", modes[i].name);
  }
  return(0);
}

#endif
