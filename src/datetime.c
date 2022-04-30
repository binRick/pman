#pragma once
///////////////////////////////////////////
#ifndef DATETIME_C
#define DATETIME_C
///////////////////////////////////////////
#include <stdio.h>            // fprintf
#include <stdlib.h>           // NULL, EXIT_*
#include <time.h>
#include <unistd.h>           // getopt(), sleep()
///////////////////////////////////////////
//#include "../include/includes.h"
///////////////////////////////////////////
#define DEFAULT_FORMAT      "%F %T"
#define DEFAULT_INTERVAL    1
#define RESULT_LENGTH       64


///////////////////////////////////////////
static char *print_datetime(const char *format, int len, int utc, int offset){
  time_t    now     = time(NULL) + (offset * 60 * 60);
  struct tm *tm     = utc ? gmtime(&now) : localtime(&now);
  char      *result = malloc(sizeof(char) * len);

  strftime(result, len, format, tm);
  return(result);
}


static char *get_datetime(){
  char *format  = NULL; // format string for use with strftime()
  int  offset   = 0;    // timezone offset, in hours, from UTC
  int  use_utc  = 0;    // use UTC instead of local time?
  int  monitor  = 0;    // keep running and printing?
  int  interval = 0;    // seconds between printing the datetime

  format   = DEFAULT_FORMAT;
  interval = DEFAULT_INTERVAL;
  setlinebuf(stdout);
  return(print_datetime(format, RESULT_LENGTH, use_utc, offset));
}

#endif
