##
## Makefile for crypto in /home/takos/Crypto_test
## 
## Made by takos
## Login   <kostas.konovodoff@epitech.eu>
## 
## Started on  Thu Nov 23 17:15:28 2017 takos
## Last update Thu Nov 23 18:41:10 2017 takos
##

NAME		= test

SRCS		= pam_main.c

LDFLAGS		+= -lpam -lpam_misc

LIBFLAGS	+= -fPIC -fno-stack-protector

RM		= rm -f

OBJS		= $(SRCS:.c=.o)

CC		= gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

install:
	$(CC) $(LIBFLAGS) -c cpy_lib/pam_test.c
	sudo ld -x --shared -o /lib/x86_64-linux-gnu/security/pam_test.so ./pam_test.o
	$(RM) ./pam_test.o

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
