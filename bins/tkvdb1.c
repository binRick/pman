// MESON_BIN_ENABLED=false
#include "../include/includes.h"
/* calculate words frequency
 */
#include "tkvdb.h"
/* min transaction buffer size */
#define MIN_TR_SIZE    100000

/* transaction size, 100M by default */
static size_t   trsize = 100 * 1024 * 1024;
static char     *db_file = "../etc/words0.tkvdb";
static int      verbose = 0;
static uint64_t nwords_total = 0, nwords_db = 0, nlines = 1;

TKVDB_RES       rc;
tkvdb_cursor    *cursor;


int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  tkvdb        *db;
  tkvdb_tr     *tr;
  tkvdb_params *params;
  tkvdb_cursor *c;
  tkvdb_tr     *transaction;


  size_t      keysize;
  size_t      valsize;
  uint8_t     *k;
  uint8_t     *val;

  int         qty = 0;
  wchar_t     word[256];
  size_t      wordlen = 0;
  int         lower = 0, opt;

  tkvdb_datum key, value;

  params = tkvdb_params_create();
  if (!params) {
    fprintf(stderr, "Can't create database parameters\n");
    exit(1);
  }

  db = tkvdb_open(db_file, params);
  tkvdb_params_free(params);
  if (!db) {
    int err = errno;
    fprintf(stderr, "Can't open db file '%s': %s\n",
            db_file, err ? strerror(err): "corrupted database");
  }

  transaction = tkvdb_tr_create(db, NULL);
  assert_nonnull(transaction);


  cursor = tkvdb_cursor_create(transaction);
  assert_nonnull(cursor);
  rc = cursor->first(cursor);
  assert_nonnull(cursor);
  while (rc == TKVDB_OK) {
    k       = cursor->key(cursor);
    keysize = cursor->keysize(cursor);
    dbg(keysize, %lu);

    val     = cursor->val(cursor);
    valsize = cursor->valsize(cursor);
    dbg(valsize, %lu);

    rc = cursor->next(cursor);
    dbg(qty, %d);

    fprintf(stdout, "Acquired Item #%d.\n", qty);
    qty++;
  }


  qty    = 0;
  cursor = tkvdb_cursor_create(transaction);
  assert_nonnull(cursor);
  rc = cursor->first(cursor);
  assert_nonnull(cursor);


  while (rc == TKVDB_OK) {
    tkvdb_datum key   = cursor->key_datum(cursor);
    tkvdb_datum value = cursor->val_datum(cursor);
    dbg(key.size, %lu);
    dbg(value.size, %lu);
    dbg((char *)key.data, %s);
    dbg((char *)value.data, %s);
    fprintf(stdout, ">Acquired Item #%d\n", qty);
    rc = cursor->next(cursor);
  }


  cursor->free(cursor);
  printf("OK\n");


  return(EXIT_SUCCESS);
} /* main */

