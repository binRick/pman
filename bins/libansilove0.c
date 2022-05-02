#include "../include/includes.h"
#define VERBOSE      false
#define WIDTH        "120"
#define BAT_STYLE    "header,numbers,rule"
#define SRC_FILE     "../bins/libansilove0.c"
#define PNG_FILE     "/tmp/ansilove.png"
#define FILE_NAME    "source.c"

#define CMD_TEMPLATE  "bat --file-name '%s' --italic-text always \
    --terminal-width " WIDTH " --paging never --force-colorization \
    --style=" BAT_STYLE " --theme=ansi '" SRC_FILE "'"

int                     res; 
char *src_dirname, *src_basename, *cmd, *bat_content;
struct ansilove_ctx     ctx;
struct ansilove_options options, png_options = {
  .dos          = false,
  .diz          = false,
//  .mode         = ANSILOVE_MODE_TRANSPARENT,
 // .font         = ANSILOVE_FONT_TERMINUS,
  .truecolor    = true,
  .icecolors    = true,
  .scale_factor = 2,
};

int init();
int bat();
int load_buffer();


int main(const int argc, const char **argv){
  tq_start(NULL);
  res = init();
  assert_eq(res, 0, %d);
  res = bat();
  assert_eq(res, 0, %d);

  res = ansilove_init(&ctx, &options);
  assert_eq(res, 0, %d);

  res = load_buffer();
  assert_eq(res, 0, %d);

  options.mode         = png_options.mode;
  options.truecolor    = png_options.truecolor;
  options.scale_factor = png_options.scale_factor;
  options.dos          = png_options.dos;
  options.diz          = png_options.diz;
  options.font         = png_options.font;
  options.icecolors    = png_options.icecolors;
  options.columns      = atoi(WIDTH);

  res = ansilove_ansi(&ctx, &options);
  assert_eq(res, 0, %d);
  res = ansilove_savefile(&ctx, PNG_FILE);
  assert_eq(res, 0, %d);
  size_t file_size = fs_size(PNG_FILE);
  assert_ge(file_size, 0, %lu);
  ansilove_clean(&ctx);
  char *dur = tq_stop(AC_RESETALL AC_BLUE AC_REVERSED "Total Duration");
  printf( AC_GREEN_BLACK AC_BOLD 
          "Wrote %lu bytes to file %s :: %s" 
          AC_RESETALL "\n"
          , file_size
          , PNG_FILE
          , dur
          );
  return(0);
}


int bat(){
  struct ScriptExecOptions options = scriptexec_create_options();

  options.runner            = "/bin/sh";
  options.exit_on_error     = true;
  options.working_directory = src_dirname;
  options.print_commands    = false;
  assert_eq(fsio_file_exists(SRC_FILE), -1, %d);
  struct ScriptExecResult result = scriptexec_run_with_options(cmd, options);

  assert_eq(result.code, 0, %d);
  bat_content = malloc(strlen(result.out));
  sprintf(bat_content, "%s", result.out);
  assert_ge(strlen(bat_content), 0, %lu);
  free(result.out);
  free(result.err);

  if (VERBOSE) {
    printf("%s\n", bat_content);
  }
  return(0);
}


int init(){
  if (fsio_file_exists(PNG_FILE)) {
    fsio_remove(PNG_FILE);
  }
  assert_eq(fsio_file_exists(PNG_FILE), 0, %d);
  assert_eq(fsio_file_exists(SRC_FILE), -1, %d);
  src_dirname  = malloc(strlen(SRC_FILE));
  cmd          = malloc(strlen(strdup(CMD_TEMPLATE)) + 1024);
  src_basename = malloc(strlen(SRC_FILE));
  src_dirname  = dirname(SRC_FILE);
  assert_eq(fsio_dir_exists(src_dirname), -1, %d);
  src_basename = basename(SRC_FILE);
  sprintf(cmd, CMD_TEMPLATE, src_basename);
  if (VERBOSE) {
    dbg(cmd, %s);
    dbg(src_dirname, %s);
    dbg(src_basename, %s);
  }
  return(0);
}


int load_buffer(){
  (&ctx)->maplen = (&ctx)->length = strlen(bat_content);
  (&ctx)->buffer = (uint8_t *)bat_content;
  assert_eq(strlen((char *)(&ctx)->buffer), strlen(bat_content), %lu);
  return(0);
}
