##
## Makefile for crypto in /home/takos/Crypto_test
## 
## Made by takos
## Login   <kostas.konovodoff@epitech.eu>
## 
## Started on  Thu Nov 23 17:15:28 2017 takos
## Last update Thu Nov 23 18:11:22 2017 takos
##

NAME		= test

SRCS		= pam_main.c

LDFLAGS		+= -lpam -lpam_misc

RM		= rm -f

OBJS		= $(SRCS:.c=.o)

CC		= gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
