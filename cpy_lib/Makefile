##
## Makefile for crypto in /home/takos/Crypto_test
## 
## Made by takos
## Login   <kostas.konovodoff@epitech.eu>
## 
## Started on  Thu Nov 23 17:15:28 2017 takos
## Last update Thu Nov 23 21:55:24 2017 takos
##

NAME		= pam_tek_module.so

SRCS		= pam_test.c

RM		= rm -f

OBJS		= $(SRCS:.c=.o)

CC		= gcc

LD		 = ld

%.o: %.c
	$(CC) -fPIC -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(LD) --shared -o $(NAME) $(OBJS)
	sudo mv $(NAME) /lib/security/
	rm $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
