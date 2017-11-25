#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "container_func.h"

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  printf("Acct mgmt\n");
  return PAM_SUCCESS;
}

void	cleanup(pam_handle_t *pamh, void *data, int error_status)
{
  free(data);
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  const char *user = NULL;
  char	*password = NULL;
  int  retval = -1;

  if ((retval = pam_get_user(pamh, &user, "Login:" )) != PAM_SUCCESS)
    return (retval);
  if ((retval = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&password)) != PAM_SUCCESS)
    return (retval);
  printf("In auth, pass = '%s'\n", password);
  if (pam_set_data(pamh, "Password", strdup(password), &cleanup) != PAM_SUCCESS)
      return retval;
  return (PAM_SUCCESS);
}

PAM_EXTERN int	pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  const char *user = NULL;
  char *password = NULL;
  int retval = -1;

  if ((retval = pam_get_user(pamh, &user, NULL)) != PAM_SUCCESS)
    return (retval);
  if ((retval = pam_get_data(pamh, "Password", (const void **)&password)) != PAM_SUCCESS)
    return (retval);
  create_container(user, password);
  return PAM_SUCCESS;
}

PAM_EXTERN int	pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  const char *user = NULL;
  int retval = -1;

  if ((retval = pam_get_user(pamh, &user, NULL)) != PAM_SUCCESS)
    return (retval);
  close_container(user);
  return (PAM_SUCCESS);
}
