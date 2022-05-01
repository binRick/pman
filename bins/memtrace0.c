#include "../include/includes.h"
#include "../submodules/memtrace/include/memtrace3.h"


int main() {
  void *ptr = malloc(64);

  free(ptr);
}
