#pragma once
#define ASSERTF_DEF_ONCE
/////////////////////////////////////////////////////
#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>
#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <time.h>
#include <time.h>
#include <unistd.h>
/////////////////////////////////////////////////////
#include "../include/includes-pman-ansi.h"
/////////////////////////////////////////////////////
static char *get_datetime();

/////////////////////////////////////////////////////
#include "../include/ansicodes.h"
#include "../include/dbg.h"
#include "../include/print.h"
#include "../include/timequick.h"
#include "../submodules/assertf.h/assertf.h"
/////////////////////////////////////////////////////
#include "../include/macros.h"
/////////////////////////////////////////////////////
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
#include "../submodules/bestline/bestline.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../submodules/csv_parser/csv.h"
#include "../submodules/env.h/env.h"
#include "../submodules/fsio/include/fsio.h"
#include "../submodules/libconfuse/src/confuse.h"
#include "../submodules/libdotenv/dot_env.h"
#include "../submodules/libterminput/libterminput.h"
#include "../submodules/scriptexec/include/scriptexec.h"
#include "../submodules/simpleconf/simpleconf.h"
#include "../submodules/spin/spin.h"
#include "../submodules/wildcardcmp/wildcardcmp.h"
#include "../submodules/tiny-regex-c/re.h"
//#include "../submodules/liblogger/logger.h"
#include "../submodules/subprocess.h/subprocess.h"
#include "../submodules/tercontrol/tercontrol.h"
#include "../submodules/tkvdb/tkvdb.h"
//////////////////////////////////////
#include "../deps/is_number/is_number.h"
#include "../include/int.h"
#include "../include/template/template.h"
#include "../src/datetime.c"
//#include "../include/errnos.h"
//#include "../include/utils.h"
#include "../include/strconv.h"
#include "../submodules/c_stringfn/include/stringfn.h"
