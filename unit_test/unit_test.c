# define _GNU_SOURCE
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../container_func.h"
#include "CUnit/Basic.h"

/* Pointer to the file used by the tests. */
static char* user = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
  free(user);
  return 0;    
}

void testCREATE_CONTAINER(void)
{
  const char *password = "fake_pass";
  
  CU_ASSERT(-1 != create_container(user, password));
}

char *getUserName()
{
  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  if (pw)
    {
      return pw->pw_name;
    }

  return NULL;
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main(void)
{
  if ((user = getUserName()) == NULL)
    {
      fprintf(stderr, "Fail to get your login.user = %s\n", getUserName());
      return -1;
    }
  
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("First Suite", init_suite, clean_suite);
  if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test of create/open container", testCREATE_CONTAINER)))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
