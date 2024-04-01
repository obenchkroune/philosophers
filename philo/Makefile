NAME		=	philo
CC			=	cc
INCLUDES	=	-I./includes
CFLAGS		=	-Wall -Wextra -Werror $(INCLUDES) -fsanitize=thread -g
CLIBS		=	-lpthread
SRCS		=	$(shell find ./src -type f -name "*.c")
OBJS		=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CLIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)