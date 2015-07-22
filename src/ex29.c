#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <limits.h>

typedef int (*lib_function)(const char* data);
typedef int (*lib_function_2)(const char* data, long len);

int main(int argc, char* argv[])
{
  int rc = 0;
  check(argc == 4 || argc == 5, "USAGE: ex29 libex29.so function data [modifier]");

  char* lib_file    = argv[1];
  char* func_to_run = argv[2];
  char* data        = argv[3];
  void* lib         = dlopen(lib_file, RTLD_NOW);

  check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

  if (argc == 4) {
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find function %s in library %s: %s",
        func_to_run, lib_file, dlerror());

    rc = func(data);
  }
  else if (argc == 5) {
    lib_function_2 func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find function %s in library %s: %s",
        func_to_run, lib_file, dlerror());

    long len = strtol(argv[4], (char **)NULL, 10);
    check(len != 0, "Conversion of string to long failed, or 0 received");
    rc = func(data, len);
  }
  check(rc == 0, "Function %s returned %d for data: %s", func_to_run, rc, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close lib %s: %d", lib_file, rc);

  return 0;

error:
  return 1;
}
