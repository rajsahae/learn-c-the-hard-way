#include "minunit.h"
#include "dbg.h"
#include "bstrlib.h"

char* testStr = "a string";

char* test_bfromcstr()
{
  mu_assert(bfromcstr(NULL) == NULL, "Passing NULL returned non-NULL");

  bstring str = bfromcstr(testStr);
  mu_assert(str != NULL, "Received NULL for real string");
  mu_assert(blength(str) == (int)strlen(testStr), "Lengths do not match");

  return NULL;
}

char* test_blk2bstr()
{
  mu_assert(blk2bstr(NULL, 10) == NULL, "Passing NULL returned non-NULL");
  mu_assert(blk2bstr(testStr, -1) == NULL, "Passing negative length returned non-NULL");

  int length = strlen(testStr);
  bstring str = blk2bstr(testStr, length);
  mu_assert(str != NULL, "Received NULL for real string");
  mu_assert(blength(str) == length, "Lengths do not match");

  return NULL;
}

char* bstrcpy_test()
{
  bstring testBstr = bfromcstr("test string");

  mu_assert(bstrcpy(NULL) == NULL, "Passing NULL returned non-NULL");
  bstring newString = bstrcpy(testBstr);

  mu_assert(newString != NULL, "Received NULL for real string");
  mu_assert(blength(newString) == blength(testBstr), "Lengths do not match");

  return NULL;
}

char* all_tests()
{
  mu_suite_start();

  mu_run_test(test_bfromcstr);
  mu_run_test(test_blk2bstr);

  return NULL;
}

RUN_TESTS(all_tests);
