#pragma once
#include "../include/includes.h"


int debug_error(){
  DO_ERR("some error"); return(0);
}


int debug_msg(){
  DO_MSG("some message"); return(0);
}


int debug_die(){
  DO_DIE("critical error"); return(0);
}


static char *__basename(const char *path){
  const char *slash = strrchr(path, '/');

  if (slash) {
    path = slash + 1;
  }
  return((char *)path);
}
