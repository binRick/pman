#include "../include/includes.h"
// MESON_BIN_ENABLED=false


int main(int argc, char **argv) {
  log_init(stdout);
  log(LOG_INFO,
      log_string("msg", "records added successfully"),
      log_uint("count", 2));
  log(LOG_INFO,
      log_string("msg", "records added successfully"),
      log_int64("count", 92233));
  log(LOG_INFO,
      log_string("msg", "record added successfully"),
      log_string("name", "Brian"),
      log_double("elapsed", 5.76));
  log(LOG_FATAL, log_string("msg", "dead :("));
}
