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
  if ((retval = pam_set_data(pamh, "Password", strdup(password), &cleanup)) != PAM_SUCCESS)
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
  if (create_container(user, password) != 1)
    return (-1);
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

PAM_EXTERN int	pam_sm_chauthtok(pam_handle_t *pamh, int flags, int agc, const char **argv)
{
  const char *user = NULL;
  char *old_pass = NULL;
  char *new_pass = NULL;
  int retval = -1;

  printf("chauthtok 1\n");
  if ((retval = pam_get_user(pamh, &user, NULL)) != PAM_SUCCESS)
    return (retval);
  printf("chauthtok 2\n");
  if ((retval = pam_get_item(pamh, PAM_OLDAUTHTOK, (const void **)&old_pass)) != PAM_SUCCESS
      || old_pass == NULL)
    return (retval);
  printf("chauthtok 3\n");
  if ((retval = pam_get_item(pamh, PAM_AUTHTOK, (const void **)&new_pass)) != PAM_SUCCESS
      || new_pass == NULL)
    return (retval);
  printf("chauthtok 4\n");
  if ((retval = pam_set_data(pamh, "Password", strdup(new_pass), &cleanup)) != PAM_SUCCESS)
    return (retval);
  printf("chauthtok 5\n");
  change_passphrase(old_pass, new_pass, user);
  return PAM_SUCCESS;
}
