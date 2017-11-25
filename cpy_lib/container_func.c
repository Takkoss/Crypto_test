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

int close_container(const char *user)
{
  char *buffer = NULL;
  char *path = NULL;
  
  asprintf(&buffer, "sudo umount /home/%s/container-decrypted-rw/", user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "rm -r /home/%s/container-decrypted-rw/", user);
  system(buffer);
  free(buffer);
  asprintf(&buffer, "sudo cryptsetup luksClose container-%s", user);
  system(buffer);
  free(buffer);
}

/**
 * Create the container if it does not exists
 */
int create_container(const char *user, const char *password)
{
  char *buffer = NULL;
  char *path = NULL;

  asprintf(&path, "/home/%s/.secure-data", user);
  printf("Checking container on path %s\n", path);
  if (access(path, F_OK) != -1)
    return(free_ptrs(buffer, path, 1));
  printf("Container does not exists, creating\n");
  asprintf(&buffer, "dd bs=10000 count=1000 if=/dev/zero of=%s", path);
  system(buffer);
  printf("dd done\n");
  free(buffer);
  asprintf(&buffer, "mkfs.ext4 %s", path);
  system(buffer);
  printf("mkfs done\n");
  free(buffer);
  asprintf(&buffer, "echo \"YES\" | echo \"%s\" | echo \"%s\" | cryptsetup luksFormat %s", password, password, path);
  system(buffer);
  free(buffer);
  printf("luksFormat done\n");
  open_container(user, password, 1);
  return (free_ptrs(buffer, path, 2));
}

/**
 * Open the container
 */
int	open_container(const char *user, const char *password, int format)
{
  char *buffer = NULL;
  char *path = NULL;
  int ret = -1;

  printf("Calling create container\n");
  if ((ret = create_container(user, password)) != 1)
    return (ret);
  printf("Container created, opening\n");
  asprintf(&path, "/home/%s/.secure-data", user);  
  asprintf(&buffer, "echo \"%s\" | sudo cryptsetup luksOpen %s container-%s", password, path, user);
  system(buffer);
  free(buffer);
  printf("luksOpen done\n");
  asprintf(&buffer, "mkdir /home/%s/container-decrypted-rw", user);
  system(buffer);
  free(buffer);
  printf("mkdir container-decrypted-rw done\n");
  if (format == 1)
    {
      printf("Formating\n");
      asprintf(&buffer, "sudo mkfs.ext4 /dev/mapper/container-%s", user);
      system(buffer);
      free(buffer);
      printf("mkfs done\n");
    }
  asprintf(&buffer, "sudo mount -t ext4 /dev/mapper/container-%s /home/%s/container-decrypted-rw/", user, path);
  system(buffer);
  printf("mount done\n");
  return (free_ptrs(buffer, path, 1));
}

int main(int argc, char **argv)
{
  if (argc != 3)
    {
      printf("Args\n");
      return (0);
    }
  open_container(argv[1], argv[2], 0);
  return (0);
}
