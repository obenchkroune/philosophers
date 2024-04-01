NAME		=	philo_bonus
CC			=	cc
INCLUDES	=	-I./includes
CFLAGS		=	-Wall -Wextra -Werror $(INCLUDES)
CLIBS		=	-lpthread
SRCS		=	$(shell find ./src -type f -name "*.c")
OBJ			=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): all

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(CLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)