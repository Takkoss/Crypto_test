##
## Makefile for crypto in /home/takos/Crypto_test
## 
## Made by takos
## Login   <kostas.konovodoff@epitech.eu>
## 
## Started on  Thu Nov 23 17:15:28 2017 takos
## Last update Sat Nov 25 18:39:58 2017 takos
##

NAME		= pam_tek_module.so

SRCS		= pam_func.c \
		  container_func.c

RM		= rm -f

OBJS		= $(SRCS:.c=.o)

CC		= gcc

LD		 = ld

%.o: %.c
	$(CC) -fPIC -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(LD) --shared -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

install: re
	sudo ./register_pam_module.sh

uninstall: fclean
	sudo ./unregister_pam_module.sh

re: fclean all

.PHONY: all clean fclean re
