CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -Iinc
CLIBS	=	-lpthread

NAME	=	philo_bonus
SRC		=	src/utils2_bonus.c src/philosophers_bonus.c src/actions_bonus.c src/cleanup_bonus.c src/errors_bonus.c src/init_bonus.c src/main_bonus.c src/utils_bonus.c
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
