#pragma once
/**********************************************/
#include "../src/includes.c"


int view_colorcode(){
  return(__view_colorcode(args->colorcode));
}
/**********************************************/
struct pman_mode_t modes[] = {
  { .name = "debug_args",                .fxn = debug_args                       },
  { .name = "modes",                     .fxn = list_modes                       },
  { .name = "color_names",               .fxn = list_color_names                 },
  { .name = "list_color_names_and_rgbs", .fxn = list_color_names_and_rgbs        },
  { .name = "show_color_name_tables",    .fxn = list_color_rgbs                  },
  { .name = "palettes",                  .fxn = list_palette_names               },
  { .name = "view_palette",              .fxn = view_palette                     },
  { .name = "view_colorcode",            .fxn = view_colorcode                   },
  { .name = "default_palette",           .fxn = view_default_palette             },
  { .name = "default_properties",        .fxn = print_default_palette_properties },
  { .name = "cur",                       .fxn = print_current_palette_colors     },
  { .name = "err",                       .fxn = debug_error                      },
  { .name = "msg",                       .fxn = debug_msg                        },
  { .name = "die",                       .fxn = debug_die                        },
  { NULL },
}; const size_t MODES_QTY = LIST_QTY(modes);


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
int list_modes(){
  for (int i = 0; i < MODES_QTY; i++) {
    printf("%s\n", modes[i].name);
  }
  return(0);
}
/**********************************************/
