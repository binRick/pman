// MESON_BIN_ENABLED=true
#include "../src/katmodule0.c"
#define MAX_C_FILES          2
#define MIN_PNG_WIDTH        40
#define VERBOSE              true
#define PNG_FILE_TEMPLATE    "/tmp/katmodule-%d.png"

/***********************************************************/
int res;
char                    *src_dirname, *src_basename, *content;
struct ansilove_options options, png_options = {
  .dos = false,
  .diz = false,
//  .mode         = ANSILOVE_MODE_TRANSPARENT,
//  .font         = ANSILOVE_FONT_TERMINUS,
  .truecolor = true,
  .icecolors = true,
  // .scale_factor = 2,
};
/***********************************************************/

struct StringFNStrings get_files(char *dir);

char **CODES;
char
     CODE0[] = \
  "int main(int argc, char **argv){ /* Comment. */\n"
  "    printf(\"Hello World %s\\n\", argv[1]);\n"
  "}",
  CODE1[] = \
  "char * get_string(){ /* Comment. */\n"
  "    char s[1024] = \"ok\"\n"
  "    return(s);\n"
  "}";

module(katmodule0) * katmodule0;


static inline void quit(int errcode, const char *msg){
  puts(msg);
  exit(errcode);
}


int init(){
  katmodule0 = require(katmodule0);
  return(0);
}


int work(){
  katmodule0->mode = LOGGER_DEBUG;
  katmodule0->info("hello");
  katmodule0->error("oops");
  katmodule0->debug("help");
  return(0);
}


int clean(){
  clib_module_free(katmodule0);
  return(0);
}


int main(const int argc, const char **argv){
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Test OK"); return(0);
  }
  tq_set_unit(tq_MILLISECONDS);
  if (highlight_init(NULL) < 0) {
    quit(-1, "Unable to initialize the highlight!\n");
  }

  char                   *C2      = fsio_read_text_file("./bins/uptime0.c");
  char                   *C3      = fsio_read_text_file("./bins/djbhash0.c");
  char                   *CODES[] = {
    CODE0,
    CODE1,
    C2,
    C3,
    NULL,
  };
  struct StringFNStrings c_files = get_files("./bins");

  dbg(c_files.count, %d);
  for (int i = 0; i < c_files.count; i++) {
    if (strlen(c_files.strings[i]) < 1) {
      continue;
    }
    //  CODES[i+2] = fsio_read_text_file(c_files.strings[i]);
    dbg(c_files.strings[i], %s);
    dbg(i, %d);
  }
//  CODES[c_files.count+2] = NULL;
  char **codes = CODES;

  char *line;

  for (int i = 0; codes[i]; i++) {
    tq_start(NULL);
    line = NULL;
    char *c_code = strdup(CODES[i]);
    dbg(strlen(c_code), %lu);
//    if(strlen(c_code) > (1024*1)) continue;

    struct StringFNStrings lines     = stringfn_split_lines(c_code);
    struct StringBuffer    *sb       = stringbuffer_new_with_options(1024, true);
    int                    max_width = MIN_PNG_WIDTH;

    for (int i = 0; i < lines.count; i++) {
      if (strlen(lines.strings[i]) > max_width) {
        max_width = strlen(lines.strings[i]);
      }

      line = highlight_line(lines.strings[i], i > 0 ? line : NULL, 0);
      stringbuffer_append_string(sb, line);
      if (i <= lines.count - 2) {
        stringbuffer_append_string(sb, "\n");
      }
    }
    struct StringFNStrings newlines = stringfn_split_lines(stringbuffer_to_string(sb));
    char                   *dt      = malloc(1024);
    sprintf(dt, "orig lines bytes: %lu|orig lines: %d|  newlines qty:%d|bytes:%lu|\n",
            strlen(c_code), lines.count,
            newlines.count,
            strlen(stringbuffer_to_string(sb))
            );
    struct ansilove_ctx *ctx    = malloc(sizeof(struct ansilove_ctx));
    int                 ctx_res = ansilove_init(ctx, &options);
    assert_eq(ctx_res, 0, %d);
    char                *content = malloc(stringbuffer_get_content_size(sb) + 1);
    content = stringbuffer_to_string(sb);
    stringbuffer_release(sb);

    ctx->maplen = ctx->length = strlen(content);
    ctx->buffer = (uint8_t *)content;
    assert_eq(strlen((char *)ctx->buffer), strlen(content), %lu);

    options.mode         = png_options.mode;
    options.truecolor    = png_options.truecolor;
    options.scale_factor = png_options.scale_factor;
    options.dos          = png_options.dos;
    options.diz          = png_options.diz;
    options.font         = png_options.font;
    options.icecolors    = png_options.icecolors;
    options.columns      = max_width;

    //fprintf(stderr, "%s", content);
    res = ansilove_ansi(ctx, &options);
    assert_eq(res, 0, %d);

    char *PNG_FILE = malloc(1024);
    assert_nonnull(PNG_FILE);

    sprintf(PNG_FILE, PNG_FILE_TEMPLATE, i);

    res = ansilove_savefile(ctx, PNG_FILE);
    assert_eq(res, 0, %d);
    size_t file_size = fs_size(PNG_FILE);

    assert_ge(file_size, 0, %lu);
    ansilove_clean(ctx);

    char *dur = tq_stop(":");
    fprintf(stderr, "---------------------\n");
    fprintf(stderr, "--#%d>\t(file: %s, size: %s) | (%d lines) | (%d width)|dur: %s|\n\t%s",
            i,
            bytes_to_string(fs_size(PNG_FILE)), PNG_FILE,
            lines.count, max_width, dur, dt
            );
    fprintf(stderr, "---------------------\n");
    free(dt);
    free(PNG_FILE);
    free(content);
    free(ctx);
  }

  highlight_free(line);
  highlight_finish();


  return(0);
} /* main */

struct StringFNStrings get_files(char *path){
  struct StringBuffer *sb = stringbuffer_new_with_options(1024, true);
  tinydir_dir         dir;

  if (tinydir_open(&dir, path) == -1) {
    perror("Error opening file");
    goto done;
  }

  while (dir.has_next) {
    tinydir_file file;
    if (tinydir_readfile(&dir, &file) == -1) {
      perror("Error getting file");
      goto done;
    }
    if ((strcmp(file.name, ".") == 0) || (strcmp(file.name, "..") == 0)) {
    }else{
      bool is_c_file = (
        !stringfn_starts_with(file.name, ".")
                       && stringfn_ends_with(file.name, ".c")
                       && !stringfn_starts_with(file.name, "katmodule")
                       && !stringfn_starts_with(file.name, "libansilove0")
                       && stringfn_starts_with(file.name, "uptime")
        );

      if (is_c_file) {
        stringbuffer_append_string(sb, path);
        stringbuffer_append_string(sb, "/");
        stringbuffer_append_string(sb, file.name);
        stringbuffer_append_string(sb, "\n");
      }
      if (false) {
        printf(
          "<tinydir> Name: " AC_RESETALL AC_YELLOW "%25s" AC_RESETALL
          "|"
          "Dir? " AC_RESETALL AC_BLUE "%3s" AC_RESETALL
          "|"
          "C? " AC_RESETALL AC_BLUE "%3s" AC_RESETALL
          "|"
          "\n",
          file.name,
          file.is_dir ? "Yes" : "No",
          is_c_file ? "Yes" : "No"
          );
      }
    }
    if (tinydir_next(&dir) == -1) {
      perror("Error getting next file");
      goto done;
    }
  }

done:
  tinydir_close(&dir);
  struct StringFNStrings c_files = stringfn_split_lines_and_trim(stringbuffer_to_string(sb));

  stringbuffer_release(sb);
  return(c_files);
} /* get_files */

