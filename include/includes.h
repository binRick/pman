#pragma once
#define _DEFAULT_SOURCE
/////////////////////////////////////////////////////
#include <assert.h>
#include <stddef.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <getopt.h>
#include <glob.h>
#include <inttypes.h>
#include <libgen.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
/////////////////////////////////////////////////////
#include "../include/includes-pman-ansi.h"
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
#include "../include/includes-module.h"
#include "../submodules/tinydir/tinydir.h"
/////////////////////////////////////////////////////
#include "../submodules/svpng/svpng.inc"
#include "../submodules/generic-print/print.h"
#include "../submodules/csplit/csplit.h"
#include "../include/pman.h"
//#include "../include/vterm_keycodes.h"
#include "../include/ansicodes.h"
#include "../include/tmt.h"
#include "../include/dbg.h"
#include "../deps/sqlite/sqlite3ext.h"
#include "../deps/url/url.h"
#include "../deps/case/case.h"
#include "../deps/is-email/is-email.h"
#include "../submodules/djbhash/src/djbhash.h"
#include "../include/timequick.h"
#include "../submodules/assertf.h/assertf.h"
#include "../submodules/expand-braces/expand-braces.h"
#include "../submodules/ctable/src/table.h"
/////////////////////////////////////////////////////
#include "../submodules/str-ends-with/src/str-ends-with.h"
/////////////////////////////////////////////////////
#include "../include/macros.h"
/////////////////////////////////////////////////////
#include "../deps/timer/timer.h"
#include "../deps/closure/closure.h"
#include "../deps/tempdir/tempdir.h"
#include "../deps/strdup/strdup.h"
#include "../deps/bytes/bytes.h"
#include "../deps/b64/b64.h"
#include "../deps/case/case.h"
#include "../deps/commander/commander.h"
#include "../deps/field-range-parser/field-range-parser.h"
#include "../deps/flag/flag.h"
#include "../deps/fs/fs.h"
#include "../deps/occurrences/occurrences.h"
#include "../deps/parson/parson.h"
#include "../deps/rgba/rgba.h"
#include "../deps/str-replace/str-replace.h"
#include "../deps/strsplit/strsplit.h"
#include "../deps/timestamp/timestamp.h"
#include "../deps/trim/trim.h"
#include "../include/fort.h"
#include "../submodules/buffet/src/buffet.h"
#include "../submodules/bestline/bestline.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../submodules/csv_parser/csv.h"
#include "../submodules/env.h/env.h"
#include "../submodules/fsio/include/fsio.h"
#include "../submodules/libansilove/include/ansilove.h"
#include "../submodules/libconfuse/src/confuse.h"
#include "../submodules/libdotenv/dot_env.h"
#include "../submodules/libterminput/libterminput.h"
#include "../submodules/scriptexec/include/scriptexec.h"
#include "../submodules/simpleconf/simpleconf.h"
#include "../submodules/spin/spin.h"
#include "../submodules/tiny-regex-c/re.h"
#include "../submodules/uptime/include/uptime/uptime.h"
#include "../submodules/wildcardcmp/wildcardcmp.h"
//#include "../submodules/liblogger/logger.h"
#include "../submodules/libusb/libusb/libusb.h"
#include "../submodules/subprocess.h/subprocess.h"
#include "../submodules/tercontrol/tercontrol.h"
#include "../submodules/tkvdb/tkvdb.h"
//#include "../submodules/c_vector/include/vector.h"
#include "../include/template/template.h"
//#include "../submodules/c_eventemitter/include/eventemitter.h"
#include "../submodules/c_forever/include/forever.h"
#include "../submodules/socket99/socket99.h"
//////////////////////////////////////
#include "../deps/is_number/is_number.h"
#include "../deps/list/list.h"
#include "../include/int.h"
//#include "../src/datetime.c"
#include "../include/strconv.h"
#include "../submodules/c_stringfn/include/stringfn.h"
#include "../deps/rhash_md5/md5.h"
#include "../submodules/kat/include/highlight.h"
#include "../submodules/kat/include/optparse.h"

#define OK(MSG){ fprintf(stderr, "  \e[32m\u2713 \e[90mOK- %s\e[0m\n", MSG); }
static char *get_datetime();
