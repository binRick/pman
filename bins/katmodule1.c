// MESON_BIN_ENABLED=true
#include "../src/katmodule1.c"

#define VERBOSE             true
#define DO_LOAD_FILENAME    true

const char LOAD_FILENAME[] = "/tmp/uptime0.c";
const char          SAVE_FILENAME[] = "/tmp/uptime0.png";

struct StringBuffer *save_filename, *load_filename;
void katmodule1_debug();

module(katmodule1) * katmodule1;


int init(){
  katmodule1 = require(katmodule1);

  dbg(katmodule1->loggermode, %d);
  dbg(katmodule1->options.truecolor, %d);

  katmodule1->overwrite_dst_filename = true;
  katmodule1->loggermode             = LOGGER_DEBUG;
  katmodule1->options.truecolor      = false;

  return(0);
}


void katmodule1_debug(){
  dbg(katmodule1->loggermode, %d);
  dbg(katmodule1->options.truecolor, %d);

  dbg(katmodule1->src_filename, %s);
  dbg(strlen(katmodule1->content), %lu);

  dbg(katmodule1->lines.count, %d);
  dbg(katmodule1->max_width, %lu);
  dbg(katmodule1->highlighted_content, %s);
  dbg(katmodule1->content_width, %lu);
  dbg(katmodule1->options.columns, %d);
}


int katmodule1_loader(){
  int r;

  if (DO_LOAD_FILENAME) {
    r = katmodule1->srcfile(stringbuffer_to_string(load_filename));
    OK("Loaded file");
  }else{
    char *content = fsio_read_text_file(stringbuffer_to_string(load_filename));
    OK("Loaded content");
    OK(content);
    r = katmodule1->setcontent(content);
  }
  assert_eq(r, 0, %d);

  return(0);
}


int work(){
  int r;

  katmodule1_debug();

  r = katmodule1_loader();
  assert_eq(r, 0, %d);

  katmodule1_debug();

  r = katmodule1->parsecontent();
  assert_eq(r, 0, %d);

  r = katmodule1->dstfile(stringbuffer_to_string(save_filename));
  assert_eq(r, 0, %d);

  r = katmodule1->writepng();
  assert_eq(r, 0, %d);

  katmodule1_debug();

  return(0);
}


int clean(){
  clib_module_free(katmodule1);
  return(0);
}


int main(const int argc, const char **argv){
  tq_set_unit(tq_MILLISECONDS);
  load_filename = stringbuffer_new_with_options(1024, true);
  save_filename = stringbuffer_new_with_options(1024, true);
  if (argc > 1 && strlen(argv[1]) > 4 && fsio_file_exists(argv[1])) {
    stringbuffer_append_string(load_filename, argv[1]);
  }else{
    stringbuffer_append_string(load_filename, LOAD_FILENAME);
  }
  if (argc > 2 && strlen(argv[2]) > 4) {
    stringbuffer_append_string(save_filename, argv[2]);
  }else{
    stringbuffer_append_string(save_filename, SAVE_FILENAME);
  }

  dbg(stringbuffer_to_string(save_filename), %s);
  dbg(stringbuffer_to_string(load_filename), %s);

  int r = init();

  assert_eq(r, 0, %d);

  r = work();
  assert_eq(r, 0, %d);

  r = clean();
  assert_eq(r, 0, %d);

  OK("katmodule1");
}

/*
 * struct StringFNStrings get_files(char *path){
 * struct StringBuffer *sb = stringbuffer_new_with_options(1024, true);
 * tinydir_dir         dir;
 *
 * if (tinydir_open(&dir, path) == -1) {
 *  perror("Error opening file");
 *  goto done;
 * }
 *
 * while (dir.has_next) {
 *  tinydir_file file;
 *  if (tinydir_readfile(&dir, &file) == -1) {
 *    perror("Error getting file");
 *    goto done;
 *  }
 *  if ((strcmp(file.name, ".") == 0) || (strcmp(file.name, "..") == 0)) {
 *  }else{
 *    bool is_c_file = (
 *      !stringfn_starts_with(file.name, ".")
 *                     && stringfn_ends_with(file.name, ".c")
 *                     && !stringfn_starts_with(file.name, "katmodule")
 *                     && !stringfn_starts_with(file.name, "libansilove0")
 *                     && stringfn_starts_with(file.name, "uptime")
 *      );
 *
 *    if (is_c_file) {
 *      stringbuffer_append_string(sb, path);
 *      stringbuffer_append_string(sb, "/");
 *      stringbuffer_append_string(sb, file.name);
 *      stringbuffer_append_string(sb, "\n");
 *    }
 *    if (false) {
 *      printf(
 *        "<tinydir> Name: " AC_RESETALL AC_YELLOW "%25s" AC_RESETALL
 *        "|"
 *        "Dir? " AC_RESETALL AC_BLUE "%3s" AC_RESETALL
 *        "|"
 *        "C? " AC_RESETALL AC_BLUE "%3s" AC_RESETALL
 *        "|"
 *        "\n",
 *        file.name,
 *        file.is_dir ? "Yes" : "No",
 *        is_c_file ? "Yes" : "No"
 *        );
 *    }
 *  }
 *  if (tinydir_next(&dir) == -1) {
 *    perror("Error getting next file");
 *    goto done;
 *  }
 * }
 *
 * done:
 * tinydir_close(&dir);
 * struct StringFNStrings c_files = stringfn_split_lines_and_trim(stringbuffer_to_string(sb));
 *
 * stringbuffer_release(sb);
 * return(c_files);
 * } */ /* get_files */

