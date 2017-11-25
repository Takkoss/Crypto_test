#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int free_ptrs(void *buffer, void *path, int ret)
{
  if (buffer != NULL)
    free(buffer);
  if (path != NULL)
    free(path);
  return (ret);
}

/**
 * Close the container
 */
int close_container(const char *user)
{
  char *buffer = NULL;
  
  asprintf(&buffer, "sudo umount /home/%s/secure_data-rw/", user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "rm -r /home/%s/secure_data-rw/", user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "sudo cryptsetup luksClose container-%s", user);
  system(buffer);
  free(buffer);
}


/**
 * Open the container
 */
int	open_container(const char *user, const char *password, int format)
{
  char *buffer = NULL;
  char *path = NULL;
  int ret = -1;

  asprintf(&path, "/home/%s/.secure-data", user);  
  asprintf(&buffer, "echo \"%s\" | sudo cryptsetup luksOpen %s container-%s", password, path, user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "mkdir /home/%s/secure_data-rw", user);
  system(buffer);
  free(buffer);
  if (format == 1)
    {
      asprintf(&buffer, "sudo mkfs.ext4 /dev/mapper/container-%s", user);
      system(buffer);
      free(buffer);
    }
  asprintf(&buffer, "sudo mount /dev/mapper/container-%s /home/%s/secure_data-rw/", user, user);
  system(buffer);
  return (free_ptrs(buffer, path, 1));
}


/**
 * Create the container if it does not exists then open it
 */
int create_container(const char *user, const char *password)
{
  char *buffer = NULL;
  char *path = NULL;

  asprintf(&path, "/home/%s/.secure-data", user);
  if (access(path, F_OK) != -1)
    return(open_container(user, password, 0));
  asprintf(&buffer, "dd bs=10000 count=1000 if=/dev/zero of=%s", path);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "echo \"YES\" | echo \"%s\" | echo \"%s\" | sudo cryptsetup luksFormat %s", password, password, path);
  system(buffer);
  free(buffer);
  buffer = NULL;
  open_container(user, password, 1);
  return (free_ptrs(buffer, path, 1));
}
