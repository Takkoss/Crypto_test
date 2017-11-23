/*
** pam_test.c for pam in /home/takos/Crypto_test
** 
** Made by takos
** Login   <kostas.konovodoff@epitech.eu>
** 
** Started on  Wed Nov 22 16:58:01 2017 takos
** Last update Thu Nov 23 17:10:09 2017 takos
*/

#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <security/pam_modules.h>
#include <stdio.h>

static struct pam_conv conv = {
  misc_conv,
  NULL
};

int main(int argc, char **argv)
{
  pam_handle_t *pamh = NULL;
  int retval;
  const char *user = "nobody";

  if (argc == 2)
    user = argv[1];

  if (argc > 2 || argc < 2)
    {
      fprintf(stderr, "Usage : check_user [username]\n");
      exit(1);
    }
  retval = pam_start("check_user", user, &conv, &pamh);

  if (retval == PAM_SUCCESS)
    retval = pam_authenticate(pamh, 0);
  if (retval == PAM_SUCCESS)
    retval = pam_acct_mgmt(pamh, 0);
  if (retval == PAM_SUCCESS)
    fprintf(stdout, "Authenticated success!\n");
  else
    fprintf(stdout, "Authenticated failed.\n");
  if (pam_end(pamh, retval) != PAM_SUCCESS)
    {
      pamh = NULL;
      fprintf(stderr, "check_user: failed to release authenticator.\n");
      exit(1);
    }

  return (retval == PAM_SUCCESS ? 0:1);
}
