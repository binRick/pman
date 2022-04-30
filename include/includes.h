#pragma once
#define ASSERTF_DEF_ONCE
/////////////////////////////////////////////////////
#include <assert.h>
#include <dirent.h>
#include <getopt.h>
#include <glob.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sysexits.h>
/////////////////////////////////////////////////////
static char *get_datetime();
/////////////////////////////////////////////////////
#include "../include/ansicodes.h"
#include "../include/print.h"
#include "../submodules/assertf.h/assertf.h"
#include "../include/dbg.h"
/////////////////////////////////////////////////////
#include "../include/macros.h"
/////////////////////////////////////////////////////
#include "../submodules/env.h/env.h"
#include "../deps/rgba/rgba.h"
#include "../deps/strsplit/strsplit.h"
#include "../deps/b64/b64.h"
#include "../deps/str-replace/str-replace.h"
#include "../submodules/c_string_buffer/include/stringbuffer.h"
#include "../deps/fs/fs.h"
#include "../include/fort.h"
#include "../submodules/spin/spin.h"
#include "../deps/commander/commander.h"
#include "../deps/occurrences/occurrences.h"
#include "../deps/case/case.h"
#include "../deps/trim/trim.h"
#include "../deps/field-range-parser/field-range-parser.h"
#include "../submodules/csv_parser/csv.h"
#include "../deps/flag/flag.h"
#include "../submodules/tercontrol/tercontrol.h"
#include "../deps/timestamp/timestamp.h"
//////////////////////////////////////
#include "../src/datetime.c"
#include "../include/template/template.h"
#include "../include/int.h"
#include "../deps/is_number/is_number.h"
//#include "../include/errnos.h"
//#include "../include/utils.h"
#include "../submodules/c_stringfn/include/stringfn.h"
#include "../include/strconv.h"
