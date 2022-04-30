#ifndef DBG_H_c49aa87c_54eb_46d2_8d72_a51f5efce2ac
#define DBG_H_c49aa87c_54eb_46d2_8d72_a51f5efce2ac
#include <assert.h>
#include <stdio.h>
#include <string.h>
const char *bname_b49cf5f69111(const char *path){
  const char *p;
  p = strrchr(path, '/');
  return(p != NULL ? p + 1 : path);
}

#define COL_NONE    ""
#define COL_RST     "\x1b[0m"
#define COL_DBG     "\x1b[02m"
#define COL_EXPR    "\x1b[36m"
#define COL_VAL     "\x1b[01m"
#define COL_TYPE    "\x1b[32m"
#define DBG_H_COL(out, col)    (col)
#ifndef xstr
#define xstr0(x)    #x
#define xstr(x)     xstr0(x)
#endif
#define DBG_H_FILE    __BASE_FILE__
#define x_dbg_ac3a2859(out, x, fs)    ({                            \
    typeof(x) _x0 = (x);                                            \
    int _n0 = fprintf(                                              \
      out, "%s[%s:%d (%s)]%s %s%s%s = %s" xstr(fs) "%s (%s%s%s)\n", \
      DBG_H_COL(out, COL_DBG),                                      \
      bname_b49cf5f69111(DBG_H_FILE), __LINE__, __func__,           \
      DBG_H_COL(out, COL_RST),                                      \
      DBG_H_COL(out, COL_EXPR), #x, DBG_H_COL(out, COL_RST),        \
      DBG_H_COL(out, COL_VAL), _x0, DBG_H_COL(out, COL_RST),        \
      DBG_H_COL(out, COL_TYPE), #fs, DBG_H_COL(out, COL_RST)        \
      );                                                            \
    assert(_n0 > 0);                                                \
    _x0;                                                            \
  })
#define dbg(x, fs)                    x_dbg_ac3a2859(stdout, x, fs)
#define dbge(x, fs)                   x_dbg_ac3a2859(stderr, x, fs)
#endif
