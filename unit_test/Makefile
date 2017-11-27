NAME	= test

SRC	= unit_test.c \
	  ../container_func.c

LDFLAGS	+= -lcunit

CC	= gcc

RM	= rm

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
