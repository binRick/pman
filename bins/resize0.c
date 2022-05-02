#include "../src/includes.c"
// MESON_BIN_ENABLED=true
#define RESIZE_SCRIPT_TEMPLATE    "env RESIZE_WIDTH=%u RESIZE_HEIGHT=%u ../../ansi/get_rgb_image.sh %u %u %u"
#define VERBOSE_MODE false
#define COLOR_BOUNDARY            8
#define WIDTH                     40
#define HEIGHT                    20
#define IMAGES_QTY                (256 / COLOR_BOUNDARY) * (256 / COLOR_BOUNDARY) * (256 / COLOR_BOUNDARY)

typedef struct resize_request resize_request;
struct resize_request {
  unsigned int width;
  unsigned int height;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  char         *path;
  int          exit_code;
  int          exists;
};
struct subprocess_s subprocess;

int resize();


int main(const int argc, const char **argv){    
  int qty = 0;
  if ((argc == 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Test Mode");
    return(0);
  }

  printf("Generating %d Images\n", IMAGES_QTY);
  for (int red = 0; red < 256; red += COLOR_BOUNDARY) {
    for (int green = 0; green < 256; green += COLOR_BOUNDARY) {
      for (int blue = 0; blue < 256; blue += COLOR_BOUNDARY) {
        qty++;
        resize_request r = {
          .width     = WIDTH,
          .height    = HEIGHT,
          .red       = red,
          .green     = green,
          .blue      = blue,
          .path      = NULL,
          .exit_code = -1,
          .exists    = -1,
        };
        resize(&r);
        if (fs_exists(r.path)) {
          OK(r.path);
        }
        printf("Finished %d/%d\n", qty, IMAGES_QTY);
      }
    }
  }
  return(0);
}


int resize(resize_request *r){
  int  result;
  char *cmd = malloc(strlen(RESIZE_SCRIPT_TEMPLATE) + 32);

  sprintf(cmd, RESIZE_SCRIPT_TEMPLATE, r->width, r->height, r->red, r->green, r->blue);
    if(VERBOSE_MODE)
  dbg(cmd, %s);

  const char *command_line[] = { "/bin/sh", "-c", cmd, NULL };

  result = subprocess_create(command_line, 0, &subprocess);
  result = subprocess_join(&subprocess, &r->exit_code);

  if (result != 0) {
    FILE *p_stderr = subprocess_stdout(&subprocess);
    char *err      = malloc(1024);
    fgets(err, 1024 * 16, p_stderr);
    if(VERBOSE_MODE)
    dbg(err, %s);
    free(err);
  }else{
    assert_eq(result, 0, %d);
    FILE *p_stdout = subprocess_stdout(&subprocess);
    char *out      = malloc(1024);
    fgets(out, 1024, p_stdout);
    if(VERBOSE_MODE)
    dbg(r->exit_code, %d);
    r->path = trim(out);
    free(out);
  }
  return(0);
}
