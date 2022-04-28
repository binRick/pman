#pragma once

#include <assert.h>
#include <dirent.h>
#include <getopt.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "../include/defines.h"
#include "../include/embedded-palettes.h"
#include "../include/macros.h"

#include "../deps/b64/b64.h"
#include "../deps/buffer/buffer.h"
#include "../deps/bytes/bytes.h"
#include "../deps/clibs/module/def.h"
#include "../deps/clibs/module/module.h"
#include "../deps/clibs/module/require.h"
#include "../deps/env.h/env.h"
#include "../deps/flag/flag.h"
#include "../deps/fs/fs.h"
#include "../deps/list/list.h"
#include "../deps/ms/ms.h"
#include "../deps/parson/parson.h"
#include "../deps/rgba/rgba.h"
#include "../deps/rhash_md5/byte_order.h"
#include "../deps/rhash_md5/md5.h"
#include "../deps/rhash_md5/ustd.h"
#include "../deps/strsplit/strsplit.h"
#include "../deps/timestamp/timestamp.h"
#include "../deps/tiny-regex-c/re.h"
#include "../deps/trim/trim.h"

#include "../include/types.h"

#include "../submodules/ansicodes/ansicodes.h"
#include "../submodules/dbg.h/dbg.h"
#include "../submodules/tercontrol/tercontrol.h"
