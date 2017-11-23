#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdio.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  const char *user = NULL;
  int  retval;
  
  fprintf(stdout, "enter");
  retval = pam_get_user(pamh, &user, NULL);
  if (retval != PAM_SUCCESS || user == NULL)
    fprintf(stdout, "User failed.");
  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
  fprintf(stdout, "Acct_mgmt enter.\n");
  return (PAM_SUCCESS);
}
