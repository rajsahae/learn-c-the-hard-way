#include <stdio.h>
#include <apr_general.h>
#include <apr_getopt.h>
#include <apr_strings.h>
#include <apr_lib.h>

#include "dbg.h"
#include "db.h"
#include "commands.h"

static const char* help = 
"Usage: devpkg (-h|-S|-I[url]|-L|-F[url]|-B[url]) [-c config_opts] [-m make_opts] [-i install_opts]\n \
\nCOMMAND OPTIONS:\n \
  -S      Initialize the devpkg database at /usr/local/.devpkg/db\n \
  -I URL  Install a package with the given URL\n \
  -L      List all installed packages\n \
  -F URL  Fetch package with the given URL, but do not install it.\n \
  -B URL  Install a package with the given URL, even if it's already installed\n\n \
  For the install (-I) and build (-B) options, if you pass in a url that\n \
  end with the word \"DEPENDS\", it will consider the URL a dependency\n \
  text file and iterate through the URLs contained within that file,\n \
  installing each package in turn. (i.e. http://fileserver.com/package/DEPENDS)\n";

int main(int argc, const char* argv[])
{
  apr_pool_t* p = NULL;
  apr_pool_initialize();
  apr_pool_create(&p, NULL);

  apr_getopt_t* opt;
  apr_status_t rv;

  char ch = '\0';
  const char* optarg       = NULL;
  const char* config_opts  = NULL;
  const char* install_opts = NULL;
  const char* make_opts    = NULL;
  const char* url          = NULL;
  
  enum CommandType request = COMMAND_NONE;

  rv = apr_getopt_init(&opt, p, argc, argv);

  while(apr_getopt(opt, "I:Lc:m:i:d:SF:B:h", &ch, &optarg) == APR_SUCCESS) {
    switch (ch) {
      case 'I':
        request = COMMAND_INSTALL;
        url = optarg;
        break;

      case 'L':
        request = COMMAND_LIST;
        break;

      case 'c':
        config_opts = optarg;
        break;

      case 'm':
        make_opts = optarg;
        break;

      case 'i':
        install_opts = optarg;
        break;

      case 'S':
        request = COMMAND_INIT;
        break;

      case 'F':
        request = COMMAND_FETCH;
        url = optarg;
        break;

      case 'B':
        request = COMMAND_BUILD;
        url = optarg;
        break;

      case 'h':
        puts(help);
        return 0;

    }
  }

  switch (request) {
    case COMMAND_INSTALL:
      check(url, "You must at least give a URL");
      Command_install(p, url, config_opts, make_opts, install_opts);
      break;

    case COMMAND_LIST:
      DB_list();
      break;

    case COMMAND_FETCH:
      check(url != NULL, "You must give a URL");
      Command_fetch(p, url, 1);
      log_info("Downloaded to %s and in /tmp/", BUILD_DIR);
      break;

    case COMMAND_BUILD:
      check(url, "You must at least give a URL");
      Command_build(p, url, config_opts, make_opts, install_opts);
      break;

    case COMMAND_INIT:
      rv = DB_init();
      check(rv == 0, "Failed to make database");
      break;

    default:
      sentinel("Invalid command given");
  }

  return 0;

error:
  return -1;
}
