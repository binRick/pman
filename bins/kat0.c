// MESON_BIN_ENABLED=true
#include "../src/includes.c"

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


int main(const int argc, const char **argv){
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    OK("Test OK"); return(0);
  }
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

  res = init_kat();
  assert_eq(res, 0, %d);

  while ((bytes_read = getline(&line, &len, rfp)) != -1) {
    hl   = highlight_line(line, hl, bytes_read);
    high = ((struct highlighted_line *)hl - 1);
    buff = add_str_to_hl(buff, hl, high->idx - 1);
  }

  buff = add_char_to_hl(buff, '\0');
  //fprintf(stderr, "Acquired %lu bytes from kat\n", strlen(buff));

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
} /* main */
