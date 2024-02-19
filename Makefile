NAME	=	philo

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -Iinclude
CLIBS	=	-lpthread

SRC		=	$(shell find ./source -type f -name '*.c')
OBJ		=	$(SRC:.c=.o)


all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)