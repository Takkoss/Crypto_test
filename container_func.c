# define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *getUserPath(const char *user, const char *file)
{
  char *buffer = NULL;
  if (strcmp(user, "root") == 0)
    asprintf(&buffer, "/root/%s", file);
  else
    asprintf(&buffer, "/home/%s/%s", user, file);
  return (buffer);
}

/**
 * Close the container
 */
void close_container(const char *user)
{
  char *buffer = NULL;
  char *path_folder = NULL;

  path_folder = getUserPath(user, "secure_data-rw");
  asprintf(&buffer, "sudo umount %s", path_folder);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "rm -r %s", path_folder);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "sudo cryptsetup luksClose container-%s", user);
  system(buffer);
  free(buffer);
  free(path_folder);
}


/**
 * Open the container
 */
int	open_container(const char *user, const char *password, int format)
{
  char *buffer = NULL;
  char *path_container = NULL;
  char *path_folder = NULL;
  int ret = -1;

  path_container = getUserPath(user, ".secure-data");
  path_folder = getUserPath(user, "secure_data-rw");
  asprintf(&buffer, "echo \"%s\" | sudo cryptsetup luksOpen %s container-%s", password, path_container, user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "mkdir -p %s", path_folder);
  system(buffer);
  free(buffer);
  if (format == 1)
    {
      asprintf(&buffer, "sudo mkfs.ext4 /dev/mapper/container-%s", user);
      system(buffer);
      free(buffer);
    }
  asprintf(&buffer, "sudo mount /dev/mapper/container-%s %s", user, path_folder);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "sudo chown -R %s %s", user, path_folder);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "sudo chmod -R 700 %s", path_folder);
  system(buffer);
  free(path_folder);
  free(path_container);
  free(buffer);
  return (1);
}


/**
 * Create the container if it does not exists then open it
 */
int create_container(const char *user, const char *password)
{
  char *buffer = NULL;
  char *path_container = NULL;

  path_container = getUserPath(user, ".secure-data");
  if (access(path_container, F_OK) != -1)
    return(open_container(user, password, 0));
  asprintf(&buffer, "dd bs=10000 count=1000 if=/dev/zero of=%s", path_container);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "echo \"YES\" | echo \"%s\" | echo \"%s\" | sudo cryptsetup luksFormat %s", password, password, path_container);
  system(buffer);
  free(buffer);
  free(path_container);
  return (open_container(user, password, 1));
}

void change_passphrase(const char *old_pass, const char *new_pass, const char *user)
{
  char *buffer = NULL;
  char *path = NULL;

  path = getUserPath(user, ".secure-data");
  asprintf(&buffer, "echo '%s\n%s\n' | sudo cryptsetup luksAddKey -q %s", old_pass, new_pass, path);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "echo '%s' | sudo cryptsetup luksRemoveKey %s", old_pass, path);
  system(buffer);
  free(buffer);
  free(path);
}
