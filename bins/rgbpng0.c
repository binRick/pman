// MESON_BIN_ENABLED=true
#include "../src/includes.c"
/********************************************************************/
#define SIZE                 50
#define RED                  100
#define GREEN                150
#define BLUE                 120
#define ALPHA                0
#define PNG_FILE_TEMPLATE    "rgb-%d-%d-%d-%d.png"
#define ENCODED_PNG_FILE_TEMPLATE    "%s.txt"
/********************************************************************/
FILE   *fp;
int    res = -1, BUF_SIZE = 1024;
char   *PNG_FILE, *msg, *rgb_data_dur, *total_dur, *write_png_dur, *init_dur, *handle_rgb_png_dur, *cleanup_dur;
size_t png_file_size;
/********************************************************************/


int handle_rgb_png(void) {
  unsigned x, y; unsigned char rgb[SIZE * SIZE * 3], *p = rgb;

  tq_start(NULL);
  for (y = 0; y < SIZE; y++) {
    for (x = 0; x < SIZE; x++) {
      *p++ = (unsigned char)RED; *p++ = (unsigned char)GREEN; *p++ = (unsigned char)BLUE;
    }
  }
  rgb_data_dur = tq_stop("");

  tq_start(NULL);
  svpng(fp, SIZE, SIZE, rgb, ALPHA);
  write_png_dur = tq_stop("");

  png_file_size = fs_size(PNG_FILE);
  assert_ge(png_file_size, 1024, %lu);

  return(0);
}


int cleanup(){
  res = fclose(fp);
  assert_eq(res, 0, %d);

  return(0);
}


int init(){
  tq_set_unit(tq_MILLISECONDS);

  msg = malloc(BUF_SIZE * 10);
  assert_nonnull(msg);

  PNG_FILE = malloc(BUF_SIZE * 10);
  assert_nonnull(PNG_FILE);

  int filename_len = sprintf(PNG_FILE,
                             PNG_FILE_TEMPLATE,
                             RED,
                             GREEN,
                             BLUE,
                             ALPHA
                             );
  assert_ge(filename_len, 0, %d);

  char *ts = stringfn_trim(stringfn_substring(PNG_FILE, 0, strlen(PNG_FILE)-4));

  if (fs_exists(PNG_FILE) == 0) {
    res = unlink(PNG_FILE);
    assert_eq(res, 0, %d);
    res = fs_exists(PNG_FILE);
    assert_eq(res, -1, %d);
  }

  fp = fopen(PNG_FILE, "wb");
  assert_nonnull(fp);

  return(0);
}


int rgb_png_logic(void) {
  tq_start(NULL);
  res      = init();
  init_dur = tq_stop("");
  assert_eq(res, 0, %d);

  res                = handle_rgb_png(); 
  assert_eq(res, 0, %d);



  tq_start(NULL);
  res = cleanup();
  assert_eq(res, 0, %d);
  cleanup_dur = tq_stop("");

  return(0);
}


int rgb_report(){
  sprintf(msg,
          AC_RESETALL "\n" AC_YELLOW AC_ITALIC "File Properties:" AC_RESETALL
          AC_RESETALL "\n\t|File Name:       " AC_ITALIC AC_BRIGHT_CYAN_BLACK "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|File Size:       " AC_ITALIC AC_GREEN_BLACK AC_BOLD   "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|File Dimensions: " AC_ITALIC AC_MAGENTA_BLACK AC_BOLD   "%dx%d" AC_RESETALL ""
          AC_RESETALL "\n" AC_YELLOW AC_ITALIC "RGB Properties:" AC_RESETALL
          AC_RESETALL "\n\t|Red:             " AC_ITALIC AC_RED   "%3d" AC_RESETALL ""
          AC_RESETALL "\n\t|Green:           " AC_ITALIC AC_GREEN   "%3d" AC_RESETALL ""
          AC_RESETALL "\n\t|Blue:            " AC_ITALIC AC_BLUE   "%3d" AC_RESETALL ""
          AC_RESETALL "\n\t|Alpha:           " AC_ITALIC AC_WHITE_BLACK   "%3d" AC_RESETALL ""
          AC_RESETALL "\n" AC_YELLOW AC_ITALIC "Durations:" AC_RESETALL
          AC_RESETALL "\n\t|Initialization:  " AC_ITALIC AC_REVERSED AC_BLUE   "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|Handle RGB PNG:  " AC_ITALIC AC_REVERSED AC_BLUE   "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|Write PNG:       " AC_ITALIC AC_REVERSED AC_BLUE "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|Cleanup:         " AC_ITALIC AC_REVERSED AC_BLUE "%s" AC_RESETALL ""
          AC_RESETALL "\n\t|Total:           " AC_ITALIC AC_REVERSED AC_BLUE "%s" AC_RESETALL "",

          PNG_FILE, bytes_to_string(png_file_size), SIZE, SIZE, 
          RED, GREEN, BLUE, ALPHA,
          init_dur, handle_rgb_png_dur, write_png_dur, cleanup_dur, total_dur
          );

  fprintf(stdout,
          AC_RESETALL AC_GREEN_BLACK AC_BOLD "%s" AC_RESETALL "\n",
          msg
          );

  return(0);
}


int main(void) {
  tq_start(NULL); //total_dur

  tq_start(NULL);
  res       = rgb_png_logic();
  assert_eq(res, 0, %d);
  handle_rgb_png_dur = tq_stop("");

  total_dur = tq_stop("");

  res = rgb_report();
  assert_eq(res, 0, %d);

  free(msg);
  free(PNG_FILE);

  OK("PNG File Generated");
  return(0);
}

