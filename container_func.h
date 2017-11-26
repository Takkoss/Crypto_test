#ifndef _CONTAINER_H_
# define _CONTAINER_H_

int	close_container(const char *user);
int	create_container(const char *user, const char *password);
void	change_passphrase(const char *old_pass, const char *new_pass, const char *user);
#endif /* !_CONTAINER_H_ */
