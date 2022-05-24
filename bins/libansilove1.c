// MESON_BIN_ENABLED=true
#include "../src/includes.c"
/***********************************************************/
#define VERBOSE      true
#define WIDTH        "140"
#define BAT_STYLE    "header,numbers,rule"
#define PNG_FILE     "/tmp/ansilove1.png"
#define SRC_FILE     "../bins/libansilove1.c"
/***********************************************************/
//#define CONTENT_MODE_RAW
#define CONTENT_MODE_KAT
/***********************************************************/
int init();
int raw_content();
int kat_content();
int load_buffer();

/***********************************************************/
int                     res;
char                    *src_dirname, *src_basename, *content;
struct ansilove_ctx     ctx;
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
INLINE extern char * add_char_to_hl(char *, char);
INLINE extern char * add_str_to_hl(char *, const char *, size_t);

char                    *line = NULL;       /* Current line.                     */
size_t                  len   = 0;          /* Allocated size.                   */
char                    *hl;                /* Currently highlighted line.       */
char                    *buff       = NULL; /* Buffer to be dumped.              */
char                    *theme_file = NULL; /* Theme file.                       */
struct highlighted_line *high;              /* Highlighted line structure. */
ssize_t                 bytes_read;         /* Bytes read.                       */
FILE                    *rfp;               /* File pointer.                     */
int                     res;


int init_kat(){
  if (highlight_init(theme_file) < 0) {
    if (rfp != stdin) {
      fclose(rfp);
    }
    return(-1);
  }

  hl   = highlight_alloc_line();
  buff = highlight_alloc_line();

  return(0);
}


int kat_content(){
  res = init_kat();
  assert_eq(res, 0, %d);


  while ((bytes_read = getline(&line, &len, rfp)) != -1) {
    hl   = highlight_line(line, hl, bytes_read);
    high = ((struct highlighted_line *)hl - 1);
    buff = add_str_to_hl(buff, hl, high->idx - 1);
  }

  buff = add_char_to_hl(buff, '\0');
//  fprintf(stderr, "Acquired %lu bytes from kat\n", strlen(buff));

  high = ((struct highlighted_line *)buff - 1);
//  fprintf(stderr, "high->idx:%lu\n", high->idx);
//  fprintf(stderr, "high->size:%lu\n", high->size);

//  printf("%s", buff);
  write(fileno(stdout), buff, high->idx - 1);
  //fprintf(stderr, "Wrote %lu bytes\n", strlen(buff));

  highlight_free(hl);
  highlight_free(buff);
  free(line);

  if (rfp != stdin) {
    fclose(rfp);
  }

  highlight_finish();

  content = buff;
  //strlen(buff)+1024);
  if (VERBOSE) {
    printf("%s\n", content);
  }

  return(0);
}


int raw_content(){
  content = calloc(1024, sizeof(char));
  sprintf(content,
          AC_RESETALL AC_RED "%s\n" AC_RESETALL
          AC_RESETALL "\n" AC_RESETALL
          AC_RESETALL AC_GREEN_BLACK "%s\n" AC_RESETALL
          "\n\n\n\n\n",
          "RED",
          "GREEN"
          );
  if (VERBOSE) {
    printf("%s\n", content);
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
  src_basename = malloc(strlen(SRC_FILE));
  src_dirname  = dirname(SRC_FILE);

  assert_eq(fsio_dir_exists(src_dirname), -1, %d);
  src_basename = basename(SRC_FILE);

  if (VERBOSE) {
    dbg(src_dirname, %s);
    dbg(src_basename, %s);
  }
  return(0);
}


int load_buffer(){
  (&ctx)->maplen = (&ctx)->length = strlen(content);
  (&ctx)->buffer = (uint8_t *)content;
  assert_eq(strlen((char *)(&ctx)->buffer), strlen(content), %lu);
  return(0);
}


int main(const int argc, const char **argv){
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    exit(0);
  }
  tq_start(NULL);

  res = init();
  assert_eq(res, 0, %d);

#ifdef CONTENT_MODE_RAW
  res = raw_content();
#endif
#ifdef CONTENT_MODE_KAT
  if (argc < 2) {
    fprintf(stderr, "reading content from stdin\n");
    rfp = stdin;
  }else {
    rfp = fopen(argv[1], "r");
    if (rfp == NULL) {
      fprintf(stderr, "%s: cannot open the file %s, is it really exists?\n",
              argv[0], argv[1]);
      return(1);
    }
  }
  res = kat_content();
#endif
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

  printf(AC_GREEN_BLACK AC_BOLD
         "Wrote %lu bytes to file %s :: %s"
         AC_RESETALL "\n",
         file_size,
         PNG_FILE,
         dur
         );
  return(0);
} /* main */

